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

void setup() {
  Serial.begin(9600);
  pins.setPins();
  delay(2000);

//  Wifi_Comm wifi_comm;
//  wifi_comm.setup();
//  wifi_comm.POSTServer("test=successful");
}

void loop() {
  drive.leftSoundTurn();
  drive.stopFor(1000);
  drive.rightSoundTurn();
  drive.stopFor(1000);

  while (!(collision_detected_alert())) {}

  for (;;) {}
//  chall2.run(true);
//  drive.backwardFor(400);
//  delay(2000);
  //int input = analogRead(Pins::colorIn);
//  int input = 21234;
//  char label[7] = "color=";
//  itoa(input, data, 10);
//  size_t oldLength  = strlen(data);
//  memmove(data + 6, data, oldLength + 1);
//  memcpy(data, label, 6);

//  wifi_comm.POSTServer(data);

//  Serial.print(":(");

//  Serial.println(":(");
//  drive.forwardToColor(red);
//  delay(2000);
//  chall1.bot1_run();
//  delay(20000);
//  drive.leftFollowLine(yellow);
//  drive.forward();
//  Serial.println(":(");
//  light_comm.chall1_send();
//  delay(2000);
//  Serial.println(analogRead(Pins::colorIn));
//  Serial.println(colorToString(getColorPrecise()));
//  Serial.println(colorToString(getColorLineFollowing()));
//  drive.chall5();
}
