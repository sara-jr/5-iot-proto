#include "distance-sensor.h"

DistanceSensor::DistanceSensor(int trigger, int echo){
    _trigger = trigger;
    _echo = echo;
    _base_distance = 0;
    _tolerance = 0;
    _prev = 0;
}

void DistanceSensor::config(){
  pinMode(_trigger, OUTPUT);
  pinMode(_echo, INPUT);
}

void DistanceSensor::set_base_distance(){
  _base_distance = get_distance();
}

int DistanceSensor::get_base_distance(){
  return _base_distance;
}

void DistanceSensor::set_tolerance(int t){
  _tolerance = t;
}

bool DistanceSensor::has_passed(){
  int distance = get_distance(), delta = distance - _prev;
  
  if(delta * delta <= _tolerance){
    return false;
  }

  if(distance - _base_distance < _tolerance){
    return false;
  }

  return true;
} 

int DistanceSensor::get_distance(){
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger, LOW);
  return pulseIn(_echo, HIGH)/59;
}
