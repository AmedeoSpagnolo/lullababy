#ifndef Eyes_h
#define Eyes_h

#include "Arduino.h"

class Eyes
{
  public:
    Eyes();
    void open();
    void close();
    void pins(int,int);
  private:
    int eye_right;
    int eye_left;
};

#endif
