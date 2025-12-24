Task 2 – Communication Protocols (UART, I²C, SPI)
📌 Aim

To study and simulate basic communication protocols used in microcontrollers—UART, I²C, and SPI—using Arduino Uno in Tinkercad, and to understand their working principles, differences, and practical behavior.

📖 Introduction

Microcontrollers often need to communicate with computers, sensors, and other microcontrollers. This communication is achieved using serial communication protocols. In this task, three commonly used protocols—UART, I²C, and SPI—were implemented and analyzed through simulations.

1️⃣ UART Communication
🔹 What is UART?

UART (Universal Asynchronous Receiver Transmitter) is a simple serial communication protocol that uses two wires:

TX (Transmit)

RX (Receive)

It is asynchronous, meaning no clock signal is used. Both devices must agree on the same baud rate.

🔹 Simulation Setup

Arduino Uno

Potentiometer

Serial Monitor (PC)

🔹 Procedure

Potentiometer connected to an analog pin of Arduino.

Arduino reads sensor value using analogRead().

Data is sent to PC using Serial.begin(9600).

Output observed on Serial Monitor.

🔹 Observation

Sensor values were transmitted continuously.

Data changed smoothly with potentiometer rotation.

Communication was simple and direct.

2️⃣ I²C Communication
🔹 What is I²C?

I²C (Inter-Integrated Circuit) is a two-wire, synchronous communication protocol that supports multiple devices on the same bus using addressing.

SDA → Data line

SCL → Clock line

🔹 Simulation Setup

Arduino Uno (Master)

Arduino Uno (Slave)

Potentiometer (connected to Slave)

🔹 Procedure

Slave Arduino reads potentiometer value.

Slave sends data when requested by Master.

Master receives data using slave address.

Data displayed on Serial Monitor.

🔹 Observation

Proper slave addressing was required.

Master successfully received data from Slave.

Multiple devices can share the same bus.

3️⃣ SPI Communication
🔹 What is SPI?

SPI (Serial Peripheral Interface) is a high-speed synchronous communication protocol.

It uses four wires:

MOSI (Master Out Slave In)

MISO (Master In Slave Out)

SCK (Clock)

SS (Slave Select)

The Master controls the clock and communication.

🔹 Simulation Setup

Arduino Uno (Master)

Arduino Uno (Slave)

Push Button (connected to Slave)

🔹 Procedure

Push button connected to Slave Arduino.

Slave reads button state.

Master selects Slave using SS pin.

Data transferred synchronously.

Master displays received data on Serial Monitor.

🔹 Observation

Data transfer occurred only when SS was LOW.

Communication was clock-based and fast.

Output changed correctly with button press.
