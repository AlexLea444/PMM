#include <Arduino.h>

#include "collision.h"
#include "pins.h"

bool collision_detected() {
  return analogRead(Pins::collisionIn) > collision_threshold;
}
