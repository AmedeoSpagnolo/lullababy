void state_machine_run()
{
  switch(state)
  {
    case MUTE:
      if(timeElapsed > mutePeriod && !shock){
        baby_exit_mute();
        baby_enter_speak();
      } else if(shock){
        baby_exit_mute();
        baby_enter_cry();
      } else if (!shock && isMoving()){
        mutePeriod += 100; //add SHAKE_EFFECTIVENESS
      }
      break;

    case SPEAK:
      baby_while_speak();
      if(timeElapsed > speakingPeriod){
        baby_exit_speak();
        baby_enter_cry();
      }
      break;

    case CRY:
      baby_while_cry();
      if(timeElapsed > cryingPeriod){
        baby_exit_cry();
        baby_enter_mute();
      }
      break;

  }
}
