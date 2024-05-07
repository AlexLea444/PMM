/*
 * EE31_Phase2B.ino
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include "drive.h"
#include "pins.h"
#include "colors.h"
#include "light_comm.h"
#include "wifi_comm.h"
#include "chall1.h"
#include "chall2.h"
#include "collision.h"

Drive& drive = Drive::getInstance();
Pins pins;
Light_Comm light_comm;
Chall1 chall1;
Chall2 chall2;
Wifi_Comm wifi_comm;

void setup() {
  Serial.begin(9600);
  pins.setPins();

  //drive.forwardFor(200);
  delay(5000);

//  wifi_comm.setup();

//  wifi_comm.chall1_go_bot2();

//  drive.forwardTrapezoidal(2000, 0.6, 1);

//  wifi_comm.POSTServer("red_detected=false");
//  drive.forwardToColor(red);
//  delay(5000);
//  drive.forwardToColor(yellow);
//  delay(5000);
//  drive.forwardToColor(blue);
//  delay(5000);



//  Serial.print(":(");
//  wifi_comm.POSTServer("red_detected=true");

//  drive.stop();

//  wifi_comm.POSTServer("test=successful");
}

void loop() {
  while (collision_detected_alert())
    delay(5000);
  //  drive.chall5();
  //  delay(1000);
//  drive.leftSoundTurn();
//  drive.stopFor(1000);
//  drive.rightSoundTurn();
//  drive.stopFor(1000);

//  while (!(collision_detected_alert())) {}

//  for (;;) {}
//  chall2.bot1_run();
//  chall2.bot2_run();
//  drive.backwardFor(400);
//  delay(2000);
//  char data[64];
  //int input = (int)(detectColor() * 10);
  //char label[7] = "color=";
  //itoa(input, data, 10);
  //size_t oldLength  = strlen(data);
  //memmove(data + 6, data, oldLength + 1);
  //memcpy(data, label, 6);

//  colorToString(detectColor()).toCharArray(data, 64);

//  wifi_comm.POSTServer(data);

//  Serial.print(":(");

//  Serial.println(":(");
//  delay(1000);
//  chall2.bot1_run();
//  delay(20000);
//  drive.leftFollowLine(yellow);
//  drive.forward();
//  Serial.println(":(");
//  light_comm.chall1_send();
//  delay(2000);
//  Serial.println(analogRead(Pins::colorIn));
//  Serial.println(colorToString(getColorPrecise()));
//  drive.chall5();
}
