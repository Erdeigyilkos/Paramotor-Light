#include "WingLight.h"

WingLight::WingLight(int LightPin) {
  pinMode(LightPin, OUTPUT);
  analogWrite(LightPin, 0);

  _LightPin = LightPin;
  _LightRequest = 0;
  _LightCurrent = 0;
  _State = 0;
  _previousMillis = millis();
  _Rising = false;

}

void WingLight::_handleFade() {

  if (_LightCurrent < 1) {
    _Rising = true;
  }

  if (_LightCurrent > 150) {
    _Rising = false;
  }

  if (_Rising) {
    _LightUp(255, 12);
  } else {
    _LightDown(0, 12);
  }

}

void WingLight::tick() {

  if (_State == 1) {
    _handleFade();
    return;
  }

  if (_LightCurrent > _LightRequest) {

    _LightDown(_LightRequest, 1);
  }

  if (_LightCurrent < _LightRequest) {

    _LightUp(_LightRequest, 1);
  }

}

void WingLight::_LightDown(int limit, int delayTime) {

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

void WingLight::_LightUp(int limit, int delayTime) {

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

void WingLight::updateState(int ChannelValue) {

  //1070-?
  int val = map(ChannelValue, 1075, 1900, 0, 250);

  int diff = abs(_LightRequest - val);

  if (val <= 250 && (_State != 0 || diff > 5)) {

    if (val < 0) {
      val = 0;
    }

    _State = 0;
    _LightRequest = val;

  }

  if (250 < val && _State != 1) {

    _State = 1;
  }

}
