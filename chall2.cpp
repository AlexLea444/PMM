#include <Arduino.h>
#include "chall2.h"
#include "drive.h"
#include "collision.h"
#include "light_comm.h"
#include "wifi_comm.h"
#include "pins.h"

void Chall2::run(bool bot1) {
  Drive& drive = Drive::getInstance();
  Wifi_Comm wifi_comm;
  wifi_comm.setup();

  delay(1000);

  if (bot1) {
    wifi_comm.POSTServer("go=false");
  } else {
    wifi_comm.POSTServer("go=true");
  }

  String response = "";
  char data[512];

  while (response != "true") {
    wifi_comm.GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("go=") + 3, response.indexOf("go=") + 7);
  }
  
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

  if (bot1) {
    wifi_comm.POSTServer("go=true");
    delay(1000);
  }

  wifi_comm.POSTServer("go=false");
  for (;;) {};
}