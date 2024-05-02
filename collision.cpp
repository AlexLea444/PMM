#include <Arduino.h>

#include "collision.h"
#include "pins.h"

bool collision_detected() {
  return analogRead(Pins::collisionIn) > collision_threshold;
}

bool collision_detected_alert() {
  if (analogRead(Pins::collisionIn) > collision_threshold) {
    digitalWrite(Pins::horn, HIGH);
    delay(50);
    digitalWrite(Pins::horn, LOW);
    delay(50);
    digitalWrite(Pins::horn, HIGH);
    delay(50);
    digitalWrite(Pins::horn, LOW);
    delay(50);
    return true;
  }
  return false;
}
