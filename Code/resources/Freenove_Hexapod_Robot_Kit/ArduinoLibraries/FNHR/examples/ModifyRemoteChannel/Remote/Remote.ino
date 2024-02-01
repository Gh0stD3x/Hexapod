/*
 * Sketch     Modify wireless communication channel of the remote
 * Platform   Freenove Smart Car Remote (Compatible with Arduino/Genuino Uno)
 * Brief      This sketch is used to show how to modify wireless communication channel between robot
 *            and remote when using default function.
 *            The robot should set the same channel to be able to controlled by romote.
 * Author     Ethan Pan @ Freenove (support@freenove.com)
 * Date       2020/04/24
 * Copyright  Copyright © Freenove (http://www.freenove.com)
 * License    Creative Commons Attribution ShareAlike 3.0
 *            (http://creativecommons.org/licenses/by-sa/3.0/legalcode)
 * -----------------------------------------------------------------------------------------------*/

#ifndef ARDUINO_AVR_UNO
#error Wrong board. Please choose "Arduino/Genuino Uno"
#endif

// Include FNHR (Freenove Hexapod Robot) library
#include <FNHR.h>

FNHRRemote remote;

void setup() {
  // Set wireless communication channel
  // Call this function before remote.Start()
  // The channel can be set to 0~125, default is 125
  remote.SetChannel(100);
  // Start remote
  remote.Start();
}

void loop() {
  // Update remote
  remote.Update();
}
