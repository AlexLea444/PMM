#ifndef __CHALL1_H__
#define __CHALL1_H__

#include <Arduino.h>
#include "drive.h"

class Chall1 {
public:
  void bot1_run();
  void bot2_run();
private:
  void bot1_start();
  void bot1_follow_red();
  void bot1_find_yellow();
  void bot1_follow_yellow();
  void bot2_follow_blue();
  void bot2_find_yellow();
  void bot2_follow_yellow();
};

#endif
