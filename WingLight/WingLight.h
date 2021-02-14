#ifndef WINGLIGHT_H
#define WINGLIGHT_H

#include "Arduino.h"


class WingLight
{
  private:
    int _LightPin;
    int _State;
    
    int _LightRequest;
    int _LightCurrent;
    
    bool _Rising;
            
    unsigned long _previousMillis;  
    
    void _LightDown(int limit,int delayTime);
    void _LightUp(int limit,int delayTime);
    
    void _handleFade();

  public:

    WingLight(int LightPin);
    void tick();
    void updateState(int ChannelValue);
    
    
   

};

#endif

