#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include <Math.h>
#include "param.h"
#include "statemachine.h"
#include "movement.h"

char mp3name[3][15] = {"a.mp3","b.mp3","c.mp3"};
char kaoMoji_array[5][20] = {"(ToT)","(T_T)","(;_;)","('U')"};
char* kaoMoji = kaoMoji_array[0];

unsigned long birthday = millis();

int emotionLevel = 80;

int eye_right = 3;
int eye_left  = 6;

// DEBUG
bool DEBUG = true;

void setup(){
  Serial.begin(9600);
  player.begin();
  player.keyDisable();
  player.setPlayMode(PM_REPEAT_ONE);
  player.setVolume(0xfe);
  player.playOne(mp3name[2]);
  pinMode(eye_right, OUTPUT);
  pinMode(eye_left, OUTPUT);
}

void loop(){
  player.play();
  check_physical_love(); // Update shake and shock
  state_machine_run(birthday,emotionLevel,shake);
  switch(state){
    case AWAKE:
      digitalWrite(eye_right, HIGH);
      digitalWrite(eye_left, HIGH);
      update_awake_feelings();
     switch (substate) {
       case A:
         player.setVolume(0x00); // 0
         break;
       case B:
         player.setVolume(0x50); // 80
         break;
       case C:
         player.setVolume(0xa0); // 160
         break;
       case D:
         player.setVolume(0xfe); // 254
         break;
     }
      if (DEBUG){
        Serial.print(state_list[state]); Serial.print(" ");
        Serial.print(kaoMoji_array[substate]); Serial.print(" ");
        Serial.print(" - EmotionLevel: "); Serial.print(emotionLevel);
        Serial.print(" - Substate: "); Serial.print(substate);
        Serial.print(" - Shake: "); Serial.print(shake);
        Serial.print(" - Shock: "); Serial.println(shock);
      }
      break;
    case ASLEEP:
      digitalWrite(eye_right, LOW);
      digitalWrite(eye_left, LOW);
      player.setVolume(0xfe); // 254
      if (DEBUG){
        Serial.print(state_list[state]);
        Serial.print(" - Shock: "); Serial.println(shock);
      }
      break;
  }
  delay(50);
}

void update_awake_feelings(){
  if (shake && !shock){
    emotionLevel += 1; //feelings are obviously linear
    if (emotionLevel > MAXHAPPY){
      emotionLevel = MAXHAPPY - 5;  // i feel like it might get stuck 999
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
