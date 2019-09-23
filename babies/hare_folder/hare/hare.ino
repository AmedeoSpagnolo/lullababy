#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>

enum state_enum {MUTE,CALM,CRY,CALM_MOVING,CRY_MOVING};
char mp3name[3][30] = {"silence.mp3","light1.mp3","hard1.mp3"};

void state_machine_run();
void baby_mute();
void baby_calm();
void baby_cry();
bool bigMovement();
bool isMoving();

int time = 0;
int MAX_MUTE          = 800;
int MAX_CALM          = 800;
int MAX_CRY           = 800;
int CALM_MOVING_TIME  = 800;
int CRY_MOVING_TIME   = 800;


uint8_t state = MUTE;

void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.playOne(mp3name[0]);
}

void loop(){
  time += 1;
  Serial.print("State: ");
  Serial.print(state);
  Serial.print(" - Time: ");
  Serial.println(time);
  player.play();
  state_machine_run();
  delay(20);
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
      if(isMoving()){
        state = CALM_MOVING;
      }
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      break;

    case CALM_MOVING:
      if(!isMoving()){
        baby_calm();
        state = CALM;
      }
      if(time > CALM_MOVING_TIME){
        baby_mute();
        state = MUTE;
      }
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      break;

    case CRY:
      if(time > MAX_CRY){
        time = 0;
        baby_mute();
        state = MUTE;
      }
      if(isMoving()){
        state = CRY_MOVING;
      }
      break;

    case CRY_MOVING:
      if(!isMoving()){
        baby_cry();
        state = CRY;
      }
      if(time > CRY_MOVING_TIME){
        baby_calm();
        state = CALM_MOVING;
      }
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      break;
  }
}

void baby_mute(){
  player.playOne(mp3name[0]);
}

void baby_calm(){
  player.playOne(mp3name[1]);
}

void baby_cry(){
  player.playOne(mp3name[2]);
}

bool bigMovement(){
  return false;
}

bool isMoving(){
  return false;
}
