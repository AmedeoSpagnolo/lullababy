#include <Math.h>

unsigned long startMillis;
unsigned long currentMillis;
unsigned long timeElapsed;
unsigned long period;
unsigned long setPeriod(unsigned long minPeriod, unsigned long maxPeriod);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
currentMillis = millis();
startMillis = currentMillis;
period = setPeriod(5000,10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  timeElapsed = currentMillis - startMillis;
  Serial.print("(");
  Serial.print(startMillis);
  Serial.print(" - ");
  Serial.print(startMillis + period);
  Serial.print(")");
  Serial.print(": ");
  Serial.println(currentMillis);
//  Serial.println("ms Start Time is:");

  
//  Serial.print(timeElapsed);
//  Serial.print("ms Current Period is: ");

//  Serial.println("ms");

  if (timeElapsed >= period){
    period = setPeriod(5000,10000);
  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  Serial.print("Time to swith period!");
  Serial.print("the new period is ");
  Serial.println(period);
  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  }
}

unsigned long setPeriod(unsigned long minPeriod, unsigned long maxPeriod){
  unsigned long output_period;  
  output_period = round(random(minPeriod,maxPeriod));
  startMillis = millis();
  return output_period;
}
