#include <Servo.h>

const int trigPin = 9; // Connect Trig pin of the ultrasonic sensor to Arduino digital pin 9
const int echoPin = 10; // Connect Echo pin of the ultrasonic sensor to Arduino digital pin 10
const int servoPin = 5; // Connect control pin of the servo motor to Arduino digital pin 5

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoMotor.attach(servoPin);
}

void loop() {
  long duration, distance;

  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin to measure the time it takes for the pulse to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Adjust the position of the servo motor based on the distance
  stabilizeObject(distance);

  delay(100); // Adjust the delay as needed
}

void stabilizeObject(long distance) {
  int servoAngle;

  // Map the distance to a servo angle (adjust the values based on your setup)
  servoAngle = map(distance, 10, 100, 0, 180);

  // Limit the servo angle to avoid excessive movement
  servoAngle = constrain(servoAngle, 0, 180);

  // Move the servo to the calculated angle
  servoMotor.write(servoAngle);

  // Print the servo angle to the serial monitor
  Serial.print("Servo Angle: ");
  Serial.println(servoAngle);
}
