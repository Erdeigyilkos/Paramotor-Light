#include "ParamotorLight.h"

LandingLight::LandingLight(int LightPin, int LightMiddle, int LightFull) {
  pinMode(LightPin, OUTPUT);
  analogWrite(LightPin, 0);
  _LightPin = LightPin;
  _LightMiddle = LightMiddle;
  _LightFull = LightFull;
  _LightCurrent = 0;
  _state = 0;
  _previousMillis = 0;
}

void LandingLight::tick() {

  if (_state == 0 && _LightCurrent != 0) {
    _LightDown(0, 15);
  }

  if (_state == 1 && _LightCurrent != _LightMiddle) {

    if (_LightCurrent < _LightMiddle) {
      _LightUp(_LightMiddle, 15);
    } else {
      _LightDown(_LightMiddle, 2);
    }
  }

  if (_state == 2 && _LightCurrent != _LightFull) {
    _LightUp(_LightFull, 3);
  }

}

void LandingLight::_LightDown(int limit, int delayTime) {
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= delayTime) {
    _previousMillis = currentMillis;
    _LightCurrent--;

    if (_LightCurrent < limit) {
      _LightCurrent = limit;
    }

    analogWrite(_LightPin, _LightCurrent);

  }

}

void LandingLight::_LightUp(int limit, int delayTime) {

  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= delayTime) {

    _previousMillis = currentMillis;
    _LightCurrent++;

    if (_LightCurrent > limit) {
      _LightCurrent = limit;
    }

    analogWrite(_LightPin, _LightCurrent);

  }

}

void LandingLight::updateState(int channelValue) {
  if (channelValue < 1300 && _state != 0) {
    _state = 0;
  } else if (channelValue > 1700 && _state != 2) {
    _state = 2;

  } else if ((channelValue < 1700 && channelValue > 1300) && _state != 1) {
    _state = 1;

  }

}
