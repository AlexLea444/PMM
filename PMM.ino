/*
 * EE31_Phase2B.ino
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include "drive.h"
#include "pins.h"
#include "colors.h"

Drive& drive = Drive::getInstance();
Pins pins;

void setup() {
  Serial.begin(9600);
  pins.setPins();
}

void loop() {
  analogWrite(Pins::batteryMgmtLED, analogRead(Pins::batteryMgmtLED) - 700);
}
