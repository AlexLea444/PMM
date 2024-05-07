/*
 * remote_control.h
 * Purple Mountain Majesties
 *  - Eddy Zhang, Alexander Lea, Connor Nightingale, Jacob Carulli
 * 5/6/2024
 *
 */

#ifndef __REMOTE_CONTROL_H__
#define __REMOTE_CONTROL_H__

void runRemote();
void onMqttMessage(int messageSize);

// Movement functions redefined here for different speed controls
void forward(int speed);
void left(int speed);
void back(int speed);
void right(int speed);

#endif