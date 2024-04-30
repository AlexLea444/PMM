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
#include "light_comm.h"
#include "chall1.h"

Drive& drive = Drive::getInstance();
Pins pins;
Light_Comm light_comm;
Chall1 chall1;

void setup() {
  Serial.begin(9600);
  pins.setPins();
  delay(5000);
}

void loop() {
//  Serial.println(":(");
//  drive.forwardToColor(red);
//  delay(2000);
//  chall1.bot1_run();
//  delay(20000);
//  drive.leftFollowLine(yellow);
//  drive.forward();
//  Serial.println(":(");
//  light_comm.chall1_send();
  delay(2000);
  Serial.println(analogRead(Pins::colorIn));
  Serial.println(colorToString(getColorPrecise()));
  Serial.println(colorToString(getColorLineFollowing()));
//  drive.chall5();
}
