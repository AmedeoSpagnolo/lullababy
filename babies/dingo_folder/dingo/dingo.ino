#include "movement.h"
#include "Eyes.h"

int shake = 0;
int shock = 0;

Movement acc = Movement();
Eyes eyes = Eyes();

void setup(){
  Serial.begin(9600);
  acc.pins(3,4,5); // x, y, z
  acc.shockSensibility(5); // 0 - 10
  acc.shakeSensibility(5); // 0 - 10
  eyes.pins(3,6);
}

void loop(){
  acc.updateValues();
  shake = acc.shake();
  shock = acc.shock();
  Serial.print(shake);
  Serial.println(shock);
  eyes.open();
  delay(300);
  eyes.close();
  delay(300);
}
