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

//read value 50 times and output the average
  for (i=0 ; i < 50 ; i++) {
    x = x + analogRead(3);
    y = y + analogRead(4);
    z = z + analogRead(5);
  }
  x = (x / 50);   y = (y / 50);  z = (z / 50);
  curr = x + y + z;
  delta = abs(curr-prev); // compare with last sum(x,y,z)

//update shake and shock and prev
  shake = (delta > 4);
  shock = (delta > 400);
  prev = curr;
}
