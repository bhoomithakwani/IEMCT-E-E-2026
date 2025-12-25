

---

# Serial Communication Protocols: UART, I²C, and SPI

This repository explains three commonly used serial communication protocols in embedded systems:

* **UART**
* **I²C**
* **SPI**

Each section includes a **short note, important terms, and Arduino example code**.

---

## 1️⃣ UART (Universal Asynchronous Receiver Transmitter)

### 📌 Short Note

UART is an **asynchronous serial communication protocol** used for **one-to-one communication** between two devices (e.g., microcontroller ↔ PC).
It does **not use a clock signal**. Both devices must agree on the same **baud rate**.

### 🔑 Important Terms

* **TX (Transmit)** – Sends data
* **RX (Receive)** – Receives data
* **Baud Rate** – Speed of data transfer (bps)
* **Start Bit** – Indicates start of data frame
* **Stop Bit** – Indicates end of data frame
* **Parity Bit** – Optional error checking

### 🧪 UART Example (Arduino)

```cpp
void setup() {
  Serial.begin(9600);   // Initialize UART communication
}

void loop() {
  int sensorValue = analogRead(A0); // Read potentiometer
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);      // Send data via UART
  delay(500);
}
```
### CIRCUIT
<img width="940" height="551" alt="image" src="https://github.com/user-attachments/assets/123307d4-b38d-483c-a4ff-0e4d89cac909" />


---

## 2️⃣ I²C (Inter-Integrated Circuit)

### 📌 Short Note

I²C is a **synchronous serial communication protocol** that allows **multiple devices** to communicate using **only two wires**.
It follows a **master–slave architecture** and uses **addresses** to identify slave devices.

### 🔑 Important Terms

* **SDA (Serial Data Line)** – Data transfer
* **SCL (Serial Clock Line)** – Clock signal
* **Master** – Initiates communication
* **Slave** – Responds to master
* **Address** – Unique ID of slave device
* **ACK / NACK** – Acknowledge signals

---

### 🧪 I²C Example (Arduino)

#### 🔹 Master Code

```cpp
#include <Wire.h>

void setup() {
  Wire.begin();          // Join I2C as master
  Serial.begin(9600);    // UART for Serial Monitor
}

void loop() {
  Wire.requestFrom(8, 1); // Request 1 byte from slave

  if (Wire.available()) {
    int value = Wire.read();
    Serial.print("Received value: ");
    Serial.println(value);
  }

  delay(500);
}
```

#### 🔹 Slave Code

```cpp
#include <Wire.h>

int sensorValue = 0;

void setup() {
  Wire.begin(8);                 // Slave address
  Wire.onRequest(sendData);      // Register request event
}

void loop() {
  sensorValue = analogRead(A0);  // Read sensor
}

void sendData() {
  Wire.write(sensorValue / 4);   // Send data (1 byte)
}
```
### CIRCUIT
<img width="940" height="388" alt="image" src="https://github.com/user-attachments/assets/6455b1a9-a641-4b0d-9f89-af7bb318e8da" />


---

## 3️⃣ SPI (Serial Peripheral Interface)

### 📌 Short Note

SPI is a **high-speed synchronous communication protocol** used for **short-distance communication**.
It supports **full-duplex communication** and is **faster than UART and I²C**.

### 🔑 Important Terms

* **MOSI** – Master Out Slave In
* **MISO** – Master In Slave Out
* **SCK** – Serial Clock
* **SS / CS** – Slave Select / Chip Select
* **Full-Duplex** – Send and receive simultaneously

---

### 🧪 SPI Example (Arduino)

#### 🔹 Master Code

```cpp
#include <SPI.h>

void setup() {
  Serial.begin(9600);
  SPI.begin();                  // Start SPI as master
  pinMode(10, OUTPUT);          // SS pin
  digitalWrite(10, HIGH);       // Slave not selected
}

void loop() {
  digitalWrite(10, LOW);        // Select slave
  byte value = SPI.transfer(0); // Request data
  digitalWrite(10, HIGH);       // Deselect slave

  Serial.print("Button State: ");
  Serial.println(value);

  delay(500);
}
```

#### 🔹 Slave Code

```cpp
#include <SPI.h>

volatile boolean received;
volatile byte buttonState;

void setup() {
  pinMode(MISO, OUTPUT);        // Slave sends data
  pinMode(2, INPUT_PULLUP);     // Button input

  SPCR |= _BV(SPE);             // Enable SPI as slave
  SPI.attachInterrupt();        // Enable SPI interrupt
}

ISR (SPI_STC_vect) {            // SPI interrupt
  buttonState = digitalRead(2); // Read button
  SPDR = buttonState;           // Send data to master
  received = true;
}

void loop() {
  // Main loop not required for SPI slave
}
```
### CIRCUIT
<img width="940" height="454" alt="image" src="https://github.com/user-attachments/assets/0056fbbd-80ce-4ea3-951f-e2ec6e55ca7c" />


---

## 🔄 Comparison Table

| Feature            | UART         | I²C          | SPI         |
| ------------------ | ------------ | ------------ | ----------- |
| Communication Type | Asynchronous | Synchronous  | Synchronous |
| Clock Signal       | ❌ No         | ✔ SCL        | ✔ SCK       |
| Number of Wires    | 2 (TX, RX)   | 2 (SDA, SCL) | 4+          |
| Devices Supported  | 2            | Multiple     | Multiple    |
| Addressing         | ❌ No         | ✔ Yes        | ❌ No        |
| Speed              | Low          | Medium       | High        |

---

### ✅ Notes

* UART is **simple** but supports only **two devices**
* I²C saves **pins** and supports **multiple devices**
* SPI offers **highest speed** and **full-duplex communication**

---

