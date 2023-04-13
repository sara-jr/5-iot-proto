#ifndef _ULTRASONIC_SENSOR_H_
#define _ULTRASONIC_SENSOR_H_
#include <HCSR04.h>

class UltrasonicSensor: public HCSR04{
public:
  UltrasonicSensor();
  UltrasonicSensor(int trigger, int echo);
};

#endif
