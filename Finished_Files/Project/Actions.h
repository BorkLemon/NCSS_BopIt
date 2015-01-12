#ifndef _Actions_h
#define _Actions_h

#define ACCEL_PIN_X A0
#define ACCEL_PIN_Y A2
#define ACCEL_PIN_Z A5

const float PUNCH_SPIKE_HIGH = 1;
const float PUNCH_SPIKE_LOW = -1;

const float JUMP_SPIKE_HIGH = 1.2;
const float JUMP_SPIKE_LOW = -1.5;

bool punchSpike = false;
bool jumpSpike = false;
bool jumpLow = false;

// Detect jumping action
bool jump();
// Detect punch action
bool punch();

bool armRaiseStart = false;

// Detect arm raise
bool armRaise();

float readGees(int pin, int correction);

#endif
