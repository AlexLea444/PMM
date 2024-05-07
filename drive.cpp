/*
 * drive.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include <Arduino.h>

#include "drive.h"
#include "pins.h"
#include "collision.h"
#include "utils.h"
#include "wifi_comm.h"

// Define the static method to get the instance
Drive& Drive::getInstance() {
  static Drive instance; // Static instance ensures it's created only once
  return instance;
}


void Drive::forward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 150);
  analogWrite(Pins::motor3, 162);
  analogWrite(Pins::motor4, 0);
}

/* Function: forwardAt
 * Description: Set drive forward at speed determined by scaler
 * Parameters:
 *   - scaler: number between 0 and 1 specifying speed of bot
 * Returns: None
 */
void Drive::forwardAt(float scaler) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 100 * scaler);
  analogWrite(Pins::motor3, 142 * scaler);
  analogWrite(Pins::motor4, 0);  
}

/* Function: backward
 * Description: Set drive backward at set speed
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::backward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 100);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 136);
}

/* Function: leftCurveTurn
 * Description: Set drive curving left at set speed
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::leftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 100);
  analogWrite(Pins::motor3, 155);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::leftTurnSignal, LOW);
}

/* Function: leftSoftCurveTurn
 * Description: Set drive curving softly left at set speed
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::leftSoftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 70);
  analogWrite(Pins::motor3, 60);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::leftTurnSignal, LOW);
}

/* Function: rightSoftCurveTurn
 * Description: Set drive curving softly right at set speed
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::rightSoftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 40);
  analogWrite(Pins::motor3, 80);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::rightTurnSignal, LOW);
}

/* Function: rightCurveTurn
 * Description: Set drive curving right at set speed
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::rightCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 125);
  analogWrite(Pins::motor3, 120);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::rightTurnSignal, LOW);
}


/* Function: stop
 * Description: Cut power to all motors
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::stop() {
  digitalWrite(Pins::headlights, LOW);
  digitalWrite(Pins::brakelights, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 0);
}

/* Function: leftFollowLine
 * Description: Follow along the left side of a colored line
 * Parameters:
 *   - c: color of line to follow
 * Returns: None
 */
void Drive::leftFollowLine(color c) {
  //Serial.println("STARTING LINE FOLLOW");
  //forward();
  while (not collision_detected()) {
    color c_new = detectColor();
    //Serial.println(colorToString(c_new));
    
    if (c_new == c) {
      leftSoftCurveTurn();
      millisDelay(100);
    } else {
      rightSoftCurveTurn();
      millisDelay(100);
    }
    millisDelay(10);
  }
  stop();
  //Serial.println("ENDING LINE FOLLOW");
}

/* Function: rightFollowLine
 * Description: Follow along the right side of a colored line
 * Parameters:
 *   - c: color of line to follow
 * Returns: None
 */
void Drive::rightFollowLine(color c) {
  //Serial.println("STARTING LINE FOLLOW");
  //forward();
  while (not collision_detected()) {
    color c_new = detectColor();
    //Serial.println(colorToString(c_new));
    
    if (c_new == c) {
      rightSoftCurveTurn();
      millisDelay(100);
    } else {
      leftSoftCurveTurn();
      millisDelay(100);
    }
    millisDelay(10);
  }
  stop();
  //Serial.println("ENDING LINE FOLLOW");
}

/* Function: forwardToWall
 * Description: Drive forward until a collision is detected
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::forwardToWall() {
  forward();
  while (not collision_detected())
    millisDelay(5);
  stopFor(400);
}

/* Function: forwardToColor
 * Description: Drive forward until a color is detected
 * Parameters:
 *   - c: color to stop at
 * Returns: None
 */
void Drive::forwardToColor(color c) {
  forward();
  while (detectColor() != c) {}
  
  if (c == yellow) {
    stop();
    return;
  }
  
  delay(10);
  
  if (detectColor() == c) {
    stop();
    return;
  } else {
    forwardToColor(c);
  }
}

/* Function: forwardFor
 * Description: Drive forward for given time (in millis)
 * Parameters:
 *   - time: time in milliseconds
 * Returns: None
 */
void Drive::forwardFor(int time) {
  forward();
  millisDelay(time);
  stop();
}

/* Function: forwardForScaled
 * Description: Drive forward for given time (in millis), at given speed
 * Parameters:
 *   - time: time in milliseconds
 *   - scaler: number between 0 and 1 specifying speed of bot
 * Returns: None
 */
void Drive::forwardForScaled(int time, float scaler) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);

  forwardAt(scaler);

  millisDelay(time);
  stop();
}

/* Function: chall5
 * Description: Drive forward at a set, slow speed (requires tuning)
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::chall5() {

  forward();
  millisDelay(10);

  while(true) {
    for (int i = 0; i < 3998; i++) {
      if ((i % 12) and (i % 13))
        stop();
      else
        forward();
      millisDelay(5);
    }
  }
  

}

/* Function: backwardFor
 * Description: Drive backward for given time (in millis)
 * Parameters:
 *   - time: time in milliseconds
 * Returns: None
 */
void Drive::backwardFor(int time) {
   backward();
   millisDelay(time);
   stop();
}

/* Function: leftPointTurn
 * Description: Make a left point turn (tuned to 90 degrees)
 * Parameters:
 *   - degrees: number of degrees to turn about center axis
 * Returns: None
 */
void Drive::leftPointTurn(unsigned long degrees) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);

  unsigned long time = (degrees * 441)/90;
  //int time = math / 90;
  analogWrite(Pins::motor1, 130);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 130);
  analogWrite(Pins::motor4, 0);

  millisDelay(time);

  digitalWrite(Pins::leftTurnSignal, LOW);
  stopFor(10);
}

/* Function: leftSoundTurn
 * Description: Make a left point turn (about 100 degrees),
 *              playing sound that ramps up over time
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::leftSoundTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);

  //int time = math / 90;
  analogWrite(Pins::motor1, 110);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 110);
  analogWrite(Pins::motor4, 0);

  for (int i = 0; i < 939; i++) {
    digitalWrite(Pins::horn, HIGH); // Set the output pin HIGH
    delayMicroseconds(i); // Delay for half of the square wave period (208 us)
    digitalWrite(Pins::horn, LOW); // Set the output pin LOW
    delayMicroseconds(i); // Delay for half of the square wave period (208 us)
  }

  digitalWrite(Pins::leftTurnSignal, LOW);
  stopFor(10);
}

/* Function: rightSoundTurn
 * Description: Make a right point turn (about 100 degrees),
 *              playing sound that ramps up over time
 * Parameters:
 *   - None
 * Returns: None
 */
void Drive::rightSoundTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);

  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 110);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 110);

  for (int i = 936; i > 0; i--) {
    digitalWrite(Pins::horn, HIGH); // Set the output pin HIGH
    delayMicroseconds(i); // Delay for half of the square wave period (208 us)
    digitalWrite(Pins::horn, LOW); // Set the output pin LOW
    delayMicroseconds(i); // Delay for half of the square wave period (208 us)
  }

  digitalWrite(Pins::rightTurnSignal, LOW);
  stopFor(10);
}

/* Function: rightPointTurn
 * Description: Make a right point turn (tuned to 90 degrees)
 * Parameters:
 *   - degrees: number of degrees to turn about center axis
 * Returns: None
 */
void Drive::rightPointTurn(unsigned long degrees) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);

  unsigned long time = (degrees * 438)/90;
  //int time = time / 90;
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 130);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 130);

  millisDelay(time);

  digitalWrite(Pins::rightTurnSignal, LOW);
  stopFor(10);
}

/* Function: stopFor
 * Description: Cut power to motors for given time (in millis)
 * Parameters:
 *   - time: time in milliseconds
 * Returns: None
 */
void Drive::stopFor(int time) {
  stop();
  millisDelay(time);
}

/* Function: forwardTrapezoidal
 * Description: Drive forward with modular acceleration and deceleration 
 * Parameters:
 *   - total_time: time in milliseconds of total function call (approx.)
 *   - pct_at_vmax: pct of time that should be spent at max velocity (0 to 1)
 *   - vmax: maximum velocity, a scaler between 0 and 1
 * Returns: None
 */
void Drive::forwardTrapezoidal(int total_time, float pct_at_vmax, float vmax) {
  float top_time = total_time * pct_at_vmax;
  float acceleration_time = ((float)total_time - top_time) / 2;

  if (vmax <= 0 || pct_at_vmax <= 0 || total_time <= 0) {
    Serial.println("trapezoidalForward given non-positive, exiting.");
    return;
  } else if (vmax > 1 || pct_at_vmax > 1) {
    Serial.println("vmax and pct_at_vmax must be between 0 and 1");
    return;
  }

  // accelerate to vmax
  auto start_time = millis();
  while (millis() < start_time + acceleration_time) {
    forwardAt(((float)(millis() - start_time) / acceleration_time) * vmax);
    delay(10);
  }

  // drive at vmax
  start_time += acceleration_time;
  while (millis() < start_time + top_time) {
    forwardAt(vmax);
    delay(10);
  }

  // decelerate to 0
  start_time += top_time;
  while (millis() < start_time + acceleration_time) {
    forwardAt(vmax * (1 - ((float)(millis() - start_time) / acceleration_time)));
    delay(10);
  }
}
