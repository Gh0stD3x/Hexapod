/*
 * Sketch     Modify wireless communication channel of the robot
 * Platform   Freenove Hexapod Robot (Compatible with Arduino/Genuino Mega 2560)
 * Brief      This sketch is used to show how to modify wireless communication channel between robot
 *            and remote when using default function.
 *            The remote control should set the same channel to control robot.
 * Author     Ethan Pan @ Freenove (support@freenove.com)
 * Date       2020/04/24
 * Copyright  Copyright © Freenove (http://www.freenove.com)
 * License    Creative Commons Attribution ShareAlike 3.0
 *            (http://creativecommons.org/licenses/by-sa/3.0/legalcode)
 * -----------------------------------------------------------------------------------------------*/

#ifndef ARDUINO_AVR_MEGA2560
#error Wrong board. Please choose "Arduino/Genuino Mega or Mega 2560"
#endif

// Include FNHR (Freenove Hexapod Robot) library
#include <FNHR.h>

FNHR robot;

void setup() {
  // Set wireless communication channel
  // Call this function before robot.Start()
  // The channel can be set to 0~125, default is 125
  robot.SetRemoteChannel(100);
  // Start Freenove Hexapod Robot with default function
  robot.Start(true);
}

void loop() {
  // Update Freenove Hexapod Robot
  robot.Update();
}
