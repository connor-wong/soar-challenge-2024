#include <WiFi.h>
#include <ArduinoOTA.h>
#include <TelnetStream.h>

/* Custom Libraries */
#include <ota_functions.h>
#include <motor_functions.h>
#include <ultrasonic_functions.h>
#include <IR_functions.h>
#include <algorithm_functions.h>

bool startFlag = false;
bool printFlag = false;

void setup() {
  /* Setup  */
  MOTOR_SETUP();
  IR_SETUP();
  OTA_SETUP();
  TelnetStream.begin();
  Serial.begin(115200);
}

void loop() {
  ArduinoOTA.handle();

  if (startFlag == false) {
    int initialDistance = ULTRASONIC_READ();

    if (initialDistance > 0 && initialDistance < 10) {
      TelnetStream.println(String(initialDistance) + " --> Low distance detected, verifying ...");
      delay(2000);

      int verifyDistance = ULTRASONIC_READ();

      if (verifyDistance > 0 && verifyDistance < 10) {
        startFlag = true;
        printFlag = false;

        TelnetStream.println(String(verifyDistance) + " --> Flag is true, starting program ...");
        delay(3000);
      }
    }

    if (printFlag == false) {
      TelnetStream.println(String(initialDistance) + " --> Waiting for flag update ...");
      printFlag = true;
    }

  } else {
    if (printFlag == false) {
      TelnetStream.println("Starting Algorithm ");
      printFlag = true;
    } else {
      ALGORITHM_BANG_BANG();
    }
  }
}