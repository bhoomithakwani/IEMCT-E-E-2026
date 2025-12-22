// C++ code
//
const int TRIG_PIN = 9;   
const int ECHO_PIN = 10;  
const int LED_PIN = 12;
const int BUZZER_PIN = 13;


const int OBSTACLE_THRESHOLD_CM = 20; 

void setup() {

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Obstacle Avoidance System Initialized");
}

void loop() {
 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distanceCm = duration * 0.0343 / 2;

  if (distanceCm < OBSTACLE_THRESHOLD_CM) {
    // OBSTACLE DETECTED!
    digitalWrite(LED_PIN, HIGH);     // Turn LED ON
    digitalWrite(BUZZER_PIN, HIGH);  // Turn Buzzer ON (continuous tone)
    
    Serial.print("OBSTACLE DETECTED! Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
    
  } else {
    digitalWrite(LED_PIN, LOW);      // Turn LED OFF
    digitalWrite(BUZZER_PIN, LOW);   // Turn Buzzer OFF
    
    Serial.print("Clear. Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  }
  delay(1000); 
}