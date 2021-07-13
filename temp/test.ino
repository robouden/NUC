#include <FanController.h>
set drivers 
  #include <SPI.h>
  #include <Wire.h>
  #include <SD.h>

int incomingByte = 0; // for incoming serial data
void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
}
void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("ESP32 received: ");
    Serial.println(incomingByte);
  }
}