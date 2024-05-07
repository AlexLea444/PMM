/*
 * chall2.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * Spring 2024
 *
 */

#include <Arduino.h>

#include "chall2.h"
#include "drive.h"
#include "collision.h"
#include "light_comm.h"
#include "wifi_comm.h"
#include "pins.h"


/* Function: bot1_run
 * Description: Precise movement challenge, starting bot
 * Parameters:
 *   - None
 * Returns: None
 */
void Chall2::bot1_run() {
  //Wifi_Comm wifi_comm;
  //wifi_comm.setup();

  delay(1000);

  /*wifi_comm.POSTServer("go=false");

 String response = "";
  char data[512];

  while (response != "true") {
    wifi_comm.GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("go=") + 3, response.indexOf("go=") + 7);
  }*/
  
  move();

  //wifi_comm.POSTServer("go=true");
  delay(1000);

  //wifi_comm.POSTServer("go=false");
  for (;;) {};
}

/* Function: bot2_run
 * Description: Precise movement challenge, second bot
 * Parameters:
 *   - None
 * Returns: None
 */
void Chall2::bot2_run() {
  Wifi_Comm wifi_comm;
  wifi_comm.setup();

  delay(1000);

  wifi_comm.POSTServer("go=true");

  String response = "";
  char data[512];

  while (response != "true") {
    wifi_comm.GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("go=") + 3, response.indexOf("go=") + 7);
  }
  
  move();

  wifi_comm.POSTServer("go=false");
  for (;;) {};
}


/* Function: move
 * Description: Precise movement run by both bots in challenge
 * Parameters:
 *   - None
 * Returns: None
 */
void Chall2::move() {
  Drive& drive = Drive::getInstance();

  drive.stopFor(3000);

  drive.forwardFor(1000);

  drive.stopFor(2000);

  drive.rightPointTurn(175);

  drive.stopFor(2000);

  drive.backwardFor(400);

  drive.stopFor(2000);

  // TURN LEFT
  drive.leftPointTurn(90);

  drive.stopFor(2000);

  drive.forwardFor(200);

  drive.stopFor(2000);

  // TURN RIGHT
  drive.rightPointTurn(90);

  drive.stopFor(2000);

  drive.forwardFor(1200);

  drive.stopFor(2000);

  // TURN RIGHT
  drive.rightPointTurn(90);

  drive.stopFor(2000);

  drive.forwardFor(200);

  drive.stopFor(2000);

  // TURN RIGHT
  drive.rightPointTurn(90);

  drive.stopFor(2000);
}