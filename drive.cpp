/*
 * drive.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include "drive.h"
#include <Arduino.h>
#include "pins.h"
#include "utils.h"

void Drive::forward(int time) {
  analogWrite(Pins::motor1, 155);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 155);
  analogWrite(Pins::motor4, 0);
  millisDelay(time);
}

void Drive::backward(int time) {
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 155);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 155);
  millisDelay(time);
}

//Found that delay of 900 is 90 degrees
void Drive::leftPointTurn(unsigned long degrees) {
  unsigned long time = (degrees * 910)/90;
  //int time = math / 90;
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 130);
  analogWrite(Pins::motor4, 0);
  millisDelay(time);
}

//NOTE : For some reason the right wheel does not like to go backwards
// for values less than 130 idk why
//Found that delay of 750 is 90 degreees
void rightPointTurn(unsigned long degrees){
  unsigned long time = (degrees * 740)/90;
  //int time = time / 90;
  analogWrite(Pins::motor1, 130);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 130);
  millisDelay(time);
}

void Drive::stop(int time) {
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 0);
  millisDelay(time);
}
