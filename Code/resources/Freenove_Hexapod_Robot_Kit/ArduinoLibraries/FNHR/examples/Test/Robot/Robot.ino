/*
 * Sketch     Self diagnosis sketch for Robot
 * Platform   Freenove Quadruped/Hexapod Robot (Compatible with Arduino Mega 2560) with 
 *            Freenove Crawling Robot Controller V2.0, V3.x (Marked on the control board)
 * Brief      This sketch is used to diagnose the robot after it has been assembled.
 *            If your robot is not working properly, follow the steps below to diagnose and fix.
 * Steps      1. Install Wireless module (if have) and WLAN module (if have) to the robot.
 *            2. Turn off the power switch and then install full charged batteries to the robot.
 *            3. Connect robot to computer via USB cable and choose the right board and port.
 *               Then open Serial Moniter with baud 115200.
 *            4. Hold the bottom of the robot to prevent the servos from suddenly turning.
 *               Open the power switch and upolad this sketch to the robot.
 *               The Serial Moniter will show diagnostic information and the servos will turn to 
 *               installation state and then rotate slowly.
 *            5. Please check the diagnostic information and try to fix the problem.
 *               Then press the RESET button to run this sketch again to see if the problem has been fixed.
 *               If yes, please upload the default sketch again to verify if the robot is working properly.
 *               If no or you can't fix the problem, please send diagnostic information and how did the 
 *               robot behave to our support team (support@freenove.com).
 * Note       When you hold the the robot, your hand should be far away from the movable range of the legs.
 *            If your hand is clamped or any servo is jammed, please turn off the power switch immediately.
 * Author     Ethan Pan @ Freenove (support@freenove.com)
 * Date       2023/02/04
 * Version    V12.4
 * Copyright  Copyright © Freenove (http://www.freenove.com)
 * License    Creative Commons Attribution ShareAlike 3.0
 *            (http://creativecommons.org/licenses/by-sa/3.0/legalcode)
 * -----------------------------------------------------------------------------------------------*/

#ifndef ARDUINO_AVR_MEGA2560
#error Wrong board. Please choose "Arduino Mega or Mega 2560"
#endif

#include <EEPROM.h>
#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
#include <FlexiTimer2.h>

const int manufactureDataAddress = 0;
const int dataFormatVersionAddress = manufactureDataAddress + 0;
const int productVersionAddress = manufactureDataAddress + 3;
int dataFormatVersion = 0;
int productVersion = 0;

float externalReference = 0;
float batteryVoltage = 0; 

RF24 rf24 = RF24(9, 53);

Servo servos[18];
const int servosPins[] = { 22, 23, 24, 25, 26, 27, 28, 29, 30,
                           31, 32, 33, 34, 35, 36, 37, 38, 39 };
const int servosPowersPins[] = { A15, A14, A13 };

const int pins[] = { A1, 3, A0, 2, 21, 14, 20, 15 };

volatile int ledState = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");
  Serial.println("Freenove Crawling Robot Controller");
  Serial.println("------------------------------------------------------------------------------------------");

// Open LED buildin.
  Serial.println("Opening LED buildin...");
  pinMode(LED_BUILTIN, OUTPUT);

// Open I/O ports.
  Serial.println("Opening I/O ports...");
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

// Start timer.
  FlexiTimer2::set(200, UpdateService);
  FlexiTimer2::start();

// Get product version.
  dataFormatVersion = EEPROM.read(dataFormatVersionAddress);
  switch (dataFormatVersion) {
  case 1:
    productVersion = EEPROM.read(productVersionAddress);
    switch (productVersion / 10) {
    case 3:
      Serial.print("Product version: V");
      Serial.print(productVersion / 10);
      Serial.print(".");
      Serial.println(productVersion % 10);
      productVersion = 3;
      break;
    default:
      productVersion = 0;
      break;
    }
    break;
  case 20:
    Serial.println("Product version: V2.0");
    productVersion = 2;
    break;
  default:
    productVersion = 0;
    break;
  }
  if(productVersion == 0) {
    Serial.println("Product version: unknown. Please contact support and provide some photos of the controller.");
    ledState = 2;
    while(1);
  }

// Using 5V as reference, measure 2.5V reference voltage.
  float arefVoltage = analogRead(A6) * 5.0 / 1023;
  Serial.print("AREF voltage: ");
  Serial.print(arefVoltage);
  Serial.print("V. ");
  if (arefVoltage > 2.4 && arefVoltage < 2.6) {
    Serial.println("OK.");
  }
  else {
    Serial.println("NG. Hardware failure.");
    ledState = 3;
  }

// Using external reference, measure battery voltage.
  switch (productVersion) {
  case 2:
    analogReference(EXTERNAL);
    externalReference = 2.5 * 32 / (32 + 6.2);
    break;
  case 3:
    float defaultReference = 2.5 / analogRead(A6) * 1023;
    analogReference(EXTERNAL);
    externalReference = defaultReference * 2 / (6.2 + 2) / analogRead(A8) * 1023;
    break;
  }
  batteryVoltage = analogRead(A7) * externalReference / 1023 * (6.2 + 2.0) / 2.0;
  Serial.print("Battery voltage: ");
  Serial.print(batteryVoltage);
  Serial.print("V. ");
  if (batteryVoltage > 6.5 && batteryVoltage < 8.5) {
    Serial.println("OK.");
  }
  else {
    Serial.println("NG. No batteries/ Low battery voltage/ Power not opened.");
    ledState = 4;
  }

// Using external reference, measure 5V and 3.3 voltage.
  switch (productVersion) {
  case 3:
    float vccVoltage = analogRead(A8) * externalReference / 1023 * (6.2 + 2) / 2;
    Serial.print("VCC voltage: ");
    Serial.print(vccVoltage);
    Serial.print("V. ");
    if (vccVoltage > 4.8 && vccVoltage < 5.2) {
      Serial.println("OK.");
    }
    else {
      Serial.println("NG. Hardware failure.");
      ledState = 5;
    }

    float v33Voltage = analogRead(A9) * externalReference / 1023 * (6.2 + 2) / 2;
    Serial.print("3.3V voltage: ");
    Serial.print(v33Voltage);
    Serial.print("V. ");
    if (v33Voltage > 3.2 && v33Voltage < 3.4) {
      Serial.println("OK.");
    }
    else {
      Serial.println("NG. Hardware failure.");
      ledState = 6;
    }

    break;
  }

// Test Wireless module.
  pinMode(50, INPUT_PULLUP);
  if (rf24.begin()) {
    Serial.println("Wireless module: OK.");
  }
  else {
    Serial.println("Wireless module: NG. Module not inatalled/ Hardware failure.");
    ledState = 7;
  }

// Test WLAN module.
  Serial2.begin(115200);
  Serial2.setTimeout(200);
  Serial2.println("AT");
  if (Serial2.readString().indexOf("OK") != -1) {
    Serial.println("WLAN module: OK.");
  }
  else {
    Serial.println("WLAN module: NG. Module not inatalled/ Hardware failure.");
    ledState = 8;
  }

// Open power of servos.
  Serial.println("Opening power of servos...");
  switch (productVersion) {
  case 2:
    for (int i = 0; i < 3; i++) {
      pinMode(servosPowersPins[i], OUTPUT);
      digitalWrite(servosPowersPins[i], HIGH);
      delay(200);
    }
    break;
  case 3:
    for (int i = 0; i < 2; i++) {
      pinMode(servosPowersPins[i], OUTPUT);
      digitalWrite(servosPowersPins[i], HIGH);
      delay(200);
    }
  
  // Using external reference, measure power of servo voltage.
    float u1Voltage = analogRead(A12) * externalReference / 1023 * (6.2 + 2.0) / 2.0;
    float u2Voltage = analogRead(A11) * externalReference / 1023 * (6.2 + 2.0) / 2.0;
    Serial.print("DC voltage: ");
    Serial.print("U1: ");
    Serial.print(u1Voltage);
    Serial.print("V, ");
    Serial.print("U2: ");
    Serial.print(u2Voltage);
    Serial.print("V. ");
    if (u1Voltage > 4.8 && u1Voltage < 5.2 &&
        u2Voltage > 4.8 && u2Voltage < 5.2) {
      Serial.println("OK");
    }
    else {
      Serial.println("NG. Hardware failure.");
      ledState = 9;
    }
    break;
  }

  Serial.println("------------------------------------------------------------------------------------------");
  Serial.println("Attaching on servos...");

  delay(500);

// Attach servos.
  for (int i = 0; i < 18; i++) {
    servos[i].attach(servosPins[i]);
    servos[i].write(90);
    delay(50);
  }

  Serial.println("All servos are starting to rotate slowly...");

  delay(500);
}

void loop() {
// Sweep servos.
  static int angle = 90;
  static bool dir = true;
  const int range = 30;

  if(dir) angle++;
  else angle--;

  if(angle == 90 + range / 2) dir = false;
  if(angle == 90 - range / 2) dir = true;

  for (int i = 0; i < 18; i++)
    servos[i].write(angle);

// Using external reference, measure battery voltage.
  batteryVoltage = analogRead(A7) * externalReference / 1023 * (6.2 + 2.0) / 2.0;
  if (batteryVoltage < 5.5) {
    Serial.println("------------------------------------------------------------------------------------------");
    Serial.print("Battery voltage: ");
    Serial.print(batteryVoltage);
    Serial.print("V. ");
    Serial.println("NG. Batteries protected/ Low battery voltage/ Power closed.");
    while(true);
  }

  delay(50);
}

void UpdateService()
{
  sei();

  static int counter = 0;

  for (int i = 0; i < 4; i++)
    digitalWrite(pins[i], HIGH);
  for (int i = 4; i < 8; i++)
    digitalWrite(pins[i], LOW);
  digitalWrite(pins[counter % 8], counter % 8 < 4 ? LOW : HIGH);

  UpdateStateLED();

  counter++;
}

void UpdateStateLED()
{
  const static int stepLength = 2;
  const static int intervalSteps = 3;
  static int ledState = ::ledState;
  static int counter = 0;

  if (counter / stepLength < abs(ledState))
  {
    if (counter % stepLength == 0)
      SetStateLed(ledState > 0 ? HIGH : LOW);
    else if (counter % stepLength == stepLength / 2)
      SetStateLed(ledState > 0 ? LOW : HIGH);
  }

  counter++;

  if (counter / stepLength >= abs(ledState) + intervalSteps)
  {
    ledState = ::ledState;
    counter = 0;
  }
}

void SetStateLed(bool state)
{
  digitalWrite(LED_BUILTIN, state);
}
