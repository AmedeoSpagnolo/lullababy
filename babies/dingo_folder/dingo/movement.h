#ifndef Movement_h
#define Movement_h

#include "Arduino.h"

class Movement
{
  public:
    Movement();
    void updateValues();
    void shockSensibility(int);
    void shakeSensibility(int);
    void pins(int,int,int);
    bool shake();
    bool shock();
  private:
    int _pin_x;
    int _pin_y;
    int _pin_z;
    long _prev;
    bool _shake;
    bool _shock;
    int _shake_sensibility;
    int _shock_sensibility;
};

#endif
