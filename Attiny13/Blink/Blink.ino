
void setup() {
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);              // wait for a second
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  delay(250);              // wait for a second
}
