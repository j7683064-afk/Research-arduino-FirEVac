#include <Arduino.h>

#define IR_Left A1
#define IR_Right A2
#define Flame_AO A3

#define LeftIN1 13
#define LeftIN2 12
#define RightIN3 11
#define RightIN4 10

#define LeftTrigUS 9
#define MidTrigUS 8
#define RightTrigUS 7
#define LeftEchoUS 6
#define MidEchoUS 5
#define RightEchoUS 4
#define Flame_DO 3
#define RelayIN 2

void setup() {
  Serial.begin(9600);

  // pin initialisation
  pinMode(IR_Left, INPUT);
  pinMode(IR_Right, INPUT);
  pinMode(Flame_AO, INPUT);

  pinMode(LeftIN1, OUTPUT);
  pinMode(LeftIN2, OUTPUT);
  pinMode(RightIN3, OUTPUT);
  pinMode(RightIN4, OUTPUT);

  pinMode(LeftTrigUS, OUTPUT);
  pinMode(MidTrigUS, OUTPUT);
  pinMode(RightTrigUS, OUTPUT);
  pinMode(LeftEchoUS, INPUT);
  pinMode(MidEchoUS, INPUT);
  pinMode(RightEchoUS, INPUT);

  pinMode(Flame_DO, INPUT);
  pinMode(RelayIN, OUPUT)
}

// moves robot forwards
void moveforward() {
  digitalWrite(LeftIN1, HIGH);
  digitalWrite(LeftIN2, LOW);
  digitalWrite(RightIN3, HIGH);
  digitalWrite(RightIN4, LOW);
}

// turns robot left
void turnLeft() {
  digitalWrite(LeftIN1, LOW);
  digitalWrite(LeftIN2, LOW);
  digitalWrite(RightIN3, HIGH);
  digitalWrite(RightIN4, LOW);
}

// turns robot right
void turnRight() {
  digitalWrite(LeftIN1, HIGH);
  digitalWrite(LeftIN2, LOW);
  digitalWrite(RightIN3, LOW);
  digitalWrite(RightIN4, LOW);
}

// turns robot 180 degrees
void kebelakangPusing() {

}

// ultrasonic object detection
float measureDistance(int trigPin, int echoPin) {

  // ensure Ultrasonic Sensor(US) is off 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(50);

  // turn on and off for detection
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long timeTaken = pulseIn(echoPin, HIGH, 30000);
  float distance = timeTaken * 0.0343 / 2;

  // if no echo
  if (timeTaken == 0){
    return 0;
  }

  return distance;

}

// follows line
void trackEvacRoute() {
  // obtain analog reading from proximity IR sensor
  int leftIRreading = analogRead(IR_Left);
  int rightIRreading = analogRead(IR_Right);

  // if in between lines
  if (leftIRreading >= 600 && rightIRreading >= 600) {
    moveforward();
  }
  // if line turns to the left
  else if (leftIRreading < 600) {
    turnLeft();
  }
  // if line turns to the right
  else if (rightIRreading < 600) {
    turnRight();
  }
}
// turn obstacleDetection on
void obstacleDetection() {

  float leftDistance = measureDistance(LeftTrigUS, LeftEchoUS);
  float midDistance = measureDistance(MidTrigUS, MidEchoUS);
  float rightDistance = measureDistance(RightTrigUS, RightEchoUS);

  Serial.print("Left: ");
  Serial.println(leftDistance);

  Serial.print("Middle: ");
  Serial.println(midDistance);

  Serial.print("Right: ");
  Serial.println(rightDistance);

}
// Turn relay ON
void relayON() {
  digitalWrite(RelayIN, HIGH);
}

// Turn relay OFF
void relayOFF() {
  digitalWrite(RelayIN, LOW);
}

void loop() {
  // Read ultrasonic sensors
  float leftDistance = measureDistance(LeftTrigUS, LeftEchoUS);
  float midDistance = measureDistance(MidTrigUS, MidEchoUS);
  float rightDistance = measureDistance(RightTrigUS, RightEchoUS);

  // Check obstacle in front
  if (midDistance > 0 && midDistance < 20) {

    stopRobot();

    Serial.println("Obstacle detected!");

  }

  // No obstacle detected
  else {

    trackEvacRoute();

  }

  delay(50);
}

//test
