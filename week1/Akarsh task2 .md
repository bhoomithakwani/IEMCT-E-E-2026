##  Communication Protocols using UART, I²C and SPI

##  Project Overview
This project demonstrates the basic working of three commonly used communication protocols in embedded systems using an Arduino UNO:

- UART (Universal Asynchronous Receiver Transmitter)  
- I²C (Inter-Integrated Circuit)  
- SPI (Serial Peripheral Interface)

The project shows how an Arduino communicates:
- with a computer using UART,
- with another Arduino using I²C (Master–Slave),
- and with another Arduino using SPI (Master–Slave).

These protocols are widely used in sensor interfacing, data transfer, displays, memory cards, and multi-device embedded systems.

---

##  How It Works
The project uses three different communication methods:

- 🔄 UART Communication: Sends analog sensor data from Arduino to a PC using serial communication without a clock signal.
- 🔗 I²C Communication: Transfers data between two Arduino boards using a shared data and clock line with device addressing.
- ⚡ SPI Communication: Transfers data between two Arduino boards using dedicated data lines and a clock controlled by the master.

In all cases, the Arduino reads a simple input and transmits data using the selected protocol.

---

##  Components Used

| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino UNO | 2 | Required for I²C and SPI Master–Slave |
| Potentiometer | 1 | Analog input source |
| Push Button | 1 | Input for SPI communication |
| Jumper Wires | As needed | Circuit connections |
| USB Cable | 1 | UART communication with PC |

---

##  Circuit Connections

### UART Connections

| Component | Arduino Pin | Description |
|------------|-------------|-------------|
| Potentiometer Output | A0 | Analog input |
| Potentiometer VCC | 5V | Power supply |
| Potentiometer GND | GND | Common ground |
| PC Connection | USB | Serial communication |

---

### I²C Connections

| Signal | Master Pin | Slave Pin | Description |
|--------|------------|-----------|-------------|
| SDA | A4 | A4 | Serial data line |
| SCL | A5 | A5 | Serial clock line |
| GND | GND | GND | Common ground |
| Potentiometer | — | A0 | Analog input to Slave |

---

### SPI Connections

| Signal | Master Pin | Slave Pin | Description |
|--------|------------|-----------|-------------|
| MOSI | D11 | D11 | Master Out Slave In |
| MISO | D12 | D12 | Master In Slave Out |
| SCK | D13 | D13 | Serial Clock |
| SS | D10 | D10 | Slave Select |
| GND | GND | GND | Common ground |
| Button | — | D2 | Input to Slave |

---

---

## 💻 Arduino Code

### UART Code
```cpp
// UART Communication Code
// Reads analog value from A0 and sends it to Serial Monitor

int sensorValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(200);
}
```
## UART Image

<img width="1305" height="674" alt="image" src="https://github.com/user-attachments/assets/f80b65e8-0813-4e32-884d-aa41224e0e4e" />

## I²C Slave Code

```
#include <Wire.h>

int sensorValue = 0;

void setup() {
  Wire.begin(8); // Initialize as Slave
}

void loop() {
  sensorValue = analogRead(A0);
  Wire.onRequest(sendData);
  delay(100);
}

void sendData() {
  Wire.write(sensorValue / 4); // Scale 10-bit ADC to 8-bit
}
```

## I²C Master Code

```
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Initialize as Master
}

void loop() {
  Wire.requestFrom(8, 1);
  if (Wire.available()) {
    int data = Wire.read();
    Serial.println(data);
  }
  delay(200);
}
```
## I2C Image


<img width="1298" height="625" alt="image" src="https://github.com/user-attachments/assets/b6844b96-f13c-4c20-852e-5b59cf66c390" />

 ## SPI Slave Code
```
#include <SPI.h>

volatile byte dataToSend = 0;

void setup() {
  pinMode(MISO, OUTPUT);
  pinMode(2, INPUT_PULLUP); // Button
  SPI.begin();
  SPI.attachInterrupt();
}

ISR(SPI_STC_vect) {
  SPDR = dataToSend;
}

void loop() {
  dataToSend = (digitalRead(2) == LOW) ? 1 : 0;
}
```
## SPI Master Code

```
#include <SPI.h>

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  SPI.begin();
}

void loop() {
  digitalWrite(10, LOW);
  byte received = SPI.transfer(0);
  digitalWrite(10, HIGH);

  Serial.println(received);
  delay(300);
}
```
