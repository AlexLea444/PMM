/*
 * wifi_comm.h
 * Purple Mountain Majesties
 *  - Eddy Zhang, Alexander Lea, Connor Nightingale, Jacob Carulli
 * Spring 2024
 *
 */

#ifndef __WIFI_COMM_H__
#define __WIFI_COMM_H__

#include <Arduino.h>
#include <WiFiNINA.h>

class Wifi_Comm {
public:
  void setup();

  void chall1_red_bot1();
  void chall1_red_bot2();
  void chall1_go_bot1();
  void chall1_go_bot2();
  void chall1_yellow_bot1();
  void chall1_yellow_bot2();
  void chall1_end();

  void printWifiStatus();

  void POSTServer(char *bodyMessage);
  void GETServer(char *message);
private:
  static const char ssid[];
  static const char pass[];
  static const int keyIndex;
  static const int portNumber;
  static int status;

  static const char server[];
  static const char postRoute[];
  static const char getRoute[];
  WiFiClient client;

  bool chall1_bot1 = false;
};

#endif
