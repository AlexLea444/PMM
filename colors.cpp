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

color getColor() {
  int reading = analogRead(Pins::colorIn);

  if (reading > 700)
    return yellow;
  if (reading > 620)
    return red;
  if (reading > 520)
    return blue;
  else
    return black;
}

color getColorPrecise() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(Pins::colorIn);
  }
  int reading = sum / 5;

  if (reading > 700)
    return yellow;
  if (reading > 620)
    return red;
  if (reading > 520)
    return blue;
  else
    return black;
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
