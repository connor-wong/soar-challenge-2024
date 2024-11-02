#include <algorithm_functions.cpp>
#include <Arduino.h>

/* Flag Status */
bool endFlag = false;
bool obstacleFlag = false;
bool printEndFlag = false;

int IR_SENSOR_READINGS_DIGITAL[5];

/* Obstacle Detection */
void ALGORITHM_OBSTACLE_DETECTION(void) {
  int distance = ULTRASONIC_READ();

  if (distance >= 15 && distance <= 30) {
    delay(500);

    distance = ULTRASONIC_READ();

    if (distance >= 15 && distance <= 25) {
      TelnetStream.print("Possible Obstacle Detected: ");
      TelnetStream.print(distance);
      TelnetStream.println("cm");

      STOP(); /* With 500ms delay */

      for (int i = 0; i < 5; i++) {
        FORWARD_CREEP(350);
        distance = ULTRASONIC_READ();

        TelnetStream.print("Verifying Obstacle: ");
        TelnetStream.print(distance);
        TelnetStream.println("cm");

        if (distance >= 10 && distance <= 20) {
          STOP();
          obstacleFlag = true;
          TelnetStream.print("Confirmed Obstacle Detected: ");
          TelnetStream.print(distance);
          TelnetStream.println("cm");
          break;
        }
      }

      STOP();
    }

    if (obstacleFlag) {
      TelnetStream.print("obstacleFlag --> true, TURN_CIRCLE");
      BACKWARD();
      delay(500);
      STOP();
      TURN_CIRCLE();
      obstacleFlag = false;
    }
  }
}

/* Straight Line Functions */
void ALGORITHM_BANG_BANG(void) {
  if (endFlag == true && printEndFlag == false) {
    TelnetStream.println("End Goal Reach!");
    printEndFlag = true;
  }

  if (endFlag == false) {
    ALGORITHM_OBSTACLE_DETECTION();
    IR_READ_DIGITAL(IR_SENSOR_READINGS_DIGITAL);

    if (DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[0])) {
      TelnetStream.println("TURN_LEFT");
      TURN_LEFT();
    }

    if (DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[2]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[0]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[1])) {
      TelnetStream.println("FORWARD");
      FORWARD();
    }

    if (DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[0]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[2]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[4])) {
      TelnetStream.println("TURN_RIGHT");
      TURN_RIGHT();
    }

    if (DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[4]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[2]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[0])) {
      TelnetStream.println("TURN_LEFT");
      TURN_LEFT();
    }

    if (DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[1])) {
      TelnetStream.println("TURN_LEFT");
      TURN_LEFT();
    }

    if (DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[3])) {
      TelnetStream.println("TURN_RIGHT");
      TURN_RIGHT();
    }

    /* End of line -> All white detection */
    if (DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[0]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[1]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[2]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[3]) && DETECT_WHITE(IR_SENSOR_READINGS_DIGITAL[4])) {
      TelnetStream.println("TURN_CIRCLE");
      TURN_CIRCLE();
    }

    /* Reach Goal -> All black detection */
    if (DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[0]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[1]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[2]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[3]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[4])) {
      TelnetStream.println("ALL DETECTED");
      // FORWARD();
      delay(300);

      /* Check if all sensors are detected after moving forward */
      IR_READ_DIGITAL(IR_SENSOR_READINGS_DIGITAL);

      if (DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[0]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[1]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[2]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[3]) && DETECT_BLACK(IR_SENSOR_READINGS_DIGITAL[4])) {
        STOP();
        endFlag = true;  // Update end flag
      }
    }
  }
}

bool DETECT_BLACK(int sensor) {
  if (sensor == 0) return true;
  else return false;
}

bool DETECT_WHITE(int sensor) {
  if (sensor == 1) return true;
  else return false;
}