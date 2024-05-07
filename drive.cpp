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

void Drive::forwardAt(float scaler) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 100 * scaler);
  analogWrite(Pins::motor3, 142 * scaler);
  analogWrite(Pins::motor4, 0);  
}

void Drive::backward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 100);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 136);
}

// TODO: Values might require tuning
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

// TODO: Values might require tuning
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

// TODO: Values might require tuning
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

// TODO: Values might require tuning
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

void Drive::stop() {
  digitalWrite(Pins::headlights, LOW);
  digitalWrite(Pins::brakelights, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 0);
}

// TODO: Values might require tuning
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

// TODO: Values might require tuning
/*void Drive::rightFollowLine(color c) {
  while (not collision_detected()) {
    rightPointTurn(15);
    leftCurveTurn();
    while ((not collision_detected()) and (getColor() != c))
      millisDelay(40);
  }
  stop();
}*/

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

void Drive::forwardToWall() {
  forward();
  while (not collision_detected())
    millisDelay(5);
  stopFor(400);
}

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

void Drive::forwardFor(int time) {
  forward();
  millisDelay(time);
  stop();
}

void Drive::forwardForScaled(int time, float scaler) {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);

  forwardAt(scaler);

  millisDelay(time);
  stop();
}

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

void Drive::backwardFor(int time) {
   backward();
   millisDelay(time);
   stop();
}

//Found that delay of 900 is 90 degrees
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


//NOTE : For some reason the right wheel does not like to go backwards
// for values less than 130 idk why
//Found that delay of 750 is 90 degreees
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

void Drive::leftSharpTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);

  analogWrite(Pins::motor1, 60);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 60);
  analogWrite(Pins::motor4, 0);

  digitalWrite(Pins::leftTurnSignal, LOW);
}

void Drive::rightSharpTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);

  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 60);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 60);

  digitalWrite(Pins::rightTurnSignal, LOW);
}

void Drive::stopFor(int time) {
  stop();
  millisDelay(time);
}

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

  auto start_time = millis();
  while (millis() < start_time + acceleration_time) {
    Serial.println("ACCELERATING");
    forwardAt(((float)(millis() - start_time) / acceleration_time) * vmax);
    delay(10);
  }

  start_time += acceleration_time;
  while (millis() < start_time + top_time) {
    Serial.println("AT MAX VELOCITY");
    forwardAt(vmax);
    delay(10);
  }

  start_time += top_time;
  while (millis() < start_time + acceleration_time) {
    Serial.println("DECELERATING");
    forwardAt(vmax * (1 - ((float)(millis() - start_time) / acceleration_time)));
    delay(10);
  }
}
