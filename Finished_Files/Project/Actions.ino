#include "Actions.h"
#include "Accelerometer_Auto_Calibrated.h"

// Detects a jumping action
bool jump() {
  
  // get accelerometer value from z axis
  float geesY = readGees(ACCEL_PIN_Y, yCorrection); // Zave DEPENDENT ON CALIBRATION CODE
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


// Detects a 'punching' action
bool punch() {
  // TODO (OPTIONAL) Add policing for backward punches
  
  // load accelerometer gees from x axis
  float geesY = readGees(ACCEL_PIN_Y, yCorrection); // Xave DEPENDENT ON CALIBRATION CODE

  // Detects a spike in the x axis as a punching action
  if (geesY > PUNCH_SPIKE_HIGH) {
    punchSpike = true;
  }
  
  // Detects a dip in the x axis to confirm the end of the punching action
  if (geesY < PUNCH_SPIKE_LOW && punchSpike) {
      Serial.println("PUNCH DETECTED");
      punchSpike = false;
      return true;
  } 
  
  // Occurs when a punch is not detected
  return false;
}

// Detects an arm raising action NOT YET PROPERLY IMPLEMENTED
bool ARaise(){ //Returns T or F based on whether the movement sent was a valid bow
  
  float x = readGees(ACCEL_PIN_X, xCorrection);
  float y = readGees(ACCEL_PIN_Y, yCorrection);
  float z = readGees(ACCEL_PIN_Z, zCorrection);
  
  Serial.print(y);
  Serial.print("--");
  Serial.print(z);
  Serial.println();
  
  if (!ARaiseStart && y > z){
    ARaiseStart = true;
    // IMPLEMENT LATER
//    tone(BUZZPIN,400,500);
//    Serial.println("Hooray - start");
//    delay(500);
  }
  else if(ARaiseStart && z>y){
    Serial.println("Hooray - finish");
    ARaiseStart = false;
    return true;
  }
  else{
    return false;
  }
  //If we're going to use this function more than once we need to set ARaiseStart to false before we enter the loop
}

// Read analog input from accelerometer in gees
float readGees(int pin, int correction) {
   int input = analogRead(pin) - correction; // ADDED CORRECTION CODE FROM CALLIBRATION
   float volts = (input/1023.0)*3.3;
   float gees = ((volts*1.5)/0.8);
   return gees;
}
