#ifndef _VEHICLE_COUNTER_H_
#define _VEHICLE_COUNTER_H_

#include "ultrasonic-sensor.h"
#include <Arduino.h>

class VehicleCounter{
private:
  UltrasonicSensor _sensor;
  int _count;
  int _base_distance;
  int _min_vehicle_height;
  int _buffer[60];
public:
  VehicleCounter(int trigger=5, int echo=6, int min_vehicle_height=15);
  
  int get_count();
  void configure();
  void measure_base_distance();
  void measure();
  void reset_count();
};

#endif
