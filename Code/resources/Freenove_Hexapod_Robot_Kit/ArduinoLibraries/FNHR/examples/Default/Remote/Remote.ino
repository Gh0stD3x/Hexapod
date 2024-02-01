/*
 * Sketch     Default function sketch for remote
 * Platform   Freenove Smart Car Remote (Compatible with Arduino/Genuino Uno)
 * Brief      This sketch is used to control Freenove Hexapod Robot by Remote.
 *            Turn on button/switch S1, S2 or S3 to experience different modes of the robot:
 *              S1  S2  S3
 *              On  Off Off - Crawl in any direction
 *              On  On  Off - Crawl forward and backward, turn left and right
 *              Off On  Off - Move body
 *              Off On  On  - Rotate body based on move body
 *              Off Off On  - Rotate body
 *            Changing the code will make the remote function not working properly.
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
  // Start remote
  remote.Start();
}

void loop() {
  // Update remote
  remote.Update();
}
