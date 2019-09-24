#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>

enum state_enum {MUTE,CALM,CRY};
char mp3name[3][15] = {"a.mp3","b.mp3","c.mp3"};

long x = 0;
long y = 0;
long z = 0;
long curr = 0;
long prev = 0;
bool shake;

void state_machine_run();
void baby_mute();
void baby_calm();
void baby_cry();
bool bigMovement();
bool isMoving();


int time = 0;
int MAX_MUTE          = 50;
int MAX_CALM          = 100;
int MAX_CRY           = 100;

uint8_t state = MUTE;

void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.playOne(mp3name[0]);
}

void loop(){
  shake = isMoving();
  if (shake){
    time = time - 4;
    Serial.print("time shake");
  } else {
    time += 1;
    Serial.print("time no shake");
  }
 

  Serial.print("State: ");
  Serial.print(state);
  Serial.print(" - Shake: ");
  Serial.print(shake);
  Serial.print(" - Time: ");
  Serial.println(time);
  player.play();
  Serial.println("here");
  state_machine_run();
  Serial.println("aqui");
  delay(50);
}

void state_machine_run()
{
  switch(state)
  {
    case MUTE:
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      if(time > MAX_MUTE){
        time = 0;
        baby_calm();
        state = CALM;
      }
      break;

    case CALM:
      if(time > MAX_CALM){
        time = 0;
        baby_cry();
        state = CRY;
      }
      if(time < 0){
        time = 0;
        baby_mute();
        state = MUTE;
      }
//      if(shake && time > 0){
//        time = time - 4;
//      }
//      if(bigMovement()){
//        baby_cry();
//        state = CRY;
//      }
      break;

    case CRY:
      if(time > MAX_CRY){
        time = 0;
        baby_mute();
        state = MUTE;
      }
      if(time < 0){
        time = 0;
        baby_calm();
        state = CALM;
      }
//      if(shake && time > 0){
//        time = time - 4;
//      }
      break;

  }
}

void baby_mute(){
 Serial.println("mute play before"); 
 player.playOne(mp3name[0]);
 Serial.println("mute play after");
 
}

void baby_calm(){
 Serial.println("calm play before");
 player.playOne(mp3name[1]);
 Serial.println("calm play after");
 
}

void baby_cry(){
 Serial.println("cry play before");
 player.playOne(mp3name[2]);
 Serial.println("cry play after");
 }

bool bigMovement(){
  return false;
}

bool isMoving(){
  int i;
  long x,y,z;
  x=y=z=0;

  //read value 50 times and output the average
  for (i=0 ; i < 50 ; i++) {
    x = x + analogRead(3);
    y = y + analogRead(4);
    z = z + analogRead(5);
  }
  x = x / 50;
  y = y / 50;
  z = z / 50;

  curr = x + y + z;
  bool temp = (curr - prev) > 4;
//  Serial.print(prev);
//  Serial.print(" - ");
//  Serial.print(curr);
//  Serial.print(" - ");
//  Serial.println(curr - prev);
  prev = curr;
  return temp;
}
