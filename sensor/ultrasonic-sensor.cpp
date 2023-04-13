#include "ultrasonic-sensor.h"
UltrasonicSensor::UltrasonicSensor(): HCSR04(5, 6){}
UltrasonicSensor::UltrasonicSensor(int trigger, int echo): HCSR04(trigger, echo){}
