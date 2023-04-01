#ifndef __DISTANCE_SENSOR_H__
#define __DISTANCE_SENSOR_H__

class DistanceSensor{
private:
  int _trigger;
  int _echo;
  int _base_distance;
  int _tolerance;
  int _prev;
public:
  DistanceSensor(int trigger, int echo);

  void config();

  void set_base_distance();

  int get_base_distance();

  void set_tolerance(int t);

  bool has_passed(); 

  int get_distance();
};

#endif
