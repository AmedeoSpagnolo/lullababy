#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include <Math.h>
#include "kumoParam.h"


enum state_enum {MUTE,SPEAK,CRY};
char mp3name[3][15] = {"a.mp3","b.mp3","c.mp3"};

long x = 0;
long y = 0;
long z = 0;
long curr = 0;
long prev = 0;
bool isMoving();

//time counter
//int t = 0;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long timeElapsed;
unsigned long mutePeriod;
unsigned long speakingPeriod;
unsigned long cryingPeriod;
unsigned long printPeriod;


//period bounds
unsigned long MAX_CRYING_PERIOD = 10000;
unsigned long MIN_CRYING_PERIOD = 6000;
unsigned long MAX_SPEAKING_PERIOD = 10000;
unsigned long MIN_SPEAKING_PERIOD= 6000;
unsigned long MAX_MUTE_PERIOD = 10000;
unsigned long MIN_MUTE_PERIOD= 6000;

unsigned long MAX_SHOCK_SENSITIVITY = 1000;
unsigned long MIN_SHOCK_SENSITIVITY = 999;
unsigned long MAX_SHAKE_EFFECTIVENESS = 1000;
unsigned long MIN_SHAKE_EFFECTIVENESS = 999;



// unsigned long _time_to_cry;
// unsigned long _time_to_speak;
unsigned long _shock_increment;
unsigned long _shake_reduction;
unsigned long _max_crying_time;

bool shake = false;
bool shock = false;

uint8_t state = MUTE;
bool DEBUG = true;

//functions

void baby_enter_speak();
void baby_enter_mute();
void baby_enter_cry();
unsigned long setPeriod(unsigned long minPeriod, unsigned long maxPeriod);
void setMutePeriod();
void setSpeakingPeriod();
void setCryingPeriod();
void baby_exit_speak();
void baby_exit_mute();
void baby_exit_cry();


void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.setVolume(0xfe);
  player.playOne(mp3name[2]);
  // _time_to_cry      = map(EASY_TO_CRY, 0, 10, 5000, 10000);
  // _time_to_speak    = _time_to_cry - map(WARNING_BEFORE_CRY, 0, 10, 10, 20);
  // _shock_increment  = map(SHOCK_SENSITIVITY, 0, 10, 2, 20);
  // _shake_reduction  = map(SHAKE_EFFECTIVENESS, 0, 10, 2, 5);
  // _max_crying_time  = map(MAX_CRYING_TIME, 0, 10, 100, 600);

  //set time
  currentMillis = millis();
  startMillis = currentMillis;

  setSpeakingPeriod();
  setMutePeriod();
  setMutePeriod();//put at end so that printPeriod becomes first period
  //_time_to_cry      = map(EASY_TO_CRY, 0, 10, 5000, 10000);
  //  _time_to_speak    = _time_to_cry - map(WARNING_BEFORE_CRY, 0, 10, 10, 20);

  // _shock_increment  = 1000;
  // _shake_reduction  = 1000;

  //_shock_increment  = random(MIN_SHOCK_SENSITIVITY, MAX_SHOCK_SENSITIVITY);
  //_shake_reduction  = random(MIN_SHAKE_EFFECTIVENESS, MAX_SHAKE_EFFECTIVENESS);


  //_max_crying_time  = map(MAX_CRYING_TIME, 0, 10, 100, 600);
  // Serial.print("time_to_cry: ");          Serial.print(_time_to_cry);
  // Serial.print(" - time_to_speak: ");     Serial.print(_time_to_speak);
  // Serial.print(" - shock_increment: ");   Serial.print(_shock_increment);
  // Serial.print(" - shake_reduction: ");   Serial.print(_shake_reduction);
  // Serial.print(" - _max_crying_time: ");  Serial.println(_max_crying_time);

  // temp values for debug
//  _time_to_cry      = 20;
//  _time_to_speak    = 10;
//  _shock_increment  = 12;
//  _shake_reduction  = 5;
//  _max_crying_time  = 30;
}

void loop(){
  //shake = isMoving();
  updateTime();
  shake = isMoving();

  if (DEBUG){
   Serial.print("State:");
   Serial.print(state);
   Serial.print("Current Time is:");
   Serial.print(currentMillis);
   Serial.print("ms Start Time is:");
   Serial.print(startMillis);
   Serial.print("ms Time Elapsed is: ");
   Serial.print(timeElapsed);
   Serial.print("ms Current Period is: ");
   Serial.print(printPeriod);
   Serial.print("ms");
   Serial.print(" ");
   Serial.print(shake);
}

  player.play();
  state_machine_run();
}

void state_machine_run()
{
  switch(state)
  {
    case MUTE:
      if(timeElapsed > mutePeriod && !shock){
        baby_exit_mute();
        baby_enter_speak();
      } else if(shock){
        baby_exit_mute();
        baby_enter_cry();
      } else if (!shock && isMoving()){
        mutePeriod += 100; //add SHAKE_EFFECTIVENESS
      }
      break;

    case SPEAK:
      baby_while_speak();
      if(timeElapsed > speakingPeriod){
        baby_exit_speak();
        baby_enter_cry();
      } if else
      break;

    case CRY:
      baby_while_cry();
      if(timeElapsed > cryingPeriod){
        baby_exit_cry();
        baby_enter_mute();
      }
      break;

  }
}

bool isMoving(){
  int i;
  long x = 0;
  long y = 0;
  long z = 0;
  long delta;
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
  delta = abs(curr-prev);
  Serial.print("the Movement value is");
  Serial.print(delta);
  bool moving = (delta) > 4;
  if (delta > 250){
  shock= true;
  }
  Serial.print(" shock");
  Serial.println(shock);
  prev = curr;
  return moving;
}

void baby_enter_mute(){
  startMillis = millis();
  player.setVolume(0xfe);
  mutePeriod = round(random(MIN_MUTE_PERIOD,MAX_MUTE_PERIOD));
}

void baby_enter_speak(){
  state = SPEAK;
  startMillis = millis();
  speakingPeriod = round(random(MIN_SPEAKING_PERIOD,MAX_SPEAKING_PERIOD);
  player.setVolume(0x6e);
}

void baby_enter_cry(){
  state = CRY;
  startMillis = millis();
  cryingPeriod = round(random(MIN_CRYING_PERIOD, MAX_CRYING_PERIOD);
  player.setVolume(0x00);
}

void updateTime(){
  currentMillis = millis();
  timeElapsed = currentMillis - startMillis;
}

void baby_exit_speak(){


}
void baby_exit_mute(){


}
void baby_exit_cry(){
  if (DEBUG){
     Serial.println("baby_exit_cry");
  }
}
void baby_while_cry(){
  // every loop change volume
  if(timeElapsed < cryingPeriod - 1000){
    baby_cry_normal();
 } else if(timeElapsed > cryingPeriod - 1000){
   baby_cry_softer();
 }

 // every loop update cryingPeriod
 if (!shock && isMoving()){
   cryingPeriod -= 1000; //add SHAKE_EFFECTIVENESS
 } else if (shock){
   cryingPeriod += 10000; //add SHAKE_EFFECTIVENESS
 }
}


// unsigned long setPeriod(unsigned long minPeriod, unsigned long maxPeriod){
//   unsigned long output_duration;
//   output_duration = round(random(minPeriod,maxPeriod));
//   return output_duration;
//   // Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
//   // Serial.print("Time to swith period!");
//   // Serial.print("the new period is ");
//   // Serial.println(period);
//   // Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
//   // startMillis = millis();
//
// }

// void setMutePeriod(){
//
// }
// void setSpeakingPeriod(){
//   speakingPeriod = round(random
//   printPeriod = speakingPeriod;
// }
// void setCryingPeriod(){
//   cryingPeriod = setPeriod
//   printPeriod = cryingPeriod;
// }
