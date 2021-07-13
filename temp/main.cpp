//**************************************************// 
//    Display for IR sensor MLX90614  on M5StickC   //
//                    V1.0.0                        //
//   written by Rob Oudendijk                       //
//     Contact email: rob@yr-design.biz             //
//          Copyright (c) 2020, YR-Design           //        
//              All rights reserved.                //
//**************************************************//
// extra info can be found at https://www.waveshare.com/wiki/Infrared_Temperature_Sensor

#include <M5StickC.h>
#include <Wire.h>


//        Inits for reading the data out of the MLX90614 RAM , will be used in Wire.write(OBJECT_TEMP) in the loop   //
#define   MLX90614_ADDRESS    0x00
#define   MLX90614_ADDR_WRITE   0x00	
#define   MLX90614_ADDR_READ    0x01
#define   MLX90614_RAM    0x00
#define   AMBIENT_TEMP    0x06
#define   OBJECT_TEMP     0x07

void setup() {
   M5.begin();
  Wire.begin(0,26);
  Serial.begin(9600);

//OLED setup and startup display
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.println("IR temp");
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


//inits
uint16_t result;
float temperature;

void loop() {
  //connect to sensor I2C
  Wire.beginTransmission(0x5A);          // Send Initial Signal and I2C Bus Address
  Wire.write(OBJECT_TEMP);               // Send data for getting the temparture sensor selection and add one address automatically. 
  Wire.endTransmission(false);           // Stop signal
  Wire.requestFrom(0x5A, 2);             // Get 2 consecutive data from 0x5A, and the data is stored only.
  result = Wire.read();                  // Receive DATA
  result |= Wire.read() << 8;            // Receive DATA
  
  temperature = result * 0.02 - 273.15;
  
  M5.Lcd.fillRect(0,0,160,80,BLACK);
  M5.Lcd.setCursor(40, 30);
  M5.Lcd.setTextColor(WHITE);

  if(temperature >1000){
      M5.Lcd.setCursor(5, 30);
      M5.Lcd.print("No data I2C");
  }
  else {
    M5.Lcd.print(temperature);
    M5.Lcd.print("C");
    }
    
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(60, 70);
  M5.Lcd.print("YR-Design ");
  M5.Lcd.setTextColor(ORANGE);
  M5.Lcd.print("2020");

  M5.Lcd.setTextSize(2);
  // Serial.println(temperature);

  delay(500);
  M5.update();
}