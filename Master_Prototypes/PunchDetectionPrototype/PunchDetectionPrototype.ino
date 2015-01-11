// CALIBRATION CODE REMOVE LATER !!!

int Cal;     
int NUM_Samples = 10;  //Sets number of accelerometer readings to 10
float Xave;
float Yave;
float Zave;
 
float averages(int cals[]){    //Calulate float average - general
    float sum = 0.0;
    float average = 0.0;
    int i;
    for (i = 0; i < NUM_Samples; i++){
      sum += cals[i];
      }
    average = (sum/NUM_Samples);
    return average;
}

void Calibration (){  // autocalibrate the accelerometer
  int XCal[NUM_Samples];
  int YCal[NUM_Samples];
  int ZCal[NUM_Samples];
  int i;
  for (i = 0; i < NUM_Samples; i++){
    XCal[i] = analogRead(A0);
    YCal[i] = analogRead(A1);
    ZCal[i] = analogRead(A2);
  }
  Xave = averages (XCal); //calculating and returning x average
  Yave = averages (YCal); //calculating and returning x average
  Zave = averages (ZCal); //calculating and returning x average
  
  Serial.println(Xave);
  Serial.println(Yave);
  Serial.println(Zave);

}

void calibrationSetup() {
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  delay (1000);  //this avoids the spike in accelerometer when arduino turned on
  Calibration();
  analogRead(A0);
  analogRead(A1);
  analogRead(A2);
  delay (1000);
    //would be good to a beep at the end of setup so everyone knows it is complete
 }

// END REMOVE!!!!

// BLUETOOTH CODE
#include <SoftwareSerial.h>

const int RxD = 6;
const int TxD = 7;

const char ROBOT_FORWARD = '1';

SoftwareSerial btSerial(RxD, TxD);

void bluetoothSetup() {
  btSerial.begin(38400);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
}
//



const int ACCEL_PIN_X = A0;
const int ACCEL_PIN_Y = A1;
const int ACCEL_PIN_Z = A2;

// CAUSES CALIBRATION ISSUES!!!
const float PUNCH_SPIKE_HIGH = 1.9;
const float PUNCH_SPIKE_LOW = -1.9;
const float JUMP_SPIKE_HIGH = 1.2;
const float JUMP_SPIKE_LOW = -1.5;
//

bool punchSpike = false;
bool jumpSpike = false;
bool jumpLow = false;

void setup() {
  Serial.begin(9600);
  bluetoothSetup();    // RELIES ON BLUETOOTH CODE
  calibrationSetup();  // RELIES ON CALIBRATION CODE
}

void loop() {
  
  // Checks if the player is punching or jumping and moves the robot forward
  if(jump() || punch()) {
    btSerial.write(ROBOT_FORWARD); // RELIES ON BLUETOOTH CODE
    Serial.println("check");
  }
}

// Detects a jumping action
bool jump() {
  
  // get accelerometer value from z axis
  float geesY = readGees(ACCEL_PIN_Y, Yave); // Zave DEPENDENT ON CALIBRATION CODE
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
  float geesY = readGees(ACCEL_PIN_Y, Yave); // Xave DEPENDENT ON CALIBRATION CODE

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

// Read analog input from accelerometer in gees
float readGees(int pin, int correction) {
   int input = analogRead(pin) - correction; // ADDED CORRECTION CODE FROM CALLIBRATION
   float volts = (input/1023.0)*3.3;
   float gees = ((volts*1.5)/0.8);
   return gees;
}







