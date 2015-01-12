#include "Actions.h"
#include "Accelerometer_Auto_Calibrated.h"

// Detects an arm raising action (NON_FUNCTIONAL)
bool armRaise(){ //Returns T or F based on whether the movement sent was a valid bow
  
  float geesY = readGees(ACCEL_PIN_Y, yCorrection);
  float geesZ = readGees(ACCEL_PIN_Z, zCorrection);
  
  Serial.println(geesY);
  Serial.print(",");
  Serial.print(geesZ);
  
  // Detect if the arm is in the starting position
  if (!armRaiseStart && (geesY > geesZ)){
    armRaiseStart = true;
    Serial.println("Hooray - start");
  }
  
  // Check if the arm is in the arm raised position
  else if(armRaiseStart && (geesZ > geesY)){
    Serial.println("Hooray - finish");
    armRaiseStart = false;
    return true;
  }
  
  // Arm raise not detected
  return false;
}

// Detects a jumping action (FUNCTIONAL)
bool jump() {
  
  // get accelerometer value from z axis
  float geesY = readGees(ACCEL_PIN_Y, zCorrection); // Zave DEPENDENT ON CALIBRATION CODE
  // Detects a spike in the Z axis as a jumping action
    
  if (geesY > JUMP_SPIKE_HIGH) {
    if (jumpLow) {
      Serial.println("JUMP DETECTED");
      jumpLow = false;
      return true;
    }
    else
      jumpSpike = true;
  }
  
  // Detects a drop in the Z axis to confirm the end of the jump
  if (geesY < JUMP_SPIKE_LOW && jumpSpike) {
      jumpSpike = false;
      jumpLow = true;
  } 
  // Occurs when a jump is not detected
  return false;
}


// Detects a 'punching' action (FUNCTIONAL)
bool punch() {
  // TODO (OPTIONAL) Add policing for backward punches
  
  // load accelerometer gees from y axis
  float geesY = readGees(ACCEL_PIN_Y, yCorrection); // yCorrection DEPENDENT ON CALIBRATION CODE

  // Detects a spike in the y axis as a punching action
  if (geesY > PUNCH_SPIKE_HIGH) {
    punchSpike = true;
  }
  
  // Detects a dip in the y axis to confirm the end of the punching action
  if (geesY < PUNCH_SPIKE_LOW && punchSpike) {
      Serial.println("PUNCH DETECTED");
      punchSpike = false;
      return true;
  } 
  
  // Occurs when a punch is not detected
  return false;
}

// Read analog input from accelerometer in gees
float readGees(int pin, int correction) {
   int input = analogRead(pin) - correction; // ADDED CORRECTION CODE FROM CALLIBRATION
   float volts = (input/1023.0)*3.3;
   float gees = ((volts*1.5)/0.8);
   return gees;
}
