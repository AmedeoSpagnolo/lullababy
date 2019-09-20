int analogPin = 0;

void setup()
{
 Serial.begin(9600);          //  setup serial
}

void loop()
{
 Serial.print("Analog: ");
 Serial.print(getValue());
 Serial.print(" Digital: ");
 Serial.println(digitalRead(digitalPin));
 delay(1000);
}

float getValue() {
 val = analogRead(analogPin);
 // need some calca to HR%
 return val;
}
