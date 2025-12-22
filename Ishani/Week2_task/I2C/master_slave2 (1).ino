#include <Wire.h>

int sensorValue = 0;

void setup() {
  Wire.begin(0x08);           // Initialize as Slave
  Wire.onRequest(sendData);  // Function to send data
}

void loop() {
  sensorValue = analogRead(A0); // Read potentiometer
  delay(100);
}

void sendData() {
  Wire.write(sensorValue >> 2); // Send 1 byte (0–255)
}
