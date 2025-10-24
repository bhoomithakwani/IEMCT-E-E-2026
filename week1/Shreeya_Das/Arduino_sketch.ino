int led = 7;
int trig = 8;
int echo = 9;
long t;        
float dist;    
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  t = pulseIn(echo, HIGH);
  dist = (0.034 * t) / 2;
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  if (dist < 6) {
    digitalWrite(led, HIGH);
    delay(700);
    digitalWrite(led, LOW);
    delay(200);
    Serial.println("found");
  } else {
    digitalWrite(led, LOW);
  }
}
