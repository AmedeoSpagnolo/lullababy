// https://www.deviceplus.com/how-tos/arduino-guide/entry017/

void setup()
{
  Serial.begin(9600); //Initialize serial monitor
}

void loop()
{
  int i;
  long x,y,z;
  //read value 50 times and output the average
  x=y=z=0;
  for (i=0; i < 50; i++) {
  x = x + analogRead(3); // Ｘ軸
  y = y + analogRead(4); // Ｙ軸
  z = z + analogRead(5); // Ｚ軸
  }
  x = x / 50;
  y = y / 50;
  z = z / 50;
  int rotateX = (x-277)/2.48 - 90; //formula to determine angle
  Serial.print("X:");
  Serial.print(x);
  Serial.print(" ");
  Serial.print(rotateX);
  int rotateY = (y-277)/2.48 - 90;
  Serial.print(" Y:");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(rotateY);
  int rotateZ = (z-277)/2.48 - 90;
  Serial.print(" Z:");
  Serial.print(z);
  Serial.print(" ");
  Serial.println(rotateZ);
  delay(50);
}
