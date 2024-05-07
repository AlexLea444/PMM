#include <Arduino.h>

#include "collision.h"
#include "pins.h"

bool collision_detected() {
  return analogRead(Pins::collisionIn) > collision_threshold;
}

bool collision_detected_alert() {
  if (analogRead(Pins::collisionIn) > collision_threshold) {
    wallDetectedNoise();
    return true;
  }
  return false;
}

void wallDetectedNoise() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 700; i++) {
      digitalWrite(Pins::horn, HIGH); // Set the output pin HIGH
      delayMicroseconds(170); // Delay for half of the square wave period (208 us)
      digitalWrite(Pins::horn, LOW); // Set the output pin LOW
      delayMicroseconds(170); // Delay for half of the square wave period (208 us)
    }
    delayMicroseconds(8000);
  }
}