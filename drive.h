/*
 * drive.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#ifndef __DRIVE_H__
#define __DRIVE_H__

#include <Arduino.h>

struct Drive {
public:
  void forward(int time);
  void backward(int time);
  void leftPointTurn(unsigned long degrees);
  void rightPointTurn(unsigned long degrees);
  void stop(int time);
};

#endif
