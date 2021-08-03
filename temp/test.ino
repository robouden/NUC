/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO15
#define ONE_WIRE_BUS 22
// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

DeviceAddress sensor1 = { 0x28, 0x24, 0x2B, 0x56, 0xB5, 0x1, 0x3C, 0x7D };
DeviceAddress sensor2 = { 0x28, 0x56, 0x49, 0x2, 0x0, 0x0, 0x0, 0x9F };


void setup(void){
  Serial.begin(115200);
  sensors.begin();
}

void loop(void){ 
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  Serial.print("Sensor 1(*C): ");
  Serial.print(sensors.getTempC(sensor1)); 
  Serial.print(" Sensor 1(*F): ");
  Serial.println(sensors.getTempF(sensor1)); 
 
  Serial.print("Sensor 2(*C): ");
  Serial.print(sensors.getTempC(sensor2)); 
  Serial.print(" Sensor 2(*F): ");
  Serial.println(sensors.getTempF(sensor2)); 
  
  
  delay(2000);
}