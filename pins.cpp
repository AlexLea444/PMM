/*
 * pins.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#include "pins.h"
#include <Arduino.h>

// PWM motor pins for variable speed, turning
const int Pins::motor1 = 6;
const int Pins::motor2 = 5;
const int Pins::motor3 = 10;
const int Pins::motor4 = 9;

// Color detection system for path following
//  Future: red & blue sensor LED can be run from SCL/SDA pins
const int Pins::redSensorLED = A2;
const int Pins::blueSensorLED =  A0;
const int Pins::colorIn = A3;

// Ambient light sensor (Note: Currently cannot be run with line following)
const int Pins::ambientLightSensor = A2;

// IR detection system for collision
const int Pins::collisionIn = A1;

// IR detection system for collision
const int Pins::commLED = 11;
const int Pins::commIn = A4;

// Battery management system
const int Pins::batteryMgmtLED = 3;
const int Pins::batteryMgmtIn = A5;

// Indicators
const int Pins::headlights = 0;
const int Pins::leftTurnSignal = 7;
const int Pins::rightTurnSignal = 8;
const int Pins::brakelights = 1;
const int Pins::redStateLED = 13;
const int Pins::blueStateLED = A5;
const int Pins::greenStateLED = 12;
const int Pins::yellowStateLED = 2;
const int Pins::horn = 4;

/* Function: setPins
 * Description: Sets all bot pins to INPUT/OUTPUT
 *              MUST BE RUN BEFORE USING PINS
 * Parameters:
 *   - None
 * Returns: None
 */
void Pins::setPins() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  pinMode(redSensorLED, OUTPUT);
  pinMode(blueSensorLED, OUTPUT);
  pinMode(colorIn, INPUT);

  pinMode(collisionIn, INPUT);

  pinMode(commLED, OUTPUT);
  pinMode(commIn, INPUT);

  pinMode(batteryMgmtLED, OUTPUT);
  pinMode(batteryMgmtIn, INPUT);

  pinMode(headlights, OUTPUT);
  pinMode(brakelights, OUTPUT);
  pinMode(leftTurnSignal, OUTPUT);
  pinMode(rightTurnSignal, OUTPUT);
  pinMode(redStateLED, OUTPUT);
  pinMode(blueStateLED, OUTPUT);
  pinMode(greenStateLED, OUTPUT);
  pinMode(yellowStateLED, OUTPUT);
  pinMode(horn, OUTPUT);
}
