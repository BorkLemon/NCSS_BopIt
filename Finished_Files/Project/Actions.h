#ifndef _Actions_h
#define _Actions_h

#define ACCEL_PIN_X A0
#define ACCEL_PIN_Y A2
#define ACCEL_PIN_Z A5

const float PUNCH_SPIKE_HIGH = 1.5;
const float PUNCH_SPIKE_LOW = -1.5;

const float JUMP_SPIKE_HIGH = 1.2;
const float JUMP_SPIKE_LOW = -1.5;

bool punchSpike = false;
bool jumpSpike = false;
bool jumpLow = false;

// Detect jumping action
bool jump();
// Detect punch action
bool punch();

const float ARM_RAISE_START_POS_Y = 0.9;
const float ARM_RAISE_START_POS_Z = -1.8;
const float ARM_RAISE_END_POS_Y = 0.2;
const float ARM_RAISE_END_POS_Z = -1.2;

bool armRaiseStart = false;

// Detect arm raise
bool armRaise();

float readGees(int pin, int correction);

#endif
