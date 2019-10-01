#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include <Math.h>
#include "param.h"

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.print(ame);
  delay(80);
}
