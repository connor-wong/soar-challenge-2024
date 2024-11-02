const int IR_SENSOR_NUM = 5;                                       // Number of IR sensors
const int IR_SENSOR_PINS[IR_SENSOR_NUM] = { 14, 13, 12, 11, 10 };  // IR Sensor Pins

void IR_SETUP(void) {
  for (int i = 0; i < IR_SENSOR_NUM; i++) {
    pinMode(IR_SENSOR_PINS[i], INPUT);
  }
}

void IR_READ_DIGITAL(int IR_SENSOR_READINGS_DIGITAL[5]) {
  for (int i = 0; i < IR_SENSOR_NUM; i++) {
    int reading = digitalRead(IR_SENSOR_PINS[i]);  // Get the reading from one IR sensor

    IR_SENSOR_READINGS_DIGITAL[i] = reading;  // Save the reading into array
  }
}

void IR_READ_ANALOG(int IR_SENSOR_READINGS_ANALOG[5]) {
  for (int i = 0; i < IR_SENSOR_NUM; i++) {
    int reading = analogRead(IR_SENSOR_PINS[i]);  // Get the reading from one IR sensor

    IR_SENSOR_READINGS_ANALOG[i] = reading;  // Save the reading into array
  }
}

void IR_READ_DIGITAL_TEST(void) {
  TelnetStream.print("IR Readings: ");

  for (int i = 0; i < IR_SENSOR_NUM; i++) {
    int reading = digitalRead(IR_SENSOR_PINS[i]);  // Get the reading from one IR sensor

    // Print the value
    TelnetStream.print(reading);
    TelnetStream.print(" | ");
  }

  TelnetStream.println(" ");
  delay(500);
}

void IR_READ_ANALOG_TEST(void) {
  TelnetStream.print("IR Readings: ");

  for (int i = 0; i < IR_SENSOR_NUM; i++) {
    int reading = analogRead(IR_SENSOR_PINS[i]);  // Get the reading from one IR sensor

    // Print the value
    TelnetStream.print(reading);
    TelnetStream.print(" | ");
  }

  TelnetStream.println(" ");
  delay(500);
}