#include "movement.h"

int shake = 0;
int shock = 0;

Movement acc = Movement();

void setup(){
  Serial.begin(9600);
  acc.pins(3,4,5); // x, y, z
  acc.shockSensibility(5); // 0 - 10
  acc.shakeSensibility(5); // 0 - 10
}

void loop(){
  acc.updateValues();
  shake = acc.shake();
  shock = acc.shock();
  Serial.print(shake);
  Serial.println(shock);
  delay(50);
}
