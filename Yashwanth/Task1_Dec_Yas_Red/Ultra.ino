// Teensy 4.1 + Cytron MDD10A + Encoders + MPU6050 DMP
// Full complementary filter for (x, y, theta)
// Outputs: x, y, th_f (rad), yaw_imu_deg, etc. — compatible with live_plot_xy_from_teensy_text.py

#include <Arduino.h>
#include <Wire.h>
#include <Encoder.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// ---------- Motor driver (MDD10A) ----------
const int DIR_L = 3;
const int PWM_L = 5;
const int DIR_R = 4;
const int PWM_R = 6;

// ---------- Encoder pins ----------
const int ENC_L_A = 20, ENC_L_B = 21;
const int ENC_R_A = 22, ENC_R_B = 23;

// ---------- MPU6050 ----------
const int MPU_INT_PIN = 2;

// ---------- Objects ----------
Encoder encLeft(ENC_L_A, ENC_L_B);
Encoder encRight(ENC_R_A, ENC_R_B);
MPU6050 mpu;

// ---------- Robot geometry ----------
const float TICKS_PER_REV = 4160.0f;     // encoder counts per track rotation
const float TRACK_LEN_M = 0.525f;        // track length covered per full encoder rev
const float M_PER_TICK = TRACK_LEN_M / TICKS_PER_REV;
const float WHEEL_BASE_M = 0.19f;        // distance between left/right wheels

// ---------- Complementary filter gains ----------
float ALPHA = 0.98f;   // encoder trust (high-pass)
float BETA = 0.02f;    // IMU trust (low-pass) — = (1 - ALPHA)

// ---------- States ----------
float x_enc = 0, y_enc = 0, theta_enc = 0;  // encoder-only
float x_f = 0, y_f = 0, theta_f = 0;        // fused
float theta_imu = 0;                        // IMU yaw (rad)

// ---------- Timers ----------
elapsedMillis odomTimer;
const uint32_t ODOM_MS = 50; // 20 Hz
long lastL = 0, lastR = 0;

elapsedMillis dirTimer;
const uint32_t SEGMENT_MS = 10000;
int direction = 1;
const int RUN_DUTY = 3000;

// ---------- DMP ----------
volatile bool mpuInterrupt = false;
bool dmpReady = false;
uint16_t packetSize = 0;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];

// ---------- Helper functions ----------
static inline float wrapPi(float a) {
  while (a > PI) a -= 2 * PI;
  while (a < -PI) a += 2 * PI;
  return a;
}

void dmpDataReady() { mpuInterrupt = true; }

void setMotorLeft(int duty) {
  bool forward = duty >= 0;
  uint16_t pwm = constrain(abs(duty), 0, 4095);
  digitalWrite(DIR_L, forward ? LOW : HIGH);
  analogWrite(PWM_L, pwm);
}

void setMotorRight(int duty) {
  bool forward = duty >= 0;
  uint16_t pwm = constrain(abs(duty), 0, 4095);
  digitalWrite(DIR_R, forward ? HIGH : LOW);
  analogWrite(PWM_R, pwm);
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  // Motor setup
  analogWriteFrequency(PWM_L, 20000);
  analogWriteFrequency(PWM_R, 20000);
  analogWriteResolution(12);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  setMotorLeft(0);
  setMotorRight(0);

  // IMU setup
  Wire.begin();
  Wire.setClock(400000);
  mpu.initialize();
  pinMode(MPU_INT_PIN, INPUT);

  if (mpu.testConnection()) {
    if (mpu.dmpInitialize() == 0) {
      mpu.setDMPEnabled(true);
      attachInterrupt(digitalPinToInterrupt(MPU_INT_PIN), dmpDataReady, RISING);
      packetSize = mpu.dmpGetFIFOPacketSize();
      dmpReady = true;
      Serial.println("MPU6050 DMP ready");
    } else {
      Serial.println("DMP init failed");
    }
  } else {
    Serial.println("MPU6050 connection failed");
  }
}

// ---------- Main loop ----------
void loop() {
  // Basic motion control (alternate direction)
  if (dirTimer >= SEGMENT_MS) {
    dirTimer = 0;
    direction = -direction;
  }
  int cmd = direction * RUN_DUTY;
  setMotorLeft(cmd);
  setMotorRight(cmd);

  // --- Read IMU yaw ---
  if (dmpReady && mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    theta_imu = wrapPi(ypr[0]); // radians
  }

  // --- Odometry & fusion ---
  if (odomTimer >= ODOM_MS) {
    odomTimer = 0;

    long cntL = -encLeft.read();
    long cntR = encRight.read();
    long dL = cntL - lastL;
    long dR = cntR - lastR;
    lastL = cntL;
    lastR = cntR;

    float dL_m = dL * M_PER_TICK;
    float dR_m = dR * M_PER_TICK;
    float dC = 0.5f * (dL_m + dR_m);
    float dTheta = (dR_m - dL_m) / WHEEL_BASE_M;

    // Encoder-only pose update
    theta_enc = wrapPi(theta_enc + dTheta);
    float theta_mid = wrapPi(theta_enc - dTheta * 0.5f);
    x_enc += dC * cosf(theta_mid);
    y_enc += dC * sinf(theta_mid);

    // Complementary fused orientation
    theta_f = wrapPi(ALPHA * wrapPi(theta_f + dTheta) + BETA * theta_imu);

    // Complementary fused translation
    float dx_enc = dC * cosf(theta_f);
    float dy_enc = dC * sinf(theta_f);
    x_f = ALPHA * (x_f + dx_enc) + BETA * x_enc;
    y_f = ALPHA * (y_f + dy_enc) + BETA * y_enc;

    // --- Output (Python plot compatible) ---
    Serial.print("x:"); Serial.print(x_f, 5);
    Serial.print(" y:"); Serial.print(y_f, 5);
    Serial.print(" th_f:"); Serial.print(theta_f, 5);
    Serial.print(" yaw_imu_deg:"); Serial.print(theta_imu * 57.2958, 2);
    Serial.print(" Xencoder:"); Serial.print(x_enc, 5);
    Serial.print(" Yencoder:"); Serial.print(y_enc, 5);
    Serial.print(" Angle_encoder:"); Serial.print(theta_enc, 5);
    Serial.println();
  }
}
