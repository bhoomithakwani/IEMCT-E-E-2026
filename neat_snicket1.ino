int irSensor = 2;   // IR sensor output pin
int buzzer = 12;    // Buzzer pin

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int obstacle = digitalRead(irSensor); // Read sensor value

  if (obstacle == 0) { // 0 = obstacle detected
    digitalWrite(buzzer, HIGH);
    Serial.println("🚫 Obstacle Detected!");
  } else {
    digitalWrite(buzzer, LOW);
    Serial.println("✅ Path Clear");
  }

  delay(200);
}
