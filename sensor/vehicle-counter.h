#ifndef _VEHICLE_COUNTER_H_
#define _VEHICLE_COUNTER_H_

#include <HCSR04.h>

class VehicleCounter{
private:
  int _count;
  int _base_distance;
  int _min_vehicle_height;
  int _buffer[60];
public:
  VehicleCounter(int trigger, int echo, int min_vehicle_height);
  
  int get_count();
  void measure_base_distance();
  void measure();
  void reset_count();
};

#endif
