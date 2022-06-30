void setup()
{
  pinMode(10,OUTPUT);
 // RED LED
  pinMode(11,OUTPUT);
 // YELLOW LED
  pinMode(12,OUTPUT);
 // GREEN LED

}

void loop()
{
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  delay(1000);
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  delay(1000);
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);

///

}
