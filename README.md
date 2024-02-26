# antigravity
This Arduino code reads distance from an ultrasonic sensor, prints it to the serial monitor, and adjusts the position of a servo motor based on the distance. The goal is to stabilize an object in front of the sensor by adjusting the servo angle.

Here's a detailed explanation of the code:

### 1. Libraries and Constants:

```cpp
#include <Servo.h>

const int trigPin = 9;   // Trig pin of the ultrasonic sensor
const int echoPin = 10;  // Echo pin of the ultrasonic sensor
const int servoPin = 5;  // Control pin of the servo motor

Servo servoMotor;
```

- **`Servo` Library:** The code includes the Servo library to control the servo motor.
- **Ultrasonic Sensor Pins:** Defines pins for the trig and echo of the ultrasonic sensor, and the control pin of the servo motor.
- **Servo Object:** Creates an instance of the Servo class named `servoMotor`.

### 2. Setup Function:

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoMotor.attach(servoPin);
}
```

- **Serial Communication Setup:** Initializes serial communication at a baud rate of 9600 for debugging purposes.
- **Pin Modes:** Sets the trig pin as OUTPUT and echo pin as INPUT.
- **Attach Servo:** Attaches the servo motor to its control pin.

### 3. Loop Function:

```cpp
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
```

- **Ultrasonic Sensor Readings:**
  - The code triggers the ultrasonic sensor to send a pulse.
  - Measures the time it takes for the pulse to return (echo duration) and calculates the distance in centimeters.
  - Prints the distance to the serial monitor.

- **Servo Adjustment:**
  - Calls the `stabilizeObject` function to adjust the position of the servo based on the calculated distance.

- **Delay:**
  - Introduces a delay to control the frequency of distance measurements. Adjust the delay as needed.

### 4. `stabilizeObject` Function:

```cpp
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
```

- **Mapping Distance to Servo Angle:**
  - Maps the distance value to a servo angle using the `map` function. Adjust the mapping values based on your setup.

- **Limiting Servo Angle:**
  - Uses `constrain` to limit the servo angle within a specified range (0 to 180).

- **Servo Movement:**
  - Sets the servo angle using `servoMotor.write()` to adjust the position of the servo.

- **Serial Output:**
  - Prints the servo angle to the serial monitor for debugging purposes.

This code provides a simple example of using an ultrasonic sensor to measure distance and a servo motor to stabilize an object based on that distance. Adjustments to mapping values may be necessary depending on your specific hardware setup.
