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

int centifeels; //new SI metric for feelings
// general reference range from 0 to 1000.
// 0 - 25: RAWR
// 25 - 50: BOO
// 50 - 75: meh
// 75 - 100: Playful

unsigned long [];

uint8_t state = AWAKE; //initial state


//Booleans
bool isAsleep = false;
bool DEBUG = false
bool ACCELEROMETER_DEBUG = false
bool isTimeSleep();

bool shake = false;
bool shock = false;

void check_physical_love(); //previously bool isMoving()

void setup(){
  Serial.begin(9600);
  current_time = millis(); // set timer
  start_time = current_time;
  emotional_value = 80; //set state to be 40
  prev = 0;
}

void loop(){
  updateTime();
  state_machine();

  //delay(80);

}

void state_machine_run(){
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

//check time and schedule

void updateTime(){
  current_time = millis();
  time_elapsed = current_time - start_time;
}

bool isTimeToSleep(){
  return false;
}


//awake functions

void status_awake_enter(){
return true;
}

void status_awake_loop(){
  // led pulse normal, Add or subtract from emotional ,indicator
  // bad - good indicatior results to high - zero volume
  check_physical_love(); // update shake and shock values

  if (shake && !shock){


  } else if (){


  }


  return true;
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

//accelerometer

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

  //is it shaking/shocking or nah?
  bool isShake = (delta) > 4;
  bool isShock = (delta) > 400;

  //update shake and shock and prev
  //ASK AME IF ITS REDUNDANT
  shake = isShake;
  shock = isShock;
  prev = curr

  if (ACCELEROMETER_DEBUG){
  Serial.print("the Movement value is");
  Serial.print(delta);
  Serial.print(" shock");
  Serial.println(shock);
}

}
