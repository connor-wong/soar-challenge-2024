#include <motor_functions.cpp>
#include <Arduino.h>

/* PWM Properties */
const int FREQ = 2000;                         // Frequency of PWM signal (2000 Hz)
const int RES = 10;                            // Resolution of PWM signal (10 bit resolution 0-1023)
const int MAX_DUTY_CYCLE = pow(2, RES) - 1;    // Maximum duty cycle
const int SPEED_LIMIT = MAX_DUTY_CYCLE * 0.1;  // Limit speed

/* Left Wheel Pins */
const int LEFT_ENA_PIN = 37;       // ENA Pin to control speed of left motor
const int LEFT_FORWARD_PIN = 38;   // IN1 Pin to control forward direction of left motor
const int LEFT_BACKWARD_PIN = 40;  // IN2 Pin to contrcol backward direction of left motor

/* Right Wheel Pins */
const int RIGHT_ENA_PIN = 2;        // ENA Pin to control speed of right motor
const int RIGHT_FORWARD_PIN = 41;   // IN1 Pin to control forward direction of right motor
const int RIGHT_BACKWARD_PIN = 42;  // IN2 Pin to control backward direction of right motor

void MOTOR_SETUP(void) {
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_BACKWARD_PIN, OUTPUT);
  ledcAttach(LEFT_ENA_PIN, FREQ, RES);
  ledcAttach(RIGHT_ENA_PIN, FREQ, RES);
}

void FORWARD(void) {
  LEFT_FORWARD(SPEED_LIMIT);
  RIGHT_FORWARD(SPEED_LIMIT);
}

void FORWARD_CREEP(int speed) {
  LEFT_FORWARD(speed);
  RIGHT_FORWARD(speed);
  delay(250);
  STOP();
}

void BACKWARD(void) {
  LEFT_BACKWARD(SPEED_LIMIT);
  RIGHT_BACKWARD(SPEED_LIMIT);
}

void TURN_RIGHT(void) {
  LEFT_FORWARD(SPEED_LIMIT);
  RIGHT_STOP();
}

void TURN_LEFT(void) {
  RIGHT_FORWARD(430);  // Fixed value after calibration
  LEFT_STOP();
}

void TURN_CIRCLE(void) {
  RIGHT_FORWARD(470);  // Fixed value after calibration
  LEFT_BACKWARD(470);  // Fixed value after calibration
}

void STOP(void) {
  LEFT_STOP();
  RIGHT_STOP();

  delay(500);
}

void LEFT_FORWARD(int speed) {
  // Set direction of motor
  digitalWrite(LEFT_FORWARD_PIN, HIGH);
  digitalWrite(LEFT_BACKWARD_PIN, LOW);

  // Limit speed to between 0 and speed limit
  speed = speed < 0 ? 0 : speed;
  speed = speed > SPEED_LIMIT ? SPEED_LIMIT : speed;

  ledcWrite(LEFT_ENA_PIN, speed);  // Set the speed of the motor
}

void LEFT_BACKWARD(int speed) {
  // Set direction of motor
  digitalWrite(LEFT_FORWARD_PIN, LOW);
  digitalWrite(LEFT_BACKWARD_PIN, HIGH);

  // Limit speed to between 0 and speed limit
  speed = speed < 0 ? 0 : speed;
  speed = speed > SPEED_LIMIT ? SPEED_LIMIT : speed;

  ledcWrite(LEFT_ENA_PIN, speed);  // Set the speed of the motor
}

void LEFT_STOP(void) {
  // Set direction of motor
  digitalWrite(LEFT_FORWARD_PIN, LOW);
  digitalWrite(LEFT_BACKWARD_PIN, LOW);

  // Set the speed to 0
  ledcWrite(LEFT_ENA_PIN, 0);
}

void RIGHT_FORWARD(int speed) {
  // Set direction of motor
  digitalWrite(RIGHT_FORWARD_PIN, HIGH);
  digitalWrite(RIGHT_BACKWARD_PIN, LOW);

  // Limit speed to between 0 and speed limit
  speed = speed < 0 ? 0 : speed;
  speed = speed > SPEED_LIMIT ? SPEED_LIMIT : speed;

  ledcWrite(RIGHT_ENA_PIN, speed);  // Set the speed of the motor
}

void RIGHT_BACKWARD(int speed) {
  // Set direction of motor
  digitalWrite(RIGHT_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_BACKWARD_PIN, HIGH);

  // Limit speed to between 0 and speed limit
  speed = speed < 0 ? 0 : speed;
  speed = speed > SPEED_LIMIT ? SPEED_LIMIT : speed;

  ledcWrite(RIGHT_ENA_PIN, speed);  // Set the speed of the motor
}

void RIGHT_STOP(void) {
  // Set direction of motor
  digitalWrite(RIGHT_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_BACKWARD_PIN, LOW);

  ledcWrite(RIGHT_ENA_PIN, 0);  // Set the speed to 0
}