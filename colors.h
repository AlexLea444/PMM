/*
 * colors.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 *  4/8/2024
 *
 */

#ifndef __COLORS_H__
#define __COLORS_H__

#include <Arduino.h>

enum color {red, blue, yellow, black};

color analogToColor(int reading);
color getColor();
color getColorPrecise();
color getColorLineFollowing();
String colorToString(color toPrint);

#endif
