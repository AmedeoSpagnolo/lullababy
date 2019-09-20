// https://www.deviceplus.com/how-tos/arduino-guide/entry017/

void setup()
{
  Serial.begin(9600); //Initialize serial monitor
}

void loop()
{
  long x , y , z ;
  x = y = z = 0 ;
  x = analogRead(3) ; // Ｘaxis
  y = analogRead(4) ; // Ｙaxis
  z = analogRead(5) ; // Ｚaxis
  Serial.print("X:") ;
  Serial.print(x) ;
  Serial.print(" Y:") ;
  Serial.print(y) ;
  Serial.print(" Z:") ;
  Serial.println(z) ;
  delay(50) ;
}
