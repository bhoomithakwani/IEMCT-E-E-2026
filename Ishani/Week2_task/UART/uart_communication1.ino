void setup() {
  Serial.begin(9600);   // Initialize UART communication
}

void loop() {
  int sensorValue = analogRead(A0); // Read potentiometer
  Serial.print("Potentiometer Value: ");
  Serial.println(sensorValue);      // Send data via UART
  delay(500);
}
