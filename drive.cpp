/*
 * drive.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include <Arduino.h>

#include "drive.h"
#include "pins.h"
#include "collision.h"
#include "utils.h"

// Define the static method to get the instance
Drive& Drive::getInstance() {
  static Drive instance; // Static instance ensures it's created only once
  return instance;
}


void Drive::forward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 160);
  analogWrite(Pins::motor4, 0);
}

void Drive::backward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 200);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 130);
}

// TODO: Values might require tuning
void Drive::leftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 100);
  analogWrite(Pins::motor3, 155);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::leftTurnSignal, LOW);
}

// TODO: Values might require tuning
void Drive::leftSoftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 160);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::leftTurnSignal, LOW);
}

// TODO: Values might require tuning
void Drive::rightSoftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 145);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::rightTurnSignal, LOW);
}

// TODO: Values might require tuning
void Drive::rightCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 125);
  analogWrite(Pins::motor3, 120);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::rightTurnSignal, LOW);
}

void Drive::stop() {
  digitalWrite(Pins::headlights, LOW);
  digitalWrite(Pins::brakelights, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 0);
}

// TODO: Values might require tuning
void Drive::leftFollowLine(color c) {
  while (not collision_detected()) {
    leftPointTurn(15);
    rightCurveTurn();
    while ((not collision_detected()) and (getColor() != c))
      millisDelay(100);
  }
  stop();
}

// TODO: Values might require tuning
/*void Drive::rightFollowLine(color c) {
  while (not collision_detected()) {
    rightPointTurn(15);
    leftCurveTurn();
    while ((not collision_detected()) and (getColor() != c))
      millisDelay(40);
  }
  stop();
}*/

void Drive::rightFollowLine(color c) {
  while (not collision_detected()) {
    Serial.println(Pins::colorIn);
    if (getColor() == c)
      rightSharpTurn();
    else
      leftSharpTurn();
    millisDelay(40);
    stop();
  }
}

void Drive::forwardToWall() {
  forward();
  while (not collision_detected())
    millisDelay(5);
  stop();
}

void Drive::forwardToColor(color c) {
  forward();
  while (getColor() != c) {
    millisDelay(40);
    Serial.println(colorToString(getColor()));
  }
  stop();
}

void Drive::forwardFor(int time) {
  forward();
  millisDelay(time);
  stop();
}

void Drive::backwardFor(int time) {
   backward();
   millisDelay(time);
   stop();
}

//Found that delay of 900 is 90 degrees
void Drive::leftPointTurn(unsigned long degrees) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);

  unsigned long time = (degrees * 438)/90;
  //int time = math / 90;
  analogWrite(Pins::motor1, 130);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 130);
  analogWrite(Pins::motor4, 0);

  millisDelay(time);

  digitalWrite(Pins::leftTurnSignal, LOW);
  stopFor(10);
}

//NOTE : For some reason the right wheel does not like to go backwards
// for values less than 130 idk why
//Found that delay of 750 is 90 degreees
void Drive::rightPointTurn(unsigned long degrees) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);

  unsigned long time = (degrees * 330)/90;
  //int time = time / 90;
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 130);

  millisDelay(time);

  digitalWrite(Pins::rightTurnSignal, LOW);
  stopFor(10);
}

void Drive::leftSharpTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);

  analogWrite(Pins::motor1, 130);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 130);
  analogWrite(Pins::motor4, 0);

  digitalWrite(Pins::leftTurnSignal, LOW);
}

void Drive::rightSharpTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);

  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 130);

  digitalWrite(Pins::rightTurnSignal, LOW);
}


void Drive::stopFor(int time) {
  stop();
  millisDelay(time);
}
