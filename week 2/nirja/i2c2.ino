#include <Wire.h>

void setup() {
  Wire.begin(8);
  Wire.onRequest(sendData);
}

void loop() {}

void sendData() {
  int value = analogRead(A0);
  Wire.write(value / 4);
}

