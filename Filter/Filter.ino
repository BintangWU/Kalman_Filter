#include "Filter.h"
Filter  filter(2, 2, 0.01);

#define nSampel 30

uint16_t data[nSampel], cnt, offset;
uint16_t dataMax = 0, dataMin = 1024;
float current;


void setup() {
  Serial.begin(115200);

  for (cnt = 0; cnt < nSampel; cnt++) {
    data[cnt] = filter.kalmanFilter(analogRead(A0));
    delay(1);
  }
  cnt = 0;
  for (cnt = 0; cnt < nSampel; cnt++) {

    if (dataMax < data[cnt])
      dataMax = data[cnt];
    if (dataMin > data[cnt])
      dataMin = data[cnt];

    offset = (dataMax - dataMin);
  }

  Serial.println("Data MAX: " + String(dataMax));
  Serial.println("Data Min: " + String(dataMin));
  Serial.println("Offset  : " + String(offset));
  delay(1000);

}

void loop() {
  int adc = filter.kalmanFilter(analogRead(A0));
  current = ((adc - dataMax) * 5.0) / 1023.0;
  Serial.print(current, 2);
  Serial.print("\t");
  current = (current * 1000) / 40.0;

  Serial.println(current, 4);
  delay(10);
}
