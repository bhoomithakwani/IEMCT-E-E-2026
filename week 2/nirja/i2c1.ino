#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(8, 1);
  if (Wire.available()) {
    int data = Wire.read();
    Serial.println(data);
  }
  delay(500);
}
