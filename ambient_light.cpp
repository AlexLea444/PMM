/*
 * battery_mgmt.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 5/6/2024
 *
 */

#include <Arduino.h>
#include "ambient_light.h"
#include "pins.h"
#include "utils.h"

/* Function: getAmbientLight
 * Description: Gets the analog reading of the ambient light sensor
 * Parameters:
 *   - None
 * Returns: Analog reading of the ambient light sensor
 */
int getAmbientLight() {
  return analogRead(Pins::ambientLightSensor);
}