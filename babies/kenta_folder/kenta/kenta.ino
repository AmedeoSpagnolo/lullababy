#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include <Math.h>
#include "param.h"

//functions
void state_machine();
void updateTime();

enum state_enum {ASLEEP,AWAKE};

char mp3name[3][15] = {"a.mp3","b.mp3","c.mp3"};

//variables
//3600 s in an hour 3600000 ms in an hour
unsigned long current_time;
unsigned long start_time;
unsigned long time_elapsed;

long prev; //Accelerometer

int millifeels; //new SI metric for feelings
// general reference range from 0 to 1000.
// 0 - 250: RAWR
// 250 - 500: BOO
// 500 - 750: meh
// 750 - 1000: Playful
// 0_______________________________________________1000
// (ToT)         (T_T)           (;_;)            ('U')
//unsigned long wakeup_intervals [];

uint8_t state = AWAKE; //initial state


//Booleans
bool isAsleep = false;
bool DEBUG = false;
bool ACCELEROMETER_DEBUG = false;
bool isTimeSleep();

bool shake = false;
bool shock = false;

void check_physical_love(); //previously bool isMoving()
void update_feelings(); //use both in awake and asleep

void setup(){
  Serial.begin(9600);
  current_time = millis(); // set timer
  start_time = current_time;
  millifeels = 80; //set state to be 80
  prev = 0;

  //music shield
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.setVolume(0xfe);
  player.playOne(mp3name[2]);
}

void loop(){
  updateTime(); // figure out time stamp
  check_physical_love(); //update shake and shock
  update_feelings();
  state_machine();
}

void state_machine_run(){ //Logic for Awake and Asleep states
  switch(state){
    case AWAKE:
      status_awake_loop();
      if(isTimeToSleep()){
        status_awake_exit();
        status_asleep_enter();
      }
      break;

    case ASLEEP:
      status_asleep_loop();
      if(!isTimeToSleep()){
        status_asleep_exit();
        status_awake_enter();
      }
      break;
  }
}

// Check time and schedule
//
void updateTime(){
  current_time = millis();
  time_elapsed = current_time - start_time;
}

bool isTimeToSleep(){
  return false;
}


// Awake functions
//
void status_awake_enter(){
return true;
}

void status_awake_loop(){
  // led pulse normal,
  // bad - good indicatior results to high - zero volume
  switch(millifeels){
    case 0 ... 250:
      player.setVolume(0x00); // 0
      break;
    case 251 ... 500:
      player.setVolume(0x50); //80
      break;
    case 501 ... 750:
      player.setVolume(0xa0); //160
      break;
    case 751 ... 1000:
      player.setVolume(0xfe); //
      break;
  }
}

void status_awake_exit(){
return true;
}

//asleep functions

void status_asleep_enter(){
return true;
}

void status_asleep_exit(){
  return true;
}

void status_asleep_loop(){
  // led pulse slow
  return true;
}



//accelerometer. Updates Shock and Shake. prev. isMoving().
void check_physical_love(){
  int i; //initialize local variables
  long curr;
  long delta;
  long x = 0;
  long y = 0;
  long z = 0;

  //read value 50 times and output the average
  for (i=0 ; i < 50 ; i++) {
    x = x + analogRead(3);
    y = y + analogRead(4);
    z = z + analogRead(5);
  }
  x = (x / 50);   y = (y / 50);  z = (z / 50);
  curr = x + y + z;
  delta = abs(curr-prev); // compare with last sum(x,y,z)

  //update shake and shock and prev
  shake = (delta > 4);
  shock = (delta > 400);
  prev = curr;

  //debug
  if (ACCELEROMETER_DEBUG){
    Serial.print("the Movement value is");
    Serial.print(delta);
    Serial.print(" shock");
    Serial.println(shock);
  }
}

void update_feelings(){
  if (shake && !shock){
    millifeels += 1; //feelings are obviously linear
    if (millifeels > 999){
      millifeels = 995;  // i feel like it might get stuck 999
    }
  } else if (!shake && !shock){
    millifeels -= 4;
    if (millifeels < 0){
      millifeels = 5; // i feel like it might get stuck if 0
    }
  } else if (shock){ //if shock, make it in cry state
    millifeels = 15;
  }
}
