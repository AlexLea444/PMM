/*
 * colors.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 4/8/2024
 *
 */

#include "colors.h"
#include <Arduino.h>
#include "pins.h"
#include "utils.h"


/* Function: analogToColor
 * Description: Estimates color based on thresholds of ADC
 * Parameters:
 *   - reading: analog reading from color sensor
 * Returns: predicted color of ground below sensor
 */
color analogToColor(int reading) {
  if (reading > 580)
    return yellow;
  if (reading > 390 && reading < 415)
    return red;
  if (reading > 300 && reading < 335)
    return blue;
  else
    return black;
}

/* Function: getColor
 * Description: Get reading of color sensor and return predicted color
 * Parameters:
 *   - None
 * Returns: predicted color of ground below sensor
 */
color getColor() {
  return analogToColor(analogRead(Pins::colorIn));
}

/* Function: getColor
 * Description: Get multiple readings of color sensor and return predicted color
 * Parameters:
 *   - None
 * Returns: predicted color of ground below sensor
 */
color getColorPrecise() {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(Pins::colorIn);
  }
  int reading = sum / 10;

  return analogToColor(reading);
}


/* Function: detectColor
 * Description: Get reading of color sensor based on red/blue flashing
 * Parameters:
 *   - None
 * Returns: predicted color of ground below sensor
 */
color detectColor() {
  float blueValue, redValue;

  //blue is high, red is low
  digitalWrite(Pins::redSensorLED, LOW);
  digitalWrite(Pins::blueSensorLED, HIGH);

  delay(50);
  //read blue value
  blueValue = analogRead(Pins::colorIn);
  blueValue = blueValue / 1023 * 5;
  //blue is low, red is high
  digitalWrite(Pins::blueSensorLED, LOW);
  digitalWrite(Pins::redSensorLED, HIGH);
  delay(50);

  //read red value
  redValue = analogRead(Pins::colorIn);
  redValue = redValue / 1023 * 5;

  // turn both leds off
  digitalWrite(Pins::blueSensorLED, LOW);
  digitalWrite(Pins::redSensorLED, LOW);
  Serial.print("Analog Red: "); Serial.print(redValue);
  Serial.print("                   Analog Blue: "); Serial.println(blueValue);

  if (redValue < 4.2 && blueValue >= 4.1) {
    return blue;
  } else if (redValue >= 4 && blueValue <= 4.5) {
    return red;
  } else if (redValue >= 4.2 && blueValue >= 4.1) {
    return yellow;
  } else {
    return black;
  }
}

/* Function: colorToString
 * Description: Get name of color as String from color enum
 * Parameters:
 *   - toPrint: color as enum
 * Returns: name of color as String
 */
String colorToString(color toPrint) {
  switch (toPrint) {
    case red:
      return "red";
    case blue:
      return "blue";
    case yellow:
      return "yellow";
    case black:
      return "black";
    case none:
      return "none";
  }
}
