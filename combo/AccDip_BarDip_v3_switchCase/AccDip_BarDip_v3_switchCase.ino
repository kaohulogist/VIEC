//Import all required libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
const int MPU6050_addr = 0x68;
int16_t AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

//Initialize the variables
int bitVal;
String stringBit;
String stringBinary;
long binaryNumber;
int decimalNumber;

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




void setup() {
//accerleration basic reading
 Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  // Show initial display buffer contents on the screen --
  display.drawBitmap(0,0,logo,128,64,1);
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(5000); // Pause for 5 seconds
  display.clearDisplay();
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
 

  //Sets pin 3 to pin 6 as input
  //DIP Switch
  for (int x = 3; x < 6; x++) {

    pinMode(x, INPUT);
   //Serial.print("Digital port input check: ");
   //Serial.println(x);
}
}

void loop() {
display.clearDisplay();
  //Reads the Binary number from the DIP Switch
  for (int x = 3; x < 6; x++) {

    bitVal = digitalRead(x);
    stringBit = String(bitVal);
    stringBinary = stringBinary + stringBit;
    binaryNumber = stringBinary.toInt();

  }
  //Function to convert Binary to Decimal
  decimalNumber = convertBinaryToDecimal(binaryNumber);
  
//Prints the Binary number on the Serial Monitor
//Serial.print("Binary: ");
//Serial.print(stringBinary);
//Serial.print("      ");
//Prints the Decimal number on the Serial Monitor
//Serial.print("Decimal: ");
//Serial.println(decimalNumber);

  switch (decimalNumber){
  case 1:
    Serial.println("Accelerometer Application Running");
    Accelerometer();
    DisplayPositionOLED();
    break;
  case 2:
    Serial.println("Barometer Application Running");
    //Barometer();
    break;
  case 3:
    Serial.println("Ultrasonic Application Running");
    //Ultrasonic();
    break;
  case 4:
    Serial.println("Switch Application Running");
    //Switch();
    break;
}


   Accelerometer();
   DisplayPositionOLED();
   Serial.println("----------------------------------");



  //Resets all the variables
  binaryNumber = 0;
  bitVal = 0;
  stringBit = "";
  stringBinary = "";


}

// function Accerlerometer sensor
void Accelerometer(){
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
/*
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
  Serial.println("Temp=");
  Serial.print(Temp / 340.00 + 36.53);*/
  
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

void Barometer(){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 10);
    display.print("Temperature = ");
    display.println(bmp.readTemperature());
    display.println(" *C");
    display.setCursor(5, 20);
    display.print("Pressure = ");
    display.print(bmp.readPressure());
    display.println(" Pa");
    display.setCursor(5, 20);
    display.print("Altitude = ");
    display.print(bmp.readAltitude());
    display.println(" meters");
    display.setCursor(5, 30);
    display.print("Pressure at sealevel (calculated) = ");
    display.print(bmp.readSealevelPressure());
    display.println(" Pa");
    display.setCursor(5, 40);
    display.print("Real altitude = ");
    display.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    display.println(" meters");
    display.println();
    display.display();
    delay(5555);
}

  