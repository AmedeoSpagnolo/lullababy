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

// SerialDebug Library

// Disable all debug ? Good to release builds (production)
// as nothing of SerialDebug is compiled, zero overhead :-)
// For it just uncomment the DEBUG_DISABLED
//#define DEBUG_DISABLED true

// Disable SerialDebug debugger ? No more commands and features as functions and globals
// Uncomment this to disable it 
//#define DEBUG_DISABLE_DEBUGGER true

// Define the initial debug level here (uncomment to do it)
//#define DEBUG_INITIAL_LEVEL DEBUG_LEVEL_VERBOSE

// Disable auto function name (good if your debug yet contains it)
//#define DEBUG_AUTO_FUNC_DISABLED true

// Include SerialDebug

#include "SerialDebug.h" //https://github.com/JoaoLopesF/SerialDebug


void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.setVolume(0x00);
  _time_to_cry      = map(EASY_TO_CRY, 0, 10, 20, 100);
  _time_to_speak    = _time_to_cry - map(WARNING_BEFORE_CRY, 0, 10, 10, 20);
  _shock_increment  = map(SHOCK_SENSITIVITY, 0, 10, 2, 20);
  _shake_reduction  = map(SHAKE_EFFECTIVENESS, 0, 10, 2, 5);
  _max_crying_time  = map(MAX_CRYING_TIME, 0, 10, 100, 600);
  printA("time_to_cry: ");          printA(_time_to_cry);
  printA(" - time_to_speak: ");     printA(_time_to_speak);
  printA(" - shock_increment: ");   printA(_shock_increment);
  printA(" - shake_reduction: ");   printA(_shake_reduction);
  printA(" - _max_crying_time: ");  printlnA(_max_crying_time);

  // temp values for debug
  _time_to_cry      = 20;
  _time_to_speak    = 10;
  _shock_increment  = 12;
  _shake_reduction  = 5;
  _max_crying_time  = 30;

#ifndef DEBUG_DISABLE_DEBUGGER

  // Add Functions and global variables to SerialDebug

  // Add functions that can called from SerialDebug

  //debugAddFunctionVoid(F("function"), &function); // Example for function without args
  //debugAddFunctionStr(F("function"), &function); // Example for function with one String arg
  //debugAddFunctionInt(F("function"), &function); // Example for function with one int arg

  // Add global variables that can showed/changed from SerialDebug
  // Note: Only global, if pass local for SerialDebug, can be dangerous

  debugAddGlobalLong(F("x"), &x);
  debugAddGlobalLong(F("y"), &y);
  debugAddGlobalLong(F("z"), &z);
  debugAddGlobalLong(F("curr"), &curr);
  debugAddGlobalLong(F("prev"), &prev);
  debugAddGlobalInt(F("_time_to_cry"), &_time_to_cry);
  debugAddGlobalInt(F("_time_to_speak"), &_time_to_speak);
  debugAddGlobalInt(F("_shock_increment"), &_shock_increment);
  debugAddGlobalInt(F("_shake_reduction"), &_shake_reduction);
  debugAddGlobalInt(F("_max_crying_time"), &_max_crying_time);
  debugAddGlobalInt(F("t"), &t);
  debugAddGlobalInt(F("EASY_TO_CRY"), &EASY_TO_CRY);
  debugAddGlobalInt(F("WARNING_BEFORE_CRY"), &WARNING_BEFORE_CRY);
  debugAddGlobalInt(F("SHOCK_SENSITIVITY"), &SHOCK_SENSITIVITY);
  debugAddGlobalInt(F("SHAKE_EFFECTIVENESS"), &SHAKE_EFFECTIVENESS);
  debugAddGlobalInt(F("MAX_CRYING_TIME"), &MAX_CRYING_TIME);
  debugAddGlobalUInt8_t(F("state"), &state);

#endif // DEBUG_DISABLE_DEBUGGER

}

void loop(){

  // SerialDebug handle
  // Notes: if in inactive mode (until receive anything from serial),
  // it show only messages of always or errors level type
  // And the overhead during inactive mode is very low
  // Only if not DEBUG_DISABLED

  debugHandle();

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

  printD(state);
  printD(" - Shake: "); printD(shake);
  printD(" - Shock: "); printD(shock);
  printD(" - Time: ");  printlnD(t);

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
  int loops = 1;
  shock = false;
  //read value 50 times and output the average
  for (i=0 ; i < loops ; i++) {
    x = x + analogRead(3);
    y = y + analogRead(4);
    z = z + analogRead(5);
  }
  x = x / loops;
  y = y / loops;
  z = z / loops;
  curr = x + y + z;
  bool moving = (curr - prev) > 4;
  if ((curr - prev) > 500) shock = true;
  prev = curr;
  return moving;
}

void baby_mute(){
  player.playOne(mp3name[0]);
}

void baby_speak(){
  player.playOne(mp3name[1]);
}

void baby_cry(){
  player.playOne(mp3name[2]);
}
