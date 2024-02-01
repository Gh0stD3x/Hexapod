/*
 * Sketch     Twist body function example
 * Platform   Freenove Hexapod Robot (Compatible with Arduino/Genuino Mega 2560)
 * Brief      This sketch is used to show how to control Freenove Hexapod Robot with code.
 *            You can easily achieve custom function by using FNHR library we provide.
 * Note       Keep the power off when uploading the code to prevent the robot from suddenly moving 
 *            after the upload is complete. Before turning on the power, disconnect the USB cable 
 *            and place the robot on a smooth surface that has no other objects.
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
  // Custom setup code start

  // Custom setup code end
  // Start Freenove Hexapod Robot
  robot.Start();
}

void loop() {
  // Custom loop code start

  delay(2000);

  // Move body
  robot.MoveBody(0, 30, 0);
  robot.MoveBody(-30, 0, 0);
  robot.MoveBody(0, -30, 0);
  robot.MoveBody(30, 0, 0);
  robot.MoveBody(0, 0, 0);
  robot.MoveBody(0, 0, 45);
  robot.MoveBody(0, 0, 0);

  delay(1000);

  // Rotate body
  robot.RotateBody(15, 0, 0);
  robot.RotateBody(0, 15, 0);
  robot.RotateBody(-15, 0, 0);
  robot.RotateBody(0, -15, 0);
  robot.RotateBody(0, 0, 0);
  robot.RotateBody(0, 0, 15);
  robot.RotateBody(0, 0, -15);
  robot.RotateBody(0, 0, 0);

  // Sleep mode
  robot.SleepMode();
  
  while (true);
  // Custom loop code end
}
