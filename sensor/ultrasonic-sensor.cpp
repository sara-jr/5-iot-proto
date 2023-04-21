#include "ultrasonic-sensor.h"

UltrasonicSensor::UltrasonicSensor(){
  _trigger = 5;
  _echo = 6;
}

void UltrasonicSensor::configure(){
  pinMode(_trigger, OUTPUT);
  pinMode(_echo, INPUT);
}

float UltrasonicSensor::distanceCm(){
  digitalWrite(_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger, LOW);
  long pulse = pulseIn(_echo, HIGH);
  float distance = pulseIn(_echo, HIGH)/58.0f;
  Serial.print(pulse);
  Serial.println(" pulse ");
  Serial.print(distance);
  Serial.println(" cm ");
  return distance;
}

UltrasonicSensor::UltrasonicSensor(int trigger, int echo){
  _trigger = trigger;
  _echo = echo;
}
