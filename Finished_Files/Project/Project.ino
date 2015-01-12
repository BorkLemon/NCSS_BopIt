#include "Bluetooth_Remote.h"
#include "Actions.h"
#include "Accelerometer_Auto_Calibrated.h"
#include "Robot.h"
#include "Rand_Func.h"

const int TIME_LIMIT = 5000; // ms

// Commands for the player
const int NONE = 0;
const int PUNCH = 1; // red
const int JUMP = 2;  // green
const int MAX_COMMAND = JUMP;

int current_action = NONE;
int past_time;

void setup() {
  Serial.begin(9600);
  bluetoothSetup();    // RELIES ON BLUETOOTH CODE
  calibrationSetup();  // RELIES ON CALIBRATION CODE
  
  //assignAction();
}

void loop() {
  // IF PLAYER TIMES OUT BEFORE COMPLETING ACTION, ACTION STATES WILL NOT BE RESET
  
  // player fails the action  
  if(punch()) {
     btSerial.write(FORWARDS);
  }
  
  
  
  //jump();
//  if (millis() > past_time + TIME_LIMIT) {
//    
//  }
//  
//  if ((current_action == PUNCH && punch()) ||
//    (current_action == JUMP && jump())) {
//    btSerial.write(FORWARDS);
//    assignAction();
//  }
  
}

void assignAction() {
  int action = randomise(3);
 
  btSerial.write(LIGHT_ONE_OFF);
  btSerial.write(LIGHT_TWO_OFF);
  
  switch(action) {
    case PUNCH: btSerial.write(LIGHT_ONE_RED); break;
    case JUMP: btSerial.write(LIGHT_ONE_GREEN); break;
  }
  
  past_time = millis();
  
  current_action = action;
}









