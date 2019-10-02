enum state_enum {ASLEEP,AWAKE};

uint8_t state = AWAKE; //initial state

void status_awake_enter(){}
void status_awake_exit(){}
void status_awake_loop(){}
void status_asleep_enter(){}
void status_asleep_exit(){}
void status_asleep_loop(){}

bool _isTimeToSleep(unsigned long birthday){
  long temp = (millis() - birthday) % 30000;
  if (temp < 1000){
    return true;
  } else {
    return false;
  }
}

void state_machine_run(unsigned long birthday, int emotionLevel){
  bool timetosleep = _isTimeToSleep(birthday);
  switch(state){
    
    case AWAKE:
      status_awake_loop();
      if(timetosleep){
        status_awake_exit();
        status_asleep_enter();
        state = ASLEEP;
      }
      break;

    case ASLEEP:
      status_asleep_loop();
      if(!timetosleep){
        status_asleep_exit();
        status_awake_enter();
        state = AWAKE;
      }
      break;
  }
}
