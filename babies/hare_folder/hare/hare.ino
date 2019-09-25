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
bool shake = false;
bool shock = false;

void state_machine_run();
void baby_mute();
void baby_calm();
void baby_cry();
bool isMoving();

int time = 0;
int MAX_MUTE      = 50;
int MAX_CALM      = 50;
int MAX_CRY       = 500;
int AFTER_SHOCK   = 40;
int MUTE_TO_CALM  = 10;  
int CALM_TO_CRY   = 10;
int CRY_TO_CALM   = 40;  

uint8_t state = MUTE;

void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.playOne(mp3name[0]);
  player.setVolume(0x00);
}

void loop(){
  shake = isMoving();
  if (shake){
    time -= 4;
  } else {
    time += 1;
  }

  Serial.print("State: ");
  Serial.print(state);
  Serial.print(" - Shake: ");
  Serial.print(shake);
  Serial.print(" - Shock: ");
  Serial.print(shock);
  Serial.print(" - Time: ");
  Serial.println(time);

  player.play();
  delay(150);
  state_machine_run();
}

void state_machine_run()
{
  switch(state)
  {
    case MUTE:
      if(shock){
        time = AFTER_SHOCK;
        baby_cry();
        state = CRY;
      }
      if(time > MAX_MUTE){
        time = MUTE_TO_CALM;
        baby_calm();
        state = CALM;
      }
      break;

    case CALM:
      if(shock){
        time = AFTER_SHOCK;
        baby_cry();
        state = CRY;
      }
      if(time > MAX_CALM){
        time = CALM_TO_CRY;
        baby_cry();
        state = CRY;
      }
      if(time < 0){
        time = 0;
        baby_mute();
        state = MUTE;
      }
      break;

    case CRY:
      if(time > MAX_CRY){
        time = 0;
        baby_mute();
        state = MUTE;
      }
      if(time < 0){
        time = CRY_TO_CALM;
        baby_calm();
        state = CALM;
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

bool isMoving(){
  int i;
  long x = 0;
  long y = 0;
  long z = 0;
  shock = false;
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
  bool moving = (curr - prev) > 4;
  if ((curr - prev) > 500) shock = true;
  prev = curr;
  return moving;
}
