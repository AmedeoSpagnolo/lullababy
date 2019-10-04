long prev  = 0;
bool shake = false;
bool shock = false;

//accelerometer. Updates Shock and Shake.
void check_physical_love(){
  int i;
  long curr;
  long delta;
  long x = 0;
  long y = 0;
  long z = 0;
  int t = 50; // read value 50 times and output the average
  for (i=0 ; i < t ; i++) {
    x = x + analogRead(3);
    y = y + analogRead(4);
    z = z + analogRead(5);
  }
  x = (x/t);   y = (y/t);  z = (z/t);
  curr = x + y + z;
  delta = abs(curr-prev); // compare with last sum(x,y,z)

  // Update shake and shock and prev
  shake = (delta > SHAKE_SENSIBILITY); // 4
  shock = (delta > map(SHOKE_SENSIBILITY,0,10,200,1000)); // 400
  prev = curr;
}
