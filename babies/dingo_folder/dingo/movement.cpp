#include "Movement.h"
#include "Arduino.h"

Movement::Movement(){
  int _pin_x;
  int _pin_y;
  int _pin_z;
  int _shake_sensibility;
  int _shock_sensibility;
  bool _shake;
  bool _shock;
  long _prev = 0;
}

void Movement::updateValues(){
  int i;
  long x = 0;
  long y = 0;
  long z = 0;
  long curr;
  long delta;
  for (i=0 ; i<50 ; i++) {
    x = x + analogRead(_pin_x);
    y = y + analogRead(_pin_y);
    z = z + analogRead(_pin_z);
  }
  x = (x/50);
  y = (y/50);
  z = (z/50);
  curr = x + y + z;
  delta = abs(curr-_prev);
  _shake = (delta > _shake_sensibility); // 4 Optimal Value
  _shock = (delta > map(_shock_sensibility,0,10,200,1000)); // 400 Optimal Value
  _prev = curr;
}

void Movement::pins(int x, int y, int z){
  _pin_x = x;
  _pin_y = y;
  _pin_z = z;
  pinMode(_pin_x, INPUT);
  pinMode(_pin_y, INPUT);
  pinMode(_pin_z, INPUT);
}

void Movement::shockSensibility(int shock){
  _shock_sensibility = shock;
}

void Movement::shakeSensibility(int shake){
  _shake_sensibility = shake;
}

bool Movement::shake(){
  return _shake;
}

bool Movement::shock(){
  return _shock;
}
