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
  private:
    int shake;
    int shock;
};

#endif
