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

color analogToColor(int reading) {
  if (reading > 950)
    return yellow;
  if (reading > 900)
    return red;
  if (reading > 800)
    return blue;
  else
    return black;
}

color getColor() {
  return analogRead(Pins::colorIn);
}

color getColorPrecise() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(Pins::colorIn);
  }
  int reading = sum / 5;

  Serial.println(reading);

  return analogToColor(reading);
}


color getColorLineFollowing() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    millisDelay(10);
    sum += analogRead(Pins::colorIn);
  }
  int reading = sum / 5;

  Serial.println(reading);

  return analogToColor(reading);
}

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
  }
}
