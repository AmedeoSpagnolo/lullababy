#include "Baby.h"

Baby dingo = Baby();  // in seconds

void setup(){
  Serial.begin(9600);
  dingo.opt(10); // rest time in second
}

void loop(){
  dingo.alive();
  Serial.print("state: "); Serial.print(dingo.state);
  Serial.print(" - happyness: "); Serial.print(dingo.happyness);
  Serial.print(" - cry: "); Serial.print(dingo.isCrying);
  Serial.print(" - speak: "); Serial.print(dingo.isSpeaking);
  Serial.print(" - mute: "); Serial.print(dingo.isMute);
  Serial.print(" - shake: "); Serial.print(dingo.shake);
  Serial.print(" - shock: "); Serial.println(dingo.shock);
}
