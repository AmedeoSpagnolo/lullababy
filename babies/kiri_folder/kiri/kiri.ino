#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>

enum state_enum {MUTE,SPEAK,CRY};
char mp3name[3][15] = {"a.mp3","b.mp3","c.mp3"};

long x = 0;
long y = 0;
long z = 0;
long curr = 0;
long prev = 0;
bool isMoving();

int _time_to_cry;
int _time_to_speak;
int _shock_increment;
int _shake_reduction;
int _max_crying_time;

bool shake = false;
bool shock = false;

int t = 0;
int EASY_TO_CRY         = 5;  // 0 - 10
int WARNING_BEFORE_CRY  = 5;  // 0 - 10
int SHOCK_SENSITIVITY   = 5;  // 0 - 10
int SHAKE_EFFECTIVENESS = 5;  // 0 - 10
int MAX_CRYING_TIME     = 5;  // 0 - 10

uint8_t state = MUTE;

void baby_speak();
void baby_mute();
void baby_cry();

void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.setVolume(0xfe);
  player.playOne(mp3name[2]);
  _time_to_cry      = map(EASY_TO_CRY, 0, 10, 20, 100);
  _time_to_speak    = _time_to_cry - map(WARNING_BEFORE_CRY, 0, 10, 10, 20);
  _shock_increment  = map(SHOCK_SENSITIVITY, 0, 10, 2, 20);
  _shake_reduction  = map(SHAKE_EFFECTIVENESS, 0, 10, 2, 5);
  _max_crying_time  = map(MAX_CRYING_TIME, 0, 10, 100, 600);
  Serial.print("time_to_cry: ");          Serial.print(_time_to_cry);
  Serial.print(" - time_to_speak: ");     Serial.print(_time_to_speak);
  Serial.print(" - shock_increment: ");   Serial.print(_shock_increment);
  Serial.print(" - shake_reduction: ");   Serial.print(_shake_reduction);
  Serial.print(" - _max_crying_time: ");  Serial.println(_max_crying_time);

  // temp values for debug
//  _time_to_cry      = 20;
//  _time_to_speak    = 10;
//  _shock_increment  = 12;
//  _shake_reduction  = 5;
//  _max_crying_time  = 30;
}

void loop(){
  shake = isMoving();
  if (t > _max_crying_time){
    t = 0;
  } else if (shake && !shock){
    t -= _shake_reduction;
  } else if (shock) {
    t += _shock_increment;
  } else {
    t += 1;
  }

  player.play();
  state_machine_run();

  Serial.print(state);
  Serial.print(" - Shake: "); Serial.print(shake);
  Serial.print(" - Shock: "); Serial.print(shock);
  Serial.print(" - Time: ");  Serial.println(t);

  delay(150);
}

void state_machine_run()
{
  switch(state)
  {
    case MUTE:
      if(t > _time_to_speak && t < _time_to_cry){
        baby_speak();
        state = SPEAK;
      }
      if(t > _time_to_cry){
        baby_cry();
        state = CRY;
      }
      break;

    case SPEAK:
      if(t < _time_to_speak){
        baby_mute();
        state = MUTE;
      }
      if(t > _time_to_cry){
        baby_cry();
        state = CRY;
      }
      break;

    case CRY:
      if(t < _time_to_speak){
        baby_mute();
        state = MUTE;
      }
      if(t > _time_to_speak && t < _time_to_cry){
        baby_speak();
        state = SPEAK;
      }
      break;

  }
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

void baby_mute(){
  player.setVolume(0xfe);
}

void baby_speak(){
  player.setVolume(0x6e);
}

void baby_cry(){
  player.setVolume(0x00);
}
