#include <ParamotorLight.h>
#include <WingLight.h>

#include <Servo.h>

#define Ch1Input 2  
#define Ch2Input 3

int Chan1Interrupt = Ch1Input;
int Chan2Interrupt = Ch2Input;

unsigned long Chan1_start, Chan2_start;
volatile double Chan1_val, Chan2_val;
volatile double Chan1_last, Chan2_last;


long LocalMillis;
long LocalFrameCounter;
long StartMillis;
long FrameCounter;


LandingLight ll = LandingLight(6, 10, 200);
WingLight wl = WingLight(5);


void setup() {
  pinMode(Ch1Input, INPUT);
  pinMode(Ch2Input, INPUT);

  attachInterrupt(digitalPinToInterrupt(Chan1Interrupt), Chan1_begin, RISING);
  attachInterrupt(digitalPinToInterrupt(Chan2Interrupt), Chan2_begin, RISING);
}

void loop() {
  LocalMillis = millis();
  LocalFrameCounter = (LocalMillis - StartMillis) / 20;


  ll.tick();
  wl.tick();

  if (LocalFrameCounter > FrameCounter) {

    FrameCounter = LocalFrameCounter;

    ll.updateState(Chan1_val);
    wl.updateState(Chan2_val);


  }
}





void Chan1_begin() {
  Chan1_start = micros();
  detachInterrupt(digitalPinToInterrupt(Chan1Interrupt));
  attachInterrupt(digitalPinToInterrupt(Chan1Interrupt), Chan1_end, FALLING);
}

void Chan1_end() {
  Chan1_val = micros() - Chan1_start;
  detachInterrupt(digitalPinToInterrupt(Chan1Interrupt));
  attachInterrupt(digitalPinToInterrupt(Chan1Interrupt), Chan1_begin, RISING);

  if (Chan1_val < 1000 || Chan1_val > 2000) {
    Chan1_val = Chan1_last;
  }
  else {
    Chan1_last = Chan1_val;
  }

}

void Chan2_begin() {
  Chan2_start = micros();
  detachInterrupt(digitalPinToInterrupt(Chan2Interrupt));
  attachInterrupt(digitalPinToInterrupt(Chan2Interrupt), Chan2_end, FALLING);
}

void Chan2_end() {
  Chan2_val = micros() - Chan2_start;
  detachInterrupt(digitalPinToInterrupt(Chan2Interrupt));
  attachInterrupt(digitalPinToInterrupt(Chan2Interrupt), Chan2_begin, RISING);

  if (Chan2_val < 1000 || Chan2_val > 2000) {
    Chan2_val = Chan2_last;
  }
  else {
    Chan2_last = Chan2_val;
  }

}
