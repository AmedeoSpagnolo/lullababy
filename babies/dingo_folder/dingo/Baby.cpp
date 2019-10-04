#include "Baby.h"
#include "Arduino.h"
#include "Eyes.h"
#include "Movement.h"

Eyes eyes = Eyes();
Movement acc = Movement();

enum state_enum {ASLEEP,AWAKE};

Baby::Baby(){
  int shake = 0;
  int shock = 0;
  acc.pins(3,4,5); // x, y, z
  acc.shockSensibility(5); // 0 - 10
  acc.shakeSensibility(5); // 0 - 10
  eyes.pins(3,6);
  uint8_t state = AWAKE;
}

void Baby::alive(){
  switch(state){
    case AWAKE:
      awake();
      if(timetosleep && !isBeenShakenDuringSleep){
        state = ASLEEP;
      }
      break;
    case ASLEEP:
      sleep();
      if(!timetosleep || isBeenShakenDuringSleep){
        state = AWAKE;
      }
      break;
  }
}

void Baby::_updateEmotion(){
  if(emotionLevel > 0 && emotionLevel < MAXHAPPY/3) {
    cry();
  } else if(emotionLevel > MAXHAPPY/3 && emotionLevel < MAXHAPPY/3*2) {
    speak();
  } else if (emotionLevel > MAXHAPPY/3*2 && emotionLevel < MAXHAPPY) {
    mute();
  }
}

void Baby::sleep(){
  acc.updateValues();
  shake = acc.shake();
  shock = acc.shock();
  eyes.close();
}

void Baby::awake(){
  _updateEmotion();
  acc.updateValues();
  shake = acc.shake();
  shock = acc.shock();
  eyes.open();
}

void Baby::cry(){
  // play crying mp3
}

void Baby::speak(){
  // play speking mp3
}

void Baby::mute(){
  // stop audio
}
