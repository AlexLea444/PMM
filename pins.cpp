/*
 * pins.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#include "pins.h"
#include <Arduino.h>

const int Pins::motor1 = 6;
const int Pins::motor2 = 5;
const int Pins::motor3 = 10;
const int Pins::motor4 = 11;
const int Pins::redLED = 7;
const int Pins::blueLED = 8;
const int Pins::colorIn = A4;

void Pins::setPins() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(colorIn, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}
