#include "Baby.h"
#include "Arduino.h"
#include "Eyes.h"
#include "Movement.h"

Eyes eyes = Eyes();
Movement acc = Movement();

enum state_enum {ASLEEP,AWAKE};

int MAXHAPPY = 1000;

Baby::Baby(){
  int shake = 0;
  int shock = 0;
  int happyness = 0; // 0 - 10
  acc.pins(3,4,5); // x, y, z
  acc.shockSensibility(5); // 0 - 10
  acc.shakeSensibility(5); // 0 - 10
  eyes.pins(3,6);
  uint8_t state = AWAKE;
  bool isBeenShocked = false;
  unsigned long birthday = millis();
  bool isCrying   = false;
  bool isSpeaking = false;
  bool isMute     = false;
  int SLEEPTIME;
}

void Baby::opt(int sleepTime){
  SLEEPTIME = sleepTime;
}

void Baby::alive(){
  switch(state){
    case AWAKE:
      awake();
      if(_timetosleep()){
        _go_to_sleep();
        state = ASLEEP;
      }
      break;
    case ASLEEP:
      sleep();
      if(!_timetosleep()){
        _wake_up();
        state = AWAKE;
      }
      break;
  }
}

bool Baby::_timetosleep(){
  long age = millis() - birthday;
  long temp = age % (SLEEPTIME*1000);
  Serial.print(SLEEPTIME); Serial.print(" - ");
  Serial.print(temp); Serial.print(" - ");
  if (temp < SLEEPTIME*1000/2 && !isBeenShocked){
    return true;
  } else if (temp >= SLEEPTIME*1000/2){
    isBeenShocked = false;
    return false;
  } else {
    return false;
  }
}

void Baby::_go_to_sleep(){
  // Do somethin when he goes to sleep
}

void Baby::_wake_up(){
  // Do somethin when he wakes up
}

void Baby::_updateEmotion(){
  acc.updateValues();
  shock = acc.shock();
  shake = acc.shake();
  if (acc.shock()){
    happyness = 0;
  } else if (acc.shake() && (happyness <= MAXHAPPY)){
    happyness += 4;
  } else if (happyness >= 0){
    happyness -= 1;
  }
}

void Baby::_triggerEmotion(){
  isCrying   = false;
  isSpeaking = false;
  isMute     = false;
  if(happyness < MAXHAPPY/3) {
    cry();
  } else if(happyness >= MAXHAPPY/3 && happyness < MAXHAPPY/3*2) {
    speak();
  } else if (happyness >= MAXHAPPY/3*2) {
    mute();
  }
}

void Baby::_check_if_shocked(){
  acc.updateValues();
  shock = acc.shock();
  shake = acc.shake();
  if (shock) isBeenShocked = true;
}

void Baby::sleep(){
  _check_if_shocked();
  eyes.close();
}

void Baby::awake(){
  _updateEmotion();
  _triggerEmotion();
  eyes.open();
}

void Baby::cry(){
  isCrying = true;
  // play crying mp3
}

void Baby::speak(){
  isSpeaking = true;
  // play speking mp3
}

void Baby::mute(){
  isMute = true;
  // stop audio
}
