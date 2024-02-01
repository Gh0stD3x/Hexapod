
#include "FaBoPWM_PCA9685.h"
#include <EEPROM.h>

#include "Servo.h"
#include "Leg.h"



FaBoPWM faboPWM(0x40);
FaBoPWM faboPWM2(0x41);

CServo FRHip;
CServo FRKnee;
CServo FRAnkle;

CServo FLHip;
CServo FLKnee;
CServo FLAnkle;


CServo MRHip;
CServo MRKnee;
CServo MRAnkle;

CServo MLHip;
CServo MLKnee;
CServo MLAnkle;


CServo BRHip;
CServo BRKnee;
CServo BRAnkle;

CServo BLHip;
CServo BLKnee;
CServo BLAnkle;



Leg FRLeg;
Leg FLLeg;

Leg MRLeg;
Leg MLLeg;

Leg BRLeg;
Leg BLLeg;






String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void processCommand(String cmd) {
  if (cmd.startsWith("[SET][SERVO]")) {
    cmd.replace("[SET][SERVO]", "");

    if (cmd.startsWith("[FRONT:")) {
      cmd.replace("[FRONT:", "");

      if (cmd.startsWith("RIGHT:")) {
        cmd.replace("RIGHT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          FRHip.Write(cmd.toInt());
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          FRKnee.Write(cmd.toInt());
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          FRAnkle.Write(cmd.toInt());
        }
      } else if (cmd.startsWith("LEFT:")) {
        cmd.replace("LEFT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          FLHip.Write(cmd.toInt());
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          FLKnee.Write(cmd.toInt());
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          FLAnkle.Write(cmd.toInt());
        }
      }
    } else if (cmd.startsWith("[MIDDLE:")) {
      cmd.replace("[MIDDLE:", "");

      if (cmd.startsWith("RIGHT:")) {
        cmd.replace("RIGHT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          MRHip.Write(cmd.toInt());
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          MRKnee.Write(cmd.toInt());
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          MRAnkle.Write(cmd.toInt());
        }
      } else if (cmd.startsWith("LEFT:")) {
        cmd.replace("LEFT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          MLHip.Write(cmd.toInt());
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          MLKnee.Write(cmd.toInt());
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          MLAnkle.Write(cmd.toInt());
        }
      }
    } else if (cmd.startsWith("[BACK:")) {
      cmd.replace("[BACK:", "");

      if (cmd.startsWith("RIGHT:")) {
        cmd.replace("RIGHT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          BRHip.Write(cmd.toInt());
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          BRKnee.Write(cmd.toInt());
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          BRAnkle.Write(cmd.toInt());
        }
      } else if (cmd.startsWith("LEFT:")) {
        cmd.replace("LEFT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          BLHip.Write(cmd.toInt());
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          BLKnee.Write(cmd.toInt());
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          BLAnkle.Write(cmd.toInt());
        }
      }
    }
  } // Cmd: [SET][SERVO][FRONT:RIGHT:ANKLE] = 90
  else if (cmd.startsWith("[RESET][LEG]")) {
    cmd.replace("[RESET][LEG]", "");
    if (cmd.startsWith("[FRONT:RIGHT]")) FRLeg.Reset();
    else if (cmd.startsWith("[FRONT:LEFT]")) FLLeg.Reset();
    else if (cmd.startsWith("[MIDDLE:RIGHT]")) MRLeg.Reset();
    else if (cmd.startsWith("[MIDDLE:LEFT]")) MLLeg.Reset();
    else if (cmd.startsWith("[BACK:RIGHT]")) BRLeg.Reset();
    else if (cmd.startsWith("[BACK:LEFT]")) BLLeg.Reset();
    else if (cmd.startsWith("[ALL:RIGHT]")) {
      FRLeg.Reset();
      MRLeg.Reset();
      BRLeg.Reset();
    } else if (cmd.startsWith("[ALL:LEFT]")) {
      FLLeg.Reset();
      MLLeg.Reset();
      BLLeg.Reset();
    } else if (cmd.startsWith("[ALL:ALL]")) {
      FRLeg.Reset();
      FLLeg.Reset();
      MRLeg.Reset();
      MLLeg.Reset();
      BRLeg.Reset();
      BLLeg.Reset();
    }
  } // Cmd: [RESET][LEG][FRONT:RIGHT]
  else if (cmd.startsWith("[CALIBRATE][SERVO]")) {
    cmd.replace("[CALIBRATE][SERVO]", "");

    if (cmd.startsWith("[FRONT:")) {
      cmd.replace("[FRONT:", "");

      if (cmd.startsWith("RIGHT:")) {
        cmd.replace("RIGHT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          FRHip.Offset = cmd.toInt();
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          FRKnee.Offset = cmd.toInt();
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          FRAnkle.Offset = cmd.toInt();
        }
      } else if (cmd.startsWith("LEFT:")) {
        cmd.replace("LEFT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          FLHip.Offset = cmd.toInt();
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          FLKnee.Offset = cmd.toInt();
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          FLAnkle.Offset = cmd.toInt();
        }
      }
    } else if (cmd.startsWith("[MIDDLE:")) {
      cmd.replace("[MIDDLE:", "");

      if (cmd.startsWith("RIGHT:")) {
        cmd.replace("RIGHT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          MRHip.Offset = cmd.toInt();
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          MRKnee.Offset = cmd.toInt();
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          MRAnkle.Offset = cmd.toInt();
        }
      } else if (cmd.startsWith("LEFT:")) {
        cmd.replace("LEFT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          MLHip.Offset = cmd.toInt();
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          MLKnee.Offset = cmd.toInt();
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          MLAnkle.Offset = cmd.toInt();
        }
      }
    } else if (cmd.startsWith("[BACK:")) {
      cmd.replace("[BACK:", "");

      if (cmd.startsWith("RIGHT:")) {
        cmd.replace("RIGHT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          BRHip.Offset = cmd.toInt();
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          BRKnee.Offset = cmd.toInt();
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          BRAnkle.Offset = cmd.toInt();
        }
      } else if (cmd.startsWith("LEFT:")) {
        cmd.replace("LEFT:", "");

        if (cmd.startsWith("HIP] = ")) {
          cmd.replace("HIP] = ", "");

          BLHip.Offset = cmd.toInt();
        } else if (cmd.startsWith("KNEE] = ")) {
          cmd.replace("KNEE] = ", "");

          BLKnee.Offset = cmd.toInt();
        } else if (cmd.startsWith("ANKLE] = ")) {
          cmd.replace("ANKLE] = ", "");

          BLAnkle.Offset = cmd.toInt();
        }
      }
    }
  } // Cmd: [CALIBRATE][SERVO][FRONT:RIGHT:HIP] = -5
  else if (cmd.startsWith("[STORE][CALIBRATION]")) {
    EEPROM.write(0x20, FRHip.Offset);
    EEPROM.write(0x21, FRKnee.Offset);
    EEPROM.write(0x22, FRAnkle.Offset);

    EEPROM.write(0x23, MRHip.Offset);
    EEPROM.write(0x24, MRKnee.Offset);
    EEPROM.write(0x25, MRAnkle.Offset);

    EEPROM.write(0x26, BRHip.Offset);
    EEPROM.write(0x27, BRKnee.Offset);
    EEPROM.write(0x28, BRAnkle.Offset);

    EEPROM.write(0x29, FLHip.Offset);
    EEPROM.write(0x30, FLKnee.Offset);
    EEPROM.write(0x31, FLAnkle.Offset);

    EEPROM.write(0x32, MLHip.Offset);
    EEPROM.write(0x33, MLKnee.Offset);
    EEPROM.write(0x34, MLAnkle.Offset);

    EEPROM.write(0x35, BLHip.Offset);
    EEPROM.write(0x36, BLKnee.Offset);
    EEPROM.write(0x37, BLAnkle.Offset);

    EEPROM.commit();
  }
  else if (cmd.startsWith("[LOAD][CALIBRATION]")) {
    FRHip.Offset = EEPROM.readChar(0x20);
    FRKnee.Offset = EEPROM.readChar(0x21);
    FRAnkle.Offset = EEPROM.readChar(0x22);

    MRHip.Offset = EEPROM.readChar(0x23);
    MRKnee.Offset = EEPROM.readChar(0x24);
    MRAnkle.Offset = EEPROM.readChar(0x25);

    BRHip.Offset = EEPROM.readChar(0x26);
    BRKnee.Offset = EEPROM.readChar(0x27);
    BRAnkle.Offset = EEPROM.readChar(0x28);

    FLHip.Offset = EEPROM.readChar(0x29);
    FLKnee.Offset = EEPROM.readChar(0x30);
    FLAnkle.Offset = EEPROM.readChar(0x31);

    MLHip.Offset = EEPROM.readChar(0x32);
    MLKnee.Offset = EEPROM.readChar(0x33);
    MLAnkle.Offset = EEPROM.readChar(0x34);

    BLHip.Offset = EEPROM.readChar(0x35);
    BLKnee.Offset = EEPROM.readChar(0x36);
    BLAnkle.Offset = EEPROM.readChar(0x37);

    processCommand("[RESET][LEG][ALL:ALL]");
  }
}


void setup() {
  Serial.begin(115200);
  Serial.print("[PCA9685]EEPROM...\t");
  if (EEPROM.begin(0x50)) {
    Serial.println("Success");
  } else {
    Serial.println("Failed");
  }

  Serial.print("[PCA9685]Init...\t");
  if (faboPWM.begin()) {
    faboPWM.init(300);
    Serial.println("Success");
  }
  else {
    Serial.println("Failed");
  }
  Serial.print("[PCA9685]Init2...\t");
  if (faboPWM2.begin()) {
    faboPWM2.init(300);
    Serial.println("Success");
  }
  else {
    Serial.println("Failed");
  }

  Serial.print("[PCA9685]Set Freq...\t");
  faboPWM.set_hz(50);
  faboPWM2.set_hz(50);
  Serial.println("Success");


  Serial.print("[SERVO]Init...\t");
// Back servos
  BRHip.Attach(faboPWM, 0);
  BRKnee.Attach(faboPWM, 1);
  BRAnkle.Attach(faboPWM, 2);

  BRLeg.Attach(BRHip, BRKnee, BRAnkle);

  BLHip.Attach(faboPWM2, 15);
  BLKnee.Attach(faboPWM2, 14);
  BLAnkle.Attach(faboPWM2, 13);

  BLLeg.Attach(BLHip, BLKnee, BLAnkle);

// Middle servos
  MRHip.Attach(faboPWM, 4);
  MRKnee.Attach(faboPWM, 5);
  MRAnkle.Attach(faboPWM, 6);
  
  MRLeg.Attach(MRHip, MRKnee, MRAnkle);

  MLHip.Attach(faboPWM2, 11);
  MLKnee.Attach(faboPWM2, 10);
  MLAnkle.Attach(faboPWM2, 9);
  
  MLLeg.Attach(MLHip, MLKnee, MLAnkle);

// Front servos
  FRHip.Attach(faboPWM, 8);
  FRKnee.Attach(faboPWM, 9);
  FRAnkle.Attach(faboPWM, 10);
  
  FRLeg.Attach(FRHip, FRKnee, FRAnkle);

  FLHip.Attach(faboPWM2, 7);
  FLKnee.Attach(faboPWM2, 6);
  FLAnkle.Attach(faboPWM2, 5);
  
  FLLeg.Attach(FLHip, FLKnee, FLAnkle);
  Serial.println("Success");
}

void loop() {
  Serial.print("> ");

  while (Serial.available() <= 0);
  String cmd = Serial.readStringUntil('\n');
  Serial.println(cmd);
  processCommand(cmd);
}
