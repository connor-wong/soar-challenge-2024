#include <NewPing.h>
#include <ultrasonic_functions.cpp>

const int TRIG = 3;
const int ECHO = 8;
const int MAX_DISTANCE = 200;
bool start = false;

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

int ULTRASONIC_READ(void) {
  int distance = sonar.ping_cm();  // Send ping, get distance in cm and print result (0 = outside set distance range)
  if (distance != 0) return distance;
}

void ULTRASONIC_READ_TEST(void) {
  int distance = sonar.ping_cm();  // Send ping, get distance in cm and print result (0 = outside set distance range)

  if (distance != 0) {
    TelnetStream.print("Distance: ");
    TelnetStream.print(distance);
    TelnetStream.println("cm");
  }

  delay(500);
}