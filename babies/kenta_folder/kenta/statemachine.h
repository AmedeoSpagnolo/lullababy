enum state_enum {ASLEEP,AWAKE};
char state_list[2][12] = {"SLEEP","AWAKE"};

enum substate_enum {A,B,C,D};

uint8_t state    = AWAKE; //initial state
uint8_t substate = A; //initial state
bool isBeenShakenDuringSleep = false;

void status_awake_loop(int emotionLevel);
void status_asleep_loop();

bool _isTimeToSleep(unsigned long birthday){
  long temp = (millis() - birthday) % (SLEEPTIME*1000);
  if (temp < SLEEPTIME*1000/2){
    return true;
  } else {
    isBeenShakenDuringSleep = false;
    return false;
  }
}

void state_machine_run(unsigned long birthday, int emotionLevel, bool shake){
  bool timetosleep = _isTimeToSleep(birthday);
  switch(state){
    case AWAKE:
      status_awake_loop(emotionLevel);
      if(timetosleep && !isBeenShakenDuringSleep){
        state = ASLEEP;
      }
      break;
    case ASLEEP:
      if (shake) isBeenShakenDuringSleep = true;
      status_asleep_loop();
      if(!timetosleep || isBeenShakenDuringSleep){
        state = AWAKE;
      }
      break;
  }
}

void status_awake_loop(int emotionLevel){
    int maxhappy = 200;
    if(emotionLevel > 0 && emotionLevel < maxhappy/4) {
      substate = A;
    } else if(emotionLevel > maxhappy/4 && emotionLevel < maxhappy/4*2) {
      substate = B;
    } else if (emotionLevel > maxhappy/4*2 && emotionLevel < maxhappy/4*3) {
      substate = C;
    } else if (emotionLevel > maxhappy/4*3 && emotionLevel < maxhappy) {
      substate = D;
    }
}

void status_asleep_loop(){
  
}
