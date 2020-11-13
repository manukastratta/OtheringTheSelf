/*
 * Ultrasonic Sensor HC-SR04 and Arduino Tutorial
 * https://www.instructables.com/Ultrasonic-sensor-in-openFrameworks-using-Arduino/
 */
#include <NewPing.h>


// Maximum distance we want to ping for (in centimeters)
#define MAX_DISTANCE 200

// Define pin numbers
// Arduino pin assigned to trigger pin on the ultrasonic sensor.
const int trigPin = 9;
// Arduino pin assigned to echo pin on the ultrasonic sensor.
const int echoPin = 10;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// Define variables
//int for reading the distance in cm into.
int distance;

void setup() {
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
    // (setting ping distance in cm to dist variable)
    distance = sonar.ping_cm();

    // Wait 50ms between pings (about 20 pings/sec).
    delay(50);

    //here the dist variable is being written in bytes so that is can be read in oF as an int. 
    Serial.write(distance);
}
