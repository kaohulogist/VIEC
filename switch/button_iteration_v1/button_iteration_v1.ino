#define LED_PIN 9
#define BUTTON_PIN 13
byte lastButtonState = LOW;
byte ledState = LOW;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}
void loop() {
  byte buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      
      ledState = (ledState == HIGH) ? LOW: HIGH;
      digitalWrite(LED_PIN, ledState);
      Serial.print("Button Press");
    }
  }
}
