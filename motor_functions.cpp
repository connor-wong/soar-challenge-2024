#ifndef MOTOR_FUNCTIONS_H
#define MOTOR_FUNCTIONS_H

void MOTOR_SETUP(void);

void LEFT_FORWARD(int speed);
void LEFT_BACKWARD(int speed);
void LEFT_STOP(void);

void RIGHT_FORWARD(int speed);
void RIGHT_BACKWARD(int speed);
void RIGHT_STOP(void);

void FORWARD(void);
void FORWARD_CREEP(void);
void BACKWARD(void);
void TURN_RIGHT(void);
void TURN_LEFT(void);
void TURN_CIRCLE(void);
void STOP(void);

#endif