#include "Eyes.h"
#include "Arduino.h"

Eyes::Eyes(){
  int eye_right;
  int eye_left;
}

void Eyes::open(){
  digitalWrite(eye_right, HIGH);
  digitalWrite(eye_left,  HIGH);
}

void Eyes::close(){
  digitalWrite(eye_right, LOW);
  digitalWrite(eye_left,  LOW);
}

void Eyes::pins(int r, int l){
  eye_right = r;
  eye_left = l;
  pinMode(eye_right, OUTPUT);
  pinMode(eye_left,  OUTPUT);
}
