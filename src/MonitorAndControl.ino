
#include <FanController.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//set drivers 
  #include <SPI.h>
  #include <Wire.h>
  #include <SD.h>

// Sensor wire is plugged into port 2 on the Arduino.
// For a list of available pins on your board,
// please refer to: https://www.arduino.cc/en/Reference/AttachInterrupt
#define SENSOR_PIN 21 //pin IO04

//For other sensor pins:
// tacho 1  pin 21
// tacho 2  pin 33
// tacho 3  pin 23
// tacho 4  pin 19

// Choose a threshold in milliseconds between readings.
// A smaller value will give more updated results,
// while a higher value will give more accurate and smooth readings
#define SENSOR_THRESHOLD 1000


// PWM pin (4th on 4 pin fans)
#define PWM_PIN 25 // pin IO33

// Initialize library
FanController fan(SENSOR_PIN, SENSOR_THRESHOLD, PWM_PIN);

// GPIO where the DS18B20 is connected to
const int oneWireBus = 22;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int speed =20;
int adjustetemp=0;

/*
   The setup function. We only start the library here
*/
void setup(void)
{
  // setup Tacho pins.
  pinMode(21,INPUT_PULLUP);
  pinMode(33,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);

  // start serial port
  Serial.begin(115200);

  // Start up Fan library
  fan.begin();

  // set min speed

  fan.setDutyCycle(speed);

  // Start the DS18B20 sensor
  sensors.begin();
}

/*
   Main function, get and show the temperature
*/
void loop(void)
{
    //Call temperature sensors data
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);

  // Call fan.getSpeed() to get fan RPM.
  unsigned int rpms = fan.getSpeed(); // Send the command to get RPM

  //Serial print data  
  Serial.print("Current speed: ");
  Serial.print(rpms);
  Serial.print("RPM");
  Serial.print("\t");
  Serial.print("Real temperature:");
  Serial.print(temperatureC);
  Serial.print("ºC");
  //calculate adjusted temperature
  temperatureC =temperatureC+adjustetemp;
  //Print new data
  Serial.print("\t");
  Serial.print("Adjusted temperature:");
  Serial.print(temperatureC);
  Serial.println("ºC");


  //Map temperature form 30-70 to fanspeed PWM from 20 to 100
  speed=map(temperatureC, 30,70,20,100);

  // Set fan duty cycle
  fan.setDutyCycle(speed);

  // Get new speed from Serial (0-100%)
  if (Serial.available() > 0) {
    // Parse speed
    adjustetemp = Serial.parseInt();

    // // Constrain a 0-100 range
    // byte target = max(min(input, 100), 20);

    // Print obtained value
    Serial.print("Duty cycle: ");
    Serial.print(speed, DEC);
    Serial.print("\t");
    Serial.print("Adjusted temperature: ");
    Serial.println(adjustetemp, DEC);
    
    // set new speed
    fan.setDutyCycle(speed);

  }

  delay(1000);
}
