/*KOTOBUKI CHANNEL*/
/* https://www.youtube.com/channel/UCg7eS98ni4n2WxfWYIiwGvw */
/*************************************************************/
#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/Org_01.h>
#include <Adafruit_BMP085.h>
#include <TroykaDHT.h>
/*Global Var*/
Adafruit_BMP085 bmp;
#define SEALEVELPRESSURE_HPA (101500)
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
DHT dht(9, DHT22);
  
void setup() {
  /*initialize the serial address of the OLED Display*/
  display.begin(0x3C);
  /*clears the display*/
  display.clearDisplay();
  bmp.begin();
  dht.begin();
}
  
void loop() {
  /*clears the display*/
  display.clearDisplay();
  /*initalize the readings of the DH11's Temperature and Humidity*/
  dht.read();
  display.setFont(&Org_01);
  display.setCursor(0,5);
  display.print("BME180");
  /*Font Style*/
  display.setFont(&FreeSansBold9pt7b);
  /*size of the text*/
  display.setTextSize(1);
  /*sets the color of the text*/
  display.setTextColor(WHITE);

  
  /*prints BME180 temperature in Celsius*/
  display.setCursor(0,19);
  display.print("T=");
  display.print(bmp.readTemperature(),1);
  display.println("*C");
  
  /*displays the humidity of the air*/
  display.setCursor(0,34);
  display.print("H=");
  display.print(dht.getHumidity(),1);
  display.println("%");
  
 
  /*prints BME180 pressure in Hectopascal Pressure Unit*/
  display.setCursor(0,49);
  display.print("P=");
  display.print(bmp.readPressure()/100.0F,1);
  display.println("hPa");
  
  
  /*prints BME180 altitude in meeters*/
  display.setCursor(0,63);
  display.print("A=");
  display.print(bmp.readAltitude(SEALEVELPRESSURE_HPA),1);
  display.println("m");
  delay(1000);
  /*display buffer*/
  display.display();
}
