
#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>

long x = 0;
long y = 0;
long z = 0;

long prev = 0;
bool shake = false;

void setup(void)
{
  Serial.begin(9600);
  player.begin();
  player.setPlayMode(PM_REPEAT_ONE);
  player.playOne("cry.mp3");
}
void loop(){

  player.play();
  player.setVolume(0x00);
  player.play();

  int i;
  long x,y,z;

  //read value 50 times and output the average
  x=y=z=0;
  for (i=0 ; i < 50 ; i++) {
    x = x + analogRead(3) ; // Ｘ軸
    y = y + analogRead(4) ; // Ｙ軸
    z = z + analogRead(5) ; // Ｚ軸
  }
  x = x / 50 ;
  y = y / 50 ;
  z = z / 50 ;
  shake = (x + y + z - prev) > 10;
  int rotateX = (x-277)/2.48 - 90; //formula to determine angle
  Serial.print("X:") ;
  Serial.print(rotateX) ;
  int rotateY = (y-277)/2.48 - 90;
  Serial.print(" Y:") ;
  Serial.print(rotateY) ;
  int rotateZ = (z-277)/2.48 - 90;
  Serial.print(" Z:") ;
  Serial.print(rotateZ) ;
  Serial.print(" Shakes:");
  Serial.println(shake);
  prev = x + y + z;
  if (shake > 0){
    player.setVolume(0xfe);
    delay(10000);
  }
  delay(250);
}
