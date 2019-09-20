int analogPin = A1;
int val = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);
  val = map(val, 920, 880, 0, 10);
  Serial.println(val);
  delay(150);
}
