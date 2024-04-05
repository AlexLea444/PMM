/*
 * light_comm.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 4/4/2024
 *
 */

#ifndef __LIGHT_COMM_H__
#define __LIGHT_COMM_H__

#include <Arduino.h>

struct Light_Comm {
public:
  void send(uint8_t bit_sequence);
}

#endif
