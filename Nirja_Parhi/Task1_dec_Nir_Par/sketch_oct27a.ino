// Pin constants
const uint8_t PIN_TRIG = 9;
const uint8_t PIN_ECHO = 10;

// Measurement variables
unsigned long echo_us = 0;   // echo time in microseconds
float distance_cm = 0.0f;    // distance in centimeters

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(9600);
}

void loop() {
  // Generate a clean 10 us trigger pulse (ASCII only)
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Measure echo pulse width
  echo_us = pulseIn(PIN_ECHO, HIGH);

  // Convert time to distance in cm: d = (t * 0.0343) / 2
  distance_cm = (echo_us * 0.0343f) / 2.0f;

  // Output in centimeters only
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(100);
}