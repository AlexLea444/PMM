/*
 * collision.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * Spring 2024
 *
 */

#include <Arduino.h>

#include "collision.h"
#include "pins.h"

/* Function: collision_detected
 * Description: detect collision with front IR emitter/sensor
 * Parameters:
 *   - None
 * Returns: True if a collision is detected, else false
 */
bool collision_detected() {
  return analogRead(Pins::collisionIn) > collision_threshold;
}

/* Function: collision_detected_alert
 * Description: detect collision, play sound if collision is detected
 * Parameters:
 *   - None
 * Returns: True if a collision is detected, else false
 */
bool collision_detected_alert() {
  if (analogRead(Pins::collisionIn) > collision_threshold) {
    wallDetectedNoise();
    return true;
  }
  return false;
}

/* Function: wallDetectedNoise
 * Description: Noise to be played when a wall is detected
 * Parameters:
 *   - None
 * Returns: None
 */
void wallDetectedNoise() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 700; i++) {
      digitalWrite(Pins::horn, HIGH); // Set the output pin HIGH
      delayMicroseconds(170); // Delay for half of the square wave period (208 us)
      digitalWrite(Pins::horn, LOW); // Set the output pin LOW
      delayMicroseconds(170); // Delay for half of the square wave period (208 us)
    }
    delayMicroseconds(8000);
  }
}