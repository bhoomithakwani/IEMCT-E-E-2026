# Obstacle Avoidance System Using Arduino Uno

## Introduction
This project is an **Obstacle Avoidance System** designed using an **Arduino Uno**, an **Ultrasonic Sensor (HC-SR04)**, and a **Buzzer**.  
The system detects obstacles placed in front of the sensor and alerts the user by turning ON a buzzer when the object is within **10 cm**.

The complete circuit and working were tested using **Tinkercad simulation** and also implemented irl.  



## Objective
- To measure distance using an ultrasonic sensor  
- To detect nearby obstacles  
- To generate an alert using a buzzer  



## Theory
The ultrasonic sensor works on the principle of **sound wave reflection**.

1. Arduino sends a short pulse to the **TRIG** pin.
2. The sensor emits ultrasonic sound waves.
3. These waves hit an obstacle and reflect back.
4. The **ECHO** pin receives the reflected signal.
5. The time taken is used to calculate the distance.

#### Distance Formula:
Distance = (Time × Speed of Sound) / 2  
Distance = duration × 0.0343 / 2



## Components Used
- Arduino Uno  
- Ultrasonic Sensor (HC-SR04)  
- Buzzer  
- Breadboard  
- Jumper wires  



## Circuit Connections

| Component | Arduino Pin |
|---------|-------------|
| TRIG | Digital Pin 8 |
| ECHO | Digital Pin 9 |
| Buzzer | Digital Pin 10 |
| VCC | 5V |
| GND | GND |



## Circuit Simulation
The circuit was designed and simulated using **Tinkercad** and also implemented physically.  
The ultrasonic sensor is connected to the Arduino, and a buzzer is used as an alert device.

<img width="882" height="510" alt="Object in range" src="https://github.com/user-attachments/assets/3a867cdc-b930-40f2-9bd4-46e40d0ec491" />   
<img width="882" height="510" alt="Object not in range" src="https://github.com/user-attachments/assets/6d87b784-1418-47bf-8238-3f5403fde2f4" /> 

Link to Tinkercad simulation: https://www.tinkercad.com/things/l4sNrwPMbHL-brave-krunk-esboo/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=_Fy31GfP84yTiz7e6YXnm67OnPTJK9mEltH8e9CCXkI <br>
Link to video of physical implentation: https://photos.app.goo.gl/4XZrYCYVXRDe4b6p6


## Working
1. Arduino sends a trigger signal to the ultrasonic sensor.
2. The sensor calculates the distance of the object.
3. If the distance is **less than or equal to 10 cm**, the buzzer turns ON.
4. If the distance is greater than **10 cm**, the buzzer remains OFF.



## Arduino Code
```cpp
long duration;
float distance;

const int trigPin = 8;
const int echoPin = 9;
const int buzzerPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;

  if (distance <= 10) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}
```



## Simulation Results  
The buzzer activates whenever an object is placed within 10 cm of the ultrasonic sensor, confirming successful obstacle detection.  



## Applications  
- Obstacle detection systems
- Robotics navigation
- Parking assistance systems
- Safety alert devices  



## Conclusion  
This project successfully demonstrates an obstacle avoidance system using Arduino Uno and an ultrasonic sensor.
The simulation confirms that the system accurately detects nearby objects and reliably alerts the user using a buzzer.
