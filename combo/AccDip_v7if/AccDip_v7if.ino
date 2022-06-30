//Import all required libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
const int MPU6050_addr = 0x68;
int16_t AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Initialize the variables
int bitVal;
String stringBit;
String stringBinary;
long binaryNumber;
int decimalNumber;



void setup() {
//accerleration basic reading
 Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Ive changed the address //already chill
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
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

 

  //Sets pin 3 to pin 6 as input
  //DIP Switch
  for (int x = 3; x < 7; x++) {

    pinMode(x, INPUT);
}
}

void loop() {

  //Reads the Binary number from the DIP Switch
  for (int x = 3; x < 7; x++) {

    bitVal = digitalRead(x);
    stringBit = String(bitVal);
    stringBinary = stringBinary + stringBit;
    binaryNumber = stringBinary.toInt();
    Serial.println(binaryNumber);
    delay(2000);
  }
  //Function to convert Binary to Decimal
  decimalNumber = convertBinaryToDecimal(binaryNumber);
  Serial.println(decimalNumber);
  delay(2000);
  //If statement
  if (decimalNumber=1){
  DisplayTest1();
  decimalNumber=0;
  }
  
    else if(decimalNumber=2){
    DisplayTest2();
    }
  
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

void DisplayPosition(){
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

  void DisplayTest1(){
   //Prints the Binary number on the OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 10);
  display.print("Test123");  
  display.display();
  delay(3000);
  display.clearDisplay();
  }

    void DisplayTest2(){
   //Prints the Binary number on the OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 10);
  display.print("Test2");  
  display.display();
  delay(3000);
  display.clearDisplay();
  }
