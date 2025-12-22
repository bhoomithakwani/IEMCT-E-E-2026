# Communication Protocols Using Arduino (UART & I2C)

## Introduction
This project demonstrates the implementation of **communication protocols** using **Arduino Uno**, focusing on **UART** and **I2C**.  
Both protocols are explored theoretically and practically using **Tinkercad simulations**.

- **UART** transmits analog data from a potentiometer to the Serial Monitor.  
- **I2C** is used for master–slave communication between two Arduino boards, where the slave reads an ultrasonic sensor and the master controls an RGB LED based on the distance.



## Objective
- Understand UART and I2C communication protocols  
- Analyze message framing and data transfer  
- Implement UART and I2C using Arduino Uno  



## UART Communication

### Theory
UART (Universal Asynchronous Receiver Transmitter) is an **asynchronous serial communication protocol**.  
It transmits data **bit by bit** without a shared clock. Both transmitter and receiver must operate at the same **baud rate**.

#### UART Message Frame  
Start Bit → Data Bits (5–8) → Optional Parity → Stop Bit  
- **Start Bit:** Signals the beginning of transmission  
- **Data Bits:** Carry the actual data (usually 8 bits)  
- **Parity Bit:** Optional error checking  
- **Stop Bit:** Indicates the end of transmission  

This ensures that the receiver correctly interprets the incoming serial data.



### Components Used
- Arduino Uno  
- Potentiometer
- Jumper wire


### Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| Potentiometer (middle pin) | A0 |
| VCC | 5V |
| GND | GND |

UART uses the built-in USB serial connection to communicate with the Serial Monitor.



### Arduino Code (UART)
```cpp
int potPin = A0;
int potValue = 0;

void setup() {
  Serial.begin(9600);   // Start UART at 9600 baud
}

void loop() {
  potValue = analogRead(potPin);  // Read potentiometer (0–1023)

  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);       // Send via UART

  delay(500);  // Send data every 500 ms
}
```
### Working  
1. Arduino reads the analog value from the potentiometer.  
2. The ADC converts it to a digital value (0–1023).  
3. The value is sent through UART and displayed on the Serial Monitor.

### Simulations  
<img width="1262" height="557" alt="Screenshot 2025-12-22 at 4 45 55 PM" src="https://github.com/user-attachments/assets/a99cc1c9-09fe-4898-9223-a4d9a9cc7bd2" />


## I2C Communication
### Theory
I2C (Inter-Integrated Circuit) is a synchronous serial communication protocol that allows multiple devices to communicate using only two wires.
It follows a master–slave architecture:  
- The master controls the clock and initiates communication.  
- The slave responds when addressed.

#### I2C Message Frame  
START → Slave Address → R/W Bit → ACK → Data Byte → ACK → STOP
- **START**: Begins communication
- **Slave Address**: Identifies the slave
- **R/W Bit**: Selects read/write operation
- **ACK**: Acknowledgement from the receiver
- **STOP**: Ends communication

### Components Used
- Arduino Uno  
- RGB LEDs
- Ultrasonic Sensor
- Jumper wire

### I2C Slave Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| Trig | D9 |
| Echo | D10 |
| SDA | A4 |
| SCL | A5 |
| VCC | 5V |
| GND | GND |

### Arduino Code for Slave
```cpp
#include <Wire.h>

#define TRIG 9
#define ECHO 10

int distance = 0;

void setup() {
  Wire.begin(0x08);          // Slave address
  Wire.onRequest(sendData);  // Master requests data

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // Measure distance
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  delay(100);
}

void sendData() {
  Wire.write(distance);  // Send distance (0–255 cm)
}
```

### I2C Master Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| Red | D3 |
| Green | D5 |
| Blue | D6 |
| CC | GND |
| SDA | A4 |
| SCL | A5 |

### Arduino Code for Master
```cpp
#include <Wire.h>

#define RED 3
#define GREEN 5
#define BLUE 6

int distance = 0;

void setup() {
  Wire.begin();        // Master
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  Wire.requestFrom(0x08, 1);  // Request 1 byte from slave

  if (Wire.available()) {
    distance = Wire.read();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // LED color logic
  if (distance < 10) {
    setColor(255, 0, 0);   // Red
  } 
  else if (distance < 20) {
    setColor(255, 255, 0); // Yellow
  } 
  else {
    setColor(0, 255, 0);   // Green
  }

  delay(300);
}

void setColor(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}
```

### Working  
1. Slave Arduino measures distance using the ultrasonic sensor.  
2. Master Arduino requests distance data over I2C.  
3. RGB LED changes color based on distance:  
    - Less than 10 cm: Red
    - 10–20 cm: Yellow
    - More than 20 cm: Green


### Simulations  
<img width="1232" height="478" alt="1" src="https://github.com/user-attachments/assets/9429fa64-bed6-4e0f-81f9-66ca01e6a110" />
<img width="1232" height="478" alt="2" src="https://github.com/user-attachments/assets/bc2f933f-655f-479f-a555-ecfe62c7860b" />
<img width="1232" height="478" alt="3" src="https://github.com/user-attachments/assets/7dff1bf9-e4f2-4310-a534-edd56ff07ef3" />

## Link to Simulations  
https://www.tinkercad.com/things/528EMOnpSYW-neat-lappi-amur/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fall&sharecode=-AM7YnT04JAN-knDLeFDH3-eUOKv426X3Yh_BpCaXsw

## Conclusion
This project demonstrates UART and I2C communication protocols using Arduino Uno.
Both simulations confirm correct data transmission and reception, providing a clear understanding of serial communication and device interfacing.
