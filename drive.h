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
#include "colors.h"

class Drive {
public:
  // Static method to get the instance
  static Drive& getInstance();

  // Function declarations
  void forward();
  void backward();
  void leftSharpTurn();
  void leftCurveTurn();
  void leftSoftCurveTurn();
  void rightSharpTurn();
  void rightCurveTurn();
  void rightSoftCurveTurn();
  void stop();

  void chall5();

  void leftFollowLine(color c);
  void rightFollowLine(color c);
  void forwardToWall();
  void forwardToColor(color c);

  void forwardFor(int time);
  void forwardForScaled(int time, float scaler);
  void backwardFor(int time);
  void leftPointTurn(unsigned long degrees);
  void rightPointTurn(unsigned long degrees);
  void stopFor(int time);

private:
  // Private constructor to prevent instantiation
  Drive() {}

  // Prevent copying of the instance
  Drive(const Drive&) = delete;
  void operator=(const Drive&) = delete;
};

#endif
