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
  Serial.begin(9600);
  
  initalReadingPosition();
  failingRedLED();
  connectYellowLED();
  runningGreenLED();
}

void initalReadingPosition(){
  Serial.print("Initaling Status ");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print(" Reding Position red+yellow+green LED blinking");
  Serial.println("");
  delay(500);
  
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  delay(1000);

}
void failingRedLED(){
  Serial.print("Failing Status ");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print(" red LED blinking");
  Serial.println("");
  delay(500);
  
  digitalWrite(10, HIGH);
  delay(2000);
  digitalWrite(10, LOW);
  delay(2000);
}
void connectYellowLED(){
  Serial.print("Conneting Status ");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print(" yellow LED blinking");
  Serial.println("");
  delay(500);
  
  digitalWrite(11, HIGH);
  delay(2000);
  digitalWrite(11, LOW);
  delay(2000);
}
void runningGreenLED(){
  Serial.print("Running Status ");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print("-");
  delay(500);
  Serial.print(" green LED blinking");
  Serial.println("");
  delay(500);
  digitalWrite(12, HIGH);
  delay(2000);
  digitalWrite(12, LOW);
  delay(2000);
}
