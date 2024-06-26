/*
 * chall4.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * Spring 2024
 *
 */

#include <Arduino.h>
#include "chall4.h"
#include "drive.h"
#include "collision.h"
#include "light_comm.h"
#include "pins.h"


/* Function: run
 * Description: Run with companion bot to demonstrate challenge 4
 * Parameters:
 *   - None
 * Returns: None
 */
void Chall4::run() {
  Drive& drive = Drive::getInstance();
  Light_Comm light_comm;

  while(not collision_detected()){
    drive.forward();
  }

  drive.stopFor(300);
  light_comm.chall1_receive();
  delay(1800);
  light_comm.chall1_send();
  digitalWrite(Pins::headlights, HIGH);
  delay(250);
  digitalWrite(Pins::headlights, LOW);
  delay(250);
  digitalWrite(Pins::headlights, HIGH);
  delay(250);
  digitalWrite(Pins::headlights, LOW);
  delay(250);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  digitalWrite(Pins::rightTurnSignal, HIGH);
}