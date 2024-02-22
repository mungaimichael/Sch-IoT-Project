void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH); // "HIGH" should be in uppercase
  delay(2000);
  digitalWrite(2, LOW);
  delay(1500);
}
