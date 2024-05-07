/*
 * battery_mgmt.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 5/6/2024
 *
 */

#include <Arduino.h>
#include "battery_mgmt.h"
#include "pins.h"
#include "utils.h"

/* Function: displayBatteryLevel
 * Description: Shows battery level with PWM on a green LED
 * Parameters:
 *   - None
 * Returns: None
 */
void displayBatteryLevel() {
  int reading = analogRead(Pins::batteryMgmtIn);
  if (reading < 440) {
    batteryDeadNoise();
  }
  int brightness = (reading - 700);
  analogWrite(Pins::batteryMgmtLED, brightness);
}

/* Function: batteryDeadNoise
 * Description: Noise to be played when battery is dead
 * Parameters:
 *   - None
 * Returns: None
 */
void batteryDeadNoise() {
  while (true) {
    for (int i = 0; i < 1200; i++) {
      digitalWrite(Pins::horn, HIGH); // Set the output pin HIGH
      delayMicroseconds(400); // Delay for half of the square wave period (208 us)
      digitalWrite(Pins::horn, LOW); // Set the output pin LOW
      delayMicroseconds(400); // Delay for half of the square wave period (208 us)
    }
    digitalWrite(Pins::horn, LOW);
    delayMicroseconds(400000);
  }
}