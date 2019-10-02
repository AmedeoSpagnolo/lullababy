#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include <Math.h>
#include "param.h"
#include "statemachine.h"

char mp3name[3][15] = {"a.mp3","b.mp3","c.mp3"};
char kaoMoji_array[5][20] = {"(ToT)","(T_T)","(;_;)","('U')"};

unsigned long birthday = millis();

// Accelerometer
long prev  = 0;
bool shake = false;
bool shock = false;

//    New SI metric for feelings
//    0___________250___________500___________750___________1000
//        (ToT)         (T_T)         (;_;)         ('U')
//
int emotionLevel = 80;
char* kaoMoji = kaoMoji_array[0];

// DEBUG
bool DEBUG = false;
bool ACCELEROMETER_DEBUG = false;

void check_physical_love(); //previously bool isMoving()
void update_feelings(); //use both in awake and asleep

void setup(){
  Serial.begin(9600);

  //music shield
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.setVolume(0xfe);
  player.playOne(mp3name[2]);
}

void loop(){
  check_physical_love(); //update shake and shock
  update_feelings();
  state_machine_run(birthday);
  Serial.print("State: ");    Serial.print(state);
  Serial.print(" - EmotionLevel: "); Serial.print(emotionLevel);
  Serial.print(kaoMoji);
  Serial.print(" - Shake: "); Serial.print(shake);
  Serial.print(" - Shock: "); Serial.println(shock);
  delay(50);
}

//accelerometer. Updates Shock and Shake.
void check_physical_love(){
  int i;
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
    emotionLevel += 1; //feelings are obviously linear
    if (emotionLevel > 999){
      emotionLevel = 995;  // i feel like it might get stuck 999
    }
  } else if (!shake && !shock){
    emotionLevel -= 1;
    if (emotionLevel < 0){
      emotionLevel = 5; // i feel like it might get stuck if 0
    }
  } else if (shock){ //if shock, make it in cry state
    emotionLevel = 15;
  }
}

void status_awake_loop(){
  // led pulse normal,
  // bad - good indicatior results to high - zero volume
  switch(emotionLevel){
    case 0 ... 250:
      kaoMoji = kaoMoji_array[0];
      //player.setVolume(0x00); // 0
      break;
    case 251 ... 500:
      kaoMoji = kaoMoji_array[1];
//      player.setVolume(0x50); //80
      break;
    case 501 ... 750:
      kaoMoji = kaoMoji_array[2];
//      player.setVolume(0xa0); //160
      break;
    case 751 ... 1000:
      kaoMoji = kaoMoji_array[3];
//      player.setVolume(0xfe); //
      break;
  }
}
