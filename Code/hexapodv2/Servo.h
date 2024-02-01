
#pragma once

#include "FaBoPWM_PCA9685.h"

class CServo {
protected:
  void WriteRAW(int8_t angle);

  FaBoPWM faboPWM;
  int channel;

  int8_t MinAngle = -90;
  int8_t MaxAngle = 90;
public:
  int8_t Offset = 0;
  bool Inverted = false;

  CServo(int8_t minAngle = -90, int8_t maxAngle = 90, int8_t offset = 0);
  ~CServo();

  void Attach(FaBoPWM faboPWM, int channel);

  void Calibrate(int8_t offset);
  int8_t Read();
  void Write(int8_t angle);
};
