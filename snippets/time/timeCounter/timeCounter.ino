#include <Math.h>

unsigned long startMillis;
unsigned long currentMillis;
unsigned long timeElapsed;
unsigned long period = 10000;
void setPeriod();

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
currentMillis = millis();
startMillis = currentMillis;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  timeElapsed = currentMillis - startMillis;
  Serial.print("Current Time is:");
  Serial.print(currentMillis);
  Serial.print("ms Start Time is:");
  Serial.print(startMillis);
  Serial.print("ms Time Elapsed is: ");
  Serial.print(timeElapsed);
  Serial.print("ms Current Period is: ");
  Serial.print(period);
  Serial.println("ms");
  
  if (timeElapsed >= period){
     setPeriod(5000,10000);   
  }    
}

void setPeriod(unsigned long minPeriod, unsigned long maxPeriod){
  period = round(random(minPeriod,maxPeriod));
  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  Serial.print("Time to swith period!");
  Serial.print("the new period is ");
  Serial.println(period);
  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  startMillis = millis();
}
