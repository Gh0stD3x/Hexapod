
#pragma once

#include "FaBoPWM_PCA9685.h"
#include "Servo.h"

class Leg {
protected:
  CServo Hip;
  CServo Knee;
  CServo Ankle;
public:
  Leg();
  ~Leg();

  void Attach(CServo hip, CServo knee, CServo ankle);

  void Reset();
};
