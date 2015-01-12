#ifndef _Accelerometer_Auto_Calibrated_h
#define _Accelerometer_Auto_Calibrated_h

//Sets number of accelerometer readings to 10
int NUM_Samples = 10;  
float xCorrection;
float yCorrection;
float zCorrection;

//Calulate float average - general
float averages(int cals[]);

// autocalibrate the accelerometer
void calibration ();

// initialised calibration
void calibrationSetup();
 
// Test calibration
void debug();
 
#endif
