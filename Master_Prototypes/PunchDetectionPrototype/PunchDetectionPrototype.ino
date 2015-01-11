const int ACCEL_PIN_X = A0;
const int ACCEL_PIN_Y = A1;
const int ACCEL_PIN_Z = A2;

const float PUNCH_SPIKE_HIGH = 4;
const float PUNCH_SPIKE_LOW = 0.5;
const float PUNCH_AVG = 2;
const float PUNCH_AVG_DEVIATION = 0.4;

bool punchSpike = false;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  
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

