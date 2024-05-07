/*
 * utils.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#include "utils.h"
#include <Arduino.h>

/* Function: millisDelay
 * Description: Delay using millis(), enables some use of interrupts
 * Parameters:
 *   - None
 * Returns: None
 */
void millisDelay( long int delayTime){
  long int start_time = millis();
  while ( millis() - start_time < delayTime) ;
}