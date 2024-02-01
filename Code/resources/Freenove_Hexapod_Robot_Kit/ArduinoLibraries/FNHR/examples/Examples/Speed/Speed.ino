/*
 * Sketch     Action speed function example
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

  // Set speed to 100
  robot.SetActionSpeed(100);
  // Crawl forward
  robot.CrawlForward();
  robot.CrawlForward();
  robot.CrawlForward();
  robot.CrawlForward();
  delay(1000);

  // Set speed to 50
  robot.SetActionSpeed(50);
  // Crawl forward
  robot.CrawlForward();
  robot.CrawlForward();
  robot.CrawlForward();
  robot.CrawlForward();
  delay(1000);

  // Set speed to 25
  robot.SetActionSpeed(25);
  // Crawl forward
  robot.CrawlForward();
  robot.CrawlForward();
  robot.CrawlForward();
  robot.CrawlForward();
  delay(1000);

  // Sleep mode
  robot.SwitchMode();

  while (true);
  // Custom loop code end
}
