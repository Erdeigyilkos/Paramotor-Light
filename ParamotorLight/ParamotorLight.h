#ifndef PARAMOTORLIGHT_H
#define PARAMOTORLIGHT_H

#include "Arduino.h"


class LandingLight
{
  private:
    int _LightPin;
    
    int _LightMiddle;
    int _LightFull;
    int _LightCurrent;

    int _state;
    
    unsigned long _previousMillis;  
    
    void _LightDown(int limit,int delayTime);
    void _LightUp(int limit,int delayTime);

  public:

    LandingLight(int LightPin,int LightMiddle,int LightFull);
    void updateState(int channelValue);
    void tick();
    
    
   

};

#endif

