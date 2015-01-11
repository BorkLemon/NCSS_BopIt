const int ACCEL_PIN_X = A0;
const int ACCEL_PIN_Y = A1;
const int ACCEL_PIN_Z = A2;

const float PUNCH_SPIKE_HIGH = 4;
const float PUNCH_SPIKE_LOW = 0.5;
const float JUMP_SPIKE_HIGH = 3.5;
const float JUMP_SPIKE_LOW = 2;

bool punchSpike = false;
bool jumpSpike = false;
bool jumpLow = false;

void setup() {
  Serial.begin(9600);
  
}
void loop() {
 // float GeesZ = readGees(ACCEL_PIN_Z);  
 // Serial.println(GeesZ);
 // delay(100);
  jump();
}

// Detects a jumping action
bool jump() {
  
  // get accelerometer value from z axis
  float geesZ = readGees(ACCEL_PIN_Z);
  // Detects a spike in the Z axis as a jumping action
  if (geesZ > JUMP_SPIKE_HIGH) {
    if (jumpLow) {
      Serial.println("JUMP DETECTED");
      jumpLow = false;
      return true;
    }
    else
      jumpSpike = true;
  }
  
  // Detects a drop in the Z axis to confirm the end of the jump
  if (geesZ < JUMP_SPIKE_LOW && jumpSpike) {
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
  float geesX = readGees(ACCEL_PIN_X);
  
  // Detects a spike in the x axis as a punching action
  if (geesX > PUNCH_SPIKE_HIGH) {
    punchSpike = true;
  }
  
  // Detects a dip in the x axis to confirm the end of the punching action
  if (geesX < PUNCH_SPIKE_LOW && punchSpike) {
      punchSpike = false;
      return true;
      Serial.println("PUNCH DETECTED");
  } 
  
  // Occurs when a punch is not detected
  return false;
}

// Read analog input from accelerometer in gees
float readGees(int pin) {
   int input = analogRead(pin);
   float volts = (input/1023.0)*3.3;
   float gees = ((volts*1.5)/0.8);
   return gees;
}

