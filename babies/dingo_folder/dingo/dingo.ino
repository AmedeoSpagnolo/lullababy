#include "Baby.h"

Baby dingo = Baby();

void setup(){
  Serial.begin(9600);
}

void loop(){
  dingo.alive();
}
