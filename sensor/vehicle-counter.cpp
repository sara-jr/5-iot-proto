#include "vehicle-counter.h"

VehicleCounter::VehicleCounter(int trigger, int echo, int min_vehicle_height){
  _count = 0;
  _base_distance = 0;
  _min_vehicle_height = min_vehicle_height;
  _sensor = UltrasonicSensor(trigger, echo);
}

int VehicleCounter::get_count(){
  return _count;
}

void VehicleCounter::configure(){
  _sensor.configure();
}

void VehicleCounter::reset_count(){
  _count = 0;
}

void VehicleCounter::measure_base_distance(){
  _base_distance = _sensor.distanceCm();
}

void VehicleCounter::measure(){
  int high_count = 0;
  bool is_in_low = true;
  for(int i = 0; i < 8; i++){
    if(_sensor.distanceCm() > _min_vehicle_height){
      if(is_in_low){ //Contar solamente cuando se detecta un objeto que transiciona de la altura minima
        high_count ++;
        is_in_low = false;
      }
    }
    else{
      is_in_low = true;
    }
    delay(50);
  }
  _count += high_count;
}