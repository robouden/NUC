/*************************************************** 
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_MAX31865.h>
#include <M5StickC.h>

// Use software SPI: CS, DI, DO, CLK
// Modified for M5StickC:
// original: Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
//Connect the CLK pin to Digital #13 but any pin can be used later   M5StickC G26               ESP32-dev-v4.1 IO18
//Connect the SDO pin to Digital #12 but any pin can be used later   M5StickC G36 (input only)  ESP32-dev-v4.1 IO5
//Connect the SDI pin to Digital #11 but any pin can be used later   M5StickC G33               ESP32-dev-v4.1 IO10
//Connect the CS pin Digital #10 but any pin can be used later       M5StickC G32               ESP32-dev-v4.1 IO9

// Use software SPI: CS, DI, DO, CLK
// Adafruit_MAX31865 thermo = Adafruit_MAX31865(32, 33, 36, 26);//for M5stickC
Adafruit_MAX31865 thermo = Adafruit_MAX31865(9,10,5,18);//for ESP32Pico-dev-V4.1
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  //serial setup
  Serial.begin(9600);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");
  //termocouple init
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  // M5 init
  M5.begin();
  //OLED setup and startup display
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.println("MAX31865 Meter");
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(70, 70);
  M5.Lcd.print("YR-Design ");
  M5.Lcd.setTextColor(ORANGE);
  M5.Lcd.print("2020");
  M5.Lcd.setTextSize(2);

  delay(3000);

//clear the screen
  M5.Lcd.fillRect(0,0,160,80,BLACK);
  M5.Lcd.setTextColor(WHITE);

}

void loop() {
  //setup termocouple reading
  uint16_t rtd = thermo.readRTD();

  //serial print
  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio,8);
  Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
  Serial.print("Temperature = "); Serial.println(thermo.temperature(RNOMINAL, RREF));

  //setup display
  M5.Lcd.fillRect(0,0,160,80,BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Axp.ScreenBreath(9);

  //display data
   M5.Lcd.setTextSize(2);
  if(ratio== 0){
      M5.Lcd.setCursor(5, 30);
      M5.Lcd.print("NO DATA !!");
  }
  else {
    M5.Lcd.setCursor(40, 30);
    M5.Lcd.print(thermo.temperature(RNOMINAL, RREF));
    M5.Lcd.print("C");
    }

 
    //display copyrights
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(60, 70);
  M5.Lcd.print("YR-Design ");
  M5.Lcd.setTextColor(ORANGE);
  M5.Lcd.print("2020");
  Serial.println();
  M5.update();
  delay(1000);

}