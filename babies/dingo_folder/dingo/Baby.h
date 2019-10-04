#ifndef Baby_h
#define Baby_h

#include "Arduino.h"

class Baby
{
  public:
    Baby();
    void alive();
    void sleep();
    void awake();
    void cry();
    void speak();
    void mute();
    int state;
    int happyness;
    bool isCrying;
    bool isSpeaking;
    bool isMute;
    int shake;
    int shock;
  private:
    bool isBeenShaken;
    unsigned long birthday;
    bool _timetosleep();
    void _go_to_sleep();
    void _wake_up();
    void _updateEmotion();
    void _check_if_shaken();
    void _triggerEmotion();
};

#endif
