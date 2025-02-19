#include "Motor.h"       // <1>
#include "ev3api_sensor.h"
#include "ColorSensor.h" // <2>
#include "GyroSensor.h"
#include "SonarSensor.h"
#include "util.h"        // <3>

char color_set(rgb_raw_t & rgb);
void angle_fix(int spd,int ag,int type);
void run_straight(int spd);

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>
  void init();
  void terminate();

private:
  Motor leftWheel;
  Motor rightWheel;
  Motor centralWheel;
  ColorSensor colorSensor; // <3>
  GyroSensor gyrosensor;
  
#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 45;
#endif

};
