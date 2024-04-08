/*
 * pins.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#ifndef __PINS_H__
#define __PINS_H__

#include <Arduino.h>

class Pins {
public:
  const static int motor1;
  const static int motor2;
  const static int motor3;
  const static int motor4;
  const static int commLED;
  const static int redLED;
  const static int blueLED;
  const static int colorIn;
  void setPins();
};

#endif
