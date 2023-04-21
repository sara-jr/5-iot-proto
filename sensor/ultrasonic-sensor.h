#ifndef _ULTRASONIC_SENSOR_H_
#define _ULTRASONIC_SENSOR_H_
#include <HCSR04.h>

class UltrasonicSensor{
private:
  HCSR04 *_sensor;
  int _trigger;
  int _echo;
public:
  UltrasonicSensor();
  ~UltrasonicSensor();
  UltrasonicSensor(int trigger, int echo);
  void configure();
  float distanceCm();
};

#endif
