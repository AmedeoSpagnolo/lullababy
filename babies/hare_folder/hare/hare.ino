#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>

enum state_enum {MUTE,CALM,CRY,CALM_MOVING,CRY_MOVING};
char mp3name[3][30] = {"silence.mp3","light1.mp3","hard1.mp3"};

long x = 0;
long y = 0;
long z = 0;
long prev = 0;
bool shake = false;

void state_machine_run();
void baby_mute();
void baby_calm();
void baby_cry();
bool bigMovement();
bool isMoving();

int time = 0;
int MAX_MUTE          = 400;
int MAX_CALM          = 400;
int MAX_CRY           = 400;
int CALM_MOVING_TIME  = 400;
int CRY_MOVING_TIME   = 400;


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
  shake = isMoving();

  Serial.print("State: ");
  Serial.print(state);
  Serial.print(" - Shake: ");
  Serial.print(shake);
  Serial.print(" - Time: ");
  Serial.println(time);
  player.play();
  state_machine_run();
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
      if(time > MAX_CALM && !shake){
        time = 0;
        baby_cry();
        state = CRY;
      }
      if(shake && time > 0){
        time = time - 10;
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
      if(shake && time > 0){){
        time = time - 10;
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
  int i;
  long x,y,z;
  x=y=z=0;

  //read value 50 times and output the average
  for (i=0 ; i < 50 ; i++) {
    x = x + analogRead(3) ; // Ｘ
    y = y + analogRead(4) ; // Ｙ
    z = z + analogRead(5) ; // Ｚ
  }
  x = x / 50 ;
  y = y / 50 ;
  z = z / 50 ;
  shake = (x + y + z - prev) > 4;
  prev = x + y + z;
  return shake;
}
