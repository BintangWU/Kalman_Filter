#ifndef Filter_h
#define Filter_h

#include <Arduino.h>
#include <math.h>

class Filter {
  public:
    Filter :: Filter(float _errMea, float _errEst, float _q) {
      errMea = _errMea;
      errEst = _errEst;
      q = _q;
    }

    float kalmanFilter(float measure) {
      kalmanGain = errEst / (errEst + errMea);
      currentEst = lastEst + kalmanGain * (measure - lastEst);
      errEst     = (1.0 - kalmanGain) * errEst + fabs(lastEst - currentEst) * q;
      lastEst = currentEst;

      return currentEst;
    }

    float adc2volt(uint16_t pin) {
      return (analogRead(pin) * 5.0) / 1024;
    }

    int volt2adc(float value) {
      return (value * 1024) / 5.0;
    }

  private:
    float errMea, errEst, q;
    float currentEst, lastEst, kalmanGain;

};
#endif
