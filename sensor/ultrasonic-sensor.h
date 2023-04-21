#ifndef _ULTRASONIC_SENSOR_H_
#define _ULTRASONIC_SENSOR_H_

#include "Arduino.h"

class UltrasonicSensor{
private:
  int _trigger;
  int _echo;
public:
  UltrasonicSensor();
  UltrasonicSensor(int trigger, int echo);
  void configure();
  float distanceCm();
};

#endif
