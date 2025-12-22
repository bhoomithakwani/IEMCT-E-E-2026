

#include <Wire.h>

void setup() {
  Wire.begin();        // Initialize as Master
  Serial.begin(9600);  // UART to PC
}

void loop() {
  Wire.requestFrom(0x08, 1); // Request 1 byte from Slave

  if (Wire.available()) {
    int receivedValue = Wire.read();
    Serial.print("Received Value: ");
    Serial.println(receivedValue);
  }

  delay(500);
}
