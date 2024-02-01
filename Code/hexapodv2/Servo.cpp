#include "Servo.h"

CServo::CServo(int8_t minAngle, int8_t maxAngle, int8_t offset) {
  this->MinAngle = minAngle;
  this->MaxAngle = maxAngle;
  this->Offset = offset;
}
CServo::~CServo() {  }

void CServo::WriteRAW(int8_t angle) {
  this->faboPWM.set_channel_value(this->channel, angle);
}

void CServo::Attach(FaBoPWM faboPWM, int channel) {
  this->faboPWM = faboPWM;
  this->channel = channel;
}

void CServo::Calibrate(int8_t offset) {
  this->Offset = offset;
}
int8_t CServo::Read() { return (int8_t)this->faboPWM.get_channel_value(this->channel); }
void CServo::Write(int8_t angle) {
  int8_t oangle = angle + this->Offset;
  if (this->Inverted) oangle *= -1;

  if (oangle > this->MaxAngle) { this->faboPWM.set_channel_value(this->channel, 415); return; }
  if (oangle < this->MinAngle) { this->faboPWM.set_channel_value(this->channel, 70); return; }

  this->faboPWM.set_channel_value(this->channel, map(oangle, -90, 90, 70, 415));
}
