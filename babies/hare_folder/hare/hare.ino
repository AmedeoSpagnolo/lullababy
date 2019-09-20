enum State_enum {SILENT,CALM,CRY};
enum Sensors_enum {NONE, ACC};

void state_machine_run();
void baby_silent();
void baby_calm();
void baby_cry();

int time = 0;
const int MAX_SILENT        = 34543212;
const int MAX_CALM          = 34543212;
const int MAX_CRY           = 34543212;
const int CALM_MOVING_TIME  = 34543212;
const int CRY_MOVING_TIME   = 34543212;


uint8_t state = SILENT;

void setup(){
}

void loop(){
  time += 1;
  state_machine_run();
  delay(10);
}

void state_machine_run(uint8_t sensors)
{
  switch(state)
  {
    case SILENT:
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      if(time > MAX_SILENT){
        time = 0;
        baby_calm();
        state = CALM;
      }
      break;

    case CALM:
      if(time > MAX_CALM){
        time = 0;
        baby_cry();
        state = CRY;
      }
      if(isMoving()){
        baby_calm_moving();
        state = CALM_MOVING;
      }
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      break;

    case CALM_MOVING:
      if(!isMoving()){
        baby_calm();
        state = CALM;
      }
      if(time > CALM_MOVING_TIME){
        baby_silent();
        state = SILENT;
      }
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      break;

    case CRY:
      if(time > MAX_CRY){
        time = 0;
        baby_silent();
        state = SILENT;
      }
      if(isMoving()){
        baby_calm_moving();
        state = CRY_MOVING;
      }
      break;

    case CRY_MOVING:
      if(!isMoving()){
        baby_cry();
        state = CRY;
      }
      if(time > CRY_MOVING_TIME){
        baby_calm();
        state = CALM_MOVING;
      }
      if(bigMovement()){
        baby_cry();
        state = CRY;
      }
      break;

  }
}

void baby_silent()
{
}
void baby_calm()
{
  player.play("light1.mp3");
}
void baby_cry()
{
  player.play("heavy1.mp3");
}
void bigMovement()
{
}
void isMoving()
{
}
