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
    bool shake();
    bool shock();
    void pins(int,int,int);
  private:
    int _pin_x;
    int _pin_y;
    int _pin_z;
    bool _shake;
    bool _shock;
    long _prev;
    int _shake_sensibility;
    int _shock_sensibility;
};

#endif
