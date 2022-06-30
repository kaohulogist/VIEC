//Import all required libraries
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
const int MPU6050_addr = 0x68;
int16_t AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;

#define trigPin 8
#define echoPin 7
Adafruit_BMP085 bmp;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

#define BUTTON_PIN 13
#define wLEDs_PIN 8
byte lastButtonState = LOW;
byte ledState = LOW;
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

//Initialize the variables
int bitVal;
String stringBit;
String stringBinary;
long binaryNumber;
int decimalNumber;
float duration;
float distance_cm;
float distance_in;

/*
//Prints the HEC5 logo on OLED Display
static const uint8_t PROGMEM logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xa3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0xb1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x01, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18, 0x00, 0x01, 0x00, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xff, 0xf0, 0x02, 0x00, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0xff, 0x60, 0x04, 0x00, 0x75, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xff, 0x20, 0x08, 0x00, 0xf3, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0xff, 0x00, 0x10, 0xc0, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xcf, 0x03, 0x00, 0x24, 0x61, 0xfd, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xdf, 0x47, 0x80, 0x40, 0x30, 0xfd, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x9f, 0x03, 0x81, 0xe0, 0x1c, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x06, 0x9f, 0xe7, 0x01, 0xf8, 0x1f, 0x7e, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x8f, 0xff, 0x01, 0x38, 0x3f, 0x7e, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x03, 0xf4, 0x27, 0x7f, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x07, 0xff, 0xff, 0x7f, 0x38, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x6c, 0x05, 0xff, 0xf3, 0x7f, 0x38, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0b, 0xfe, 0xfb, 0xff, 0x28, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x13, 0xff, 0xf8, 0xff, 0xb8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x23, 0xbf, 0xfd, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x03, 0x7f, 0xf5, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x04, 0x07, 0x7f, 0xf5, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x7f, 0xfd, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x7f, 0xf1, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x7e, 0xe0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x03, 0x7f, 0xe0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x17, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x7e, 0x15, 0xc0, 0xff, 0x70, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x78, 0xfd, 0xc0, 0xcf, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0xf0, 0xfd, 0x80, 0x82, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x01, 0xc0, 0xfe, 0xd0, 0xc0, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x80, 0xff, 0xe0, 0xe4, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x01, 0xff, 0xe3, 0xcd, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x01, 0x83, 0xff, 0xf3, 0xc1, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x01, 0x83, 0xff, 0xfb, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x03, 0xff, 0xf9, 0xf3, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x10, 0xff, 0xf9, 0xe1, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0xff, 0xfb, 0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x83, 0xf1, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x03, 0xe0, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x03, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xbe, 0x32, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xba, 0xbe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xfa, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

*/

void setup() {
//accerleration basic reading
 Serial.begin(9600);
initalReadingPosition();
  
Serial.print("VIEC System Starting");
Serial.println("");
delay(1000);

 pinMode(10,OUTPUT);  // RED LED
 pinMode(11,OUTPUT);  // YELLOW LED
 pinMode(12,OUTPUT);  // GREEN LED
 pinMode(wLEDs_PIN, OUTPUT); // 3 white LEDs
 pinMode(BUTTON_PIN, INPUT); // button trigger

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

/*
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
display.clearDisplay();
//   Show initial display buffer contents on the screen --
display.drawBitmap(0,0,logo,128,64,1);
//   the library initializes this with an Adafruit splash screen.
display.display();
delay(5000); // Pause for 5 seconds
display.clearDisplay();
*/

  /*
  //display.clearDisplay();
  // Clear the buffer
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
 Wire.begin();
 Wire.beginTransmission(MPU6050_addr);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setRotation(0);
 display.clearDisplay();
 */

}


void loop() {


//display.clearDisplay();
  //Reads the Binary number from the DIP Switch
  for (int x = 3; x < 6; x++) {

    bitVal = digitalRead(x);
    stringBit = String(bitVal);
    stringBinary = stringBinary + stringBit;
    binaryNumber = stringBinary.toInt();

  }
  //Function to convert Binary to Decimal
  decimalNumber = convertBinaryToDecimal(binaryNumber);
 
  initalReadingPosition();
  failingRedLED();
  connectYellowLED();
  runningGreenLED();

  switch (decimalNumber){
  case 1:
  connectYellowLED();
  Serial.println("Accelerometer Application Running");
  delay(900);
  Serial.print(".");
  delay(900);
  Serial.print(".");
  delay(900);
  Serial.print(".");
  delay(500);
  Serial.println("");
  AccelerometerSerial();
  PositionSerial();
  //AccelerometerOLED();
  //DisplayPositionOLED();
  delay(2000);
  runningGreenLED();
  break;
  
  case 2:
    if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    failingRedLED();
    //connectYellowLED();
    //runningGreenLED();
    while (0) {}
  }
  else{
  Serial.println("Barometer Application Running");
  delay(900);
  Serial.print(".");
  delay(900);
  Serial.print(".");
  delay(900);
  Serial.print(".");
  delay(500);
  Serial.println("");
    BarometerSerial();
    //BarometerOLED();
    PositionSerial();
    //DisplayPositionOLED();
    connectYellowLED();
    runningGreenLED();
    break;
  }
  case 3:
  Serial.print("Ultrasonic Application Running");
  delay(900);
  Serial.print(".");
  delay(900);
  Serial.print(".");
  delay(900);
  Serial.print(".");
  delay(500);
  Serial.println("");
    //UltrasonicOLED();
    UltrasonicSerial();
    //PositionSerial();
    break;
  case 4:
    Serial.println("Switch Application Running");
    delay(900);
    Serial.print(".");
    delay(900);
    Serial.print(".");
    delay(900);
    Serial.print(".");
    delay(500);
    Serial.println("");
    if(decimalNumber!=4){
      failingRedLED();
      }
    else{    buttonBounce();}

    //DisplayPositionOLED();
    PositionSerial();
    break;
}

   //AccelerometerOLED();
   //AccelerometerSerial();
   
   //BarometerOLED();
   //BarometerSerial();
   
   //UltrasonicOLED();
   //UltrasonicSerial();

   //buttonBounce();
   
   //PositionSerial(); 
   //DisplayPositionOLED();

   
   delay(4000);
   Serial.println(" ");
   Serial.println("----------------------------------");
   delay(3000);


  //Resets all the variables
  binaryNumber = 0;
  bitVal = 0;
  stringBit = "";
  stringBinary = "";


}


void AccelerometerSerial(){

  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);
  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();
  Temp = Wire.read() << 8 | Wire.read();
  GyroX = Wire.read() << 8 | Wire.read();
  GyroY = Wire.read() << 8 | Wire.read();
  GyroZ = Wire.read() << 8 | Wire.read();

  Serial.println("HEC5-UTTyler 2022");
  Serial.println("NASA-TSGC Design");
  Serial.println("");
  Serial.println("Accelerometer - m/s^2");
  Serial.print(AccX);
  Serial.print(", ");
  Serial.print(AccY);
  Serial.print(", ");
  Serial.print(AccZ);
  Serial.println("");
  Serial.println("Gyroscope - rps");
  Serial.print(GyroX, 1);
  Serial.print(", ");
  Serial.print(GyroY);
  Serial.print(", ");
  Serial.print(GyroZ);
  Serial.println("");
  Serial.print("Temp=");
  Serial.print(Temp / 340.00 + 36.53);
  Serial.println("");
  delay(2000);
}

void AccelerometerOLED(){
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);
  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();
  Temp = Wire.read() << 8 | Wire.read();
  GyroX = Wire.read() << 8 | Wire.read();
  GyroY = Wire.read() << 8 | Wire.read();
  GyroZ = Wire.read() << 8 | Wire.read();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("HEC5-UTTyler 2022");
  display.println("NASA-TSGC Design");
  display.println("");
  display.println("Accelerometer - m/s^2");
  display.print(AccX);
  display.print(", ");
  display.print(AccY);
  display.print(", ");
  display.print(AccZ);
  display.println("");
  display.println("Gyroscope - rps");
  display.print(GyroX, 1);
  display.print(", ");
  display.print(GyroY);
  display.print(", ");
  display.print(GyroZ);
  display.println("");
  display.print("Temp=");
  display.print(Temp / 340.00 + 36.53);
  display.display();
  delay(5555); // Pause for 5.55 seconds
}


 //Function to convert Binary to Decimal
long convertBinaryToDecimal(long binary) {
  long number = binary;
  long decimalVal = 0;
  long baseVal = 1;
  long tempVal = number;
  long previousDigit;
  while (tempVal) {
  //Converts Binary to Decimal
  previousDigit = tempVal % 10;
  tempVal = tempVal / 10;
  decimalVal += previousDigit * baseVal;
  baseVal = baseVal * 2;
  }
  //Returns the Decimal number
  return decimalVal;
}

void DisplayPositionOLED(){
   //Prints the Binary number on the OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 10);
  display.print("HEC5-UTTyler");  
  display.setCursor(5, 20);
  display.print("NASA-TSGC Design");  
  display.setCursor(5, 40);
  display.print("Binary:");
  display.println(stringBinary);
  //Prints the Decimal number on the OLED Display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 50);
  display.print("Position:");
  display.println(decimalNumber);
  display.display();
  delay(3000);
  display.clearDisplay();
  }


void PositionSerial(){
  //Prints the Binary number on the Serial Monitor
Serial.println("Position Checking");
Serial.print("Binary: ");
Serial.print(stringBinary);
Serial.print("      ");
//Prints the Decimal number on the Serial Monitor
Serial.print("Decimal: ");
Serial.println(decimalNumber);
}

void BarometerSerial(){
  Serial.println("HEC5-UTTyler 2022");
  Serial.println("NASA-TSGC Design");
  Serial.println("");
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");
  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");
  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
  Serial.println(" meters");    
  Serial.println("------------------------------------");
  delay(3000);
}

void BarometerOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("HEC5-UTTyler 2022");
  display.println("NASA-TSGC Design");

  display.setCursor(0, 30);
  display.print("Temperature: ");
  display.print(bmp.readTemperature());
  display.print(" C");
  display.println("");
  display.print("Pressure:   ");
  display.print(bmp.readPressure());
  display.print(" Pa");
  display.println("");
  display.print("Altitude:   ");
  display.print(bmp.readAltitude());
  display.print(" m");
  display.display();
  delay(5555);
}

void UltrasonicOLED(){
digitalWrite(trigPin, LOW); //PULSE ___|---|___
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance_cm = (duration/2) / 29.1;
distance_in = (duration/2) / 73.914;

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(5, 00);
display.print("HEC5-UTTyler");  
display.setCursor(5, 10);
display.print("NASA-TSGC Design"); 
display.setCursor(0,30);
display.println("Distance Measurement");
display.setCursor(40,40);
display.print(distance_cm);
display.print(" cm");
display.setCursor(40,50);
display.print(distance_in);
display.print(" in");
display.display();
delay(2222);
display.clearDisplay();
}

void UltrasonicSerial(){
digitalWrite(trigPin, LOW); //PULSE ___|---|___
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance_cm = (duration/2) / 29.1;
distance_in = (duration/2) / 73.914;

Serial.println("HEC5-UTTyler 2022");
Serial.println("NASA-TSGC Design");
Serial.println("");
Serial.println("Distance Measurement ");
Serial.print(distance_cm);
Serial.print(" cm");
Serial.println("");
Serial.print(distance_in);
Serial.println(" in");
Serial.println("");
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
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  delay(1000);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(10, HIGH);
  delay(200);
  digitalWrite(10, LOW);
  delay(200);
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
  delay(2000);  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  delay(1000);
  digitalWrite(11, HIGH);
  delay(500);
  digitalWrite(11, LOW);
  delay(500);
  digitalWrite(11, HIGH);
  delay(200);
  digitalWrite(11, LOW);
  delay(200);
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
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);
  delay(200);
  digitalWrite(12, LOW);
  delay(200);
}

void buttonBounce(){
    if (millis() - lastTimeButtonStateChanged > debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
       Serial.println("Button pressed ---- 3 white LED on");
      //Serial.println("");
    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW) {
      //Serial.println("Button pressed ---- 3 white LED off");
      //Serial.println("");
        ledState = (ledState == HIGH) ? LOW: HIGH;
        digitalWrite(wLEDs_PIN, ledState);
      }
    }
  }
}
