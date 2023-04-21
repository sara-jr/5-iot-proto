#include "ultrasonic-sensor.h"
UltrasonicSensor::UltrasonicSensor(){
  _trigger = 5;
  _echo = 6;
}

UltrasonicSensor::~UltrasonicSensor(){
  delete _sensor;  
}

void UltrasonicSensor::configure(){
  _sensor = new HCSR04(_trigger, _echo);
}

float UltrasonicSensor::distanceCm(){
  return _sensor->dist();
}

UltrasonicSensor::UltrasonicSensor(int trigger, int echo){
  _trigger = trigger;
  _echo = echo;
}
