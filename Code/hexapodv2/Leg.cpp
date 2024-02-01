#include "Leg.h"

Leg::Leg() {}
Leg::~Leg() {}

void Leg::Attach(CServo hip, CServo knee, CServo ankle) {
  this->Hip = hip;
  this->Knee = knee;
  this->Ankle = ankle;
}

void Leg::Reset() {
  this->Hip.Write(0);
  this->Knee.Write(0);
  this->Ankle.Write(0);
}
