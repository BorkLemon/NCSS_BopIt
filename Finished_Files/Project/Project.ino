#include "Bluetooth_Remote.h"
#include "Actions.h"
#include "Accelerometer_Auto_Calibrated.h"

void setup() {
  Serial.begin(9600);
  //bluetoothSetup();    // RELIES ON BLUETOOTH CODE
  calibrationSetup();  // RELIES ON CALIBRATION CODE
}

void loop() {
  // Checks if the player is punching or jumping and moves the robot forward
  if(jump() || punch()) {
    //btSerial.write(ROBOT_FORWARD); // RELIES ON BLUETOOTH CODE
    Serial.println("check");
  }
}









