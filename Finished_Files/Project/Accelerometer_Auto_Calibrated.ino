#include "Accelerometer_Auto_Calibrated.h"
 
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

void calibration (){  // autocalibrate the accelerometer
  int XCal[NUM_Samples];
  int YCal[NUM_Samples];
  int ZCal[NUM_Samples];
  int i;
  for (i = 0; i < NUM_Samples; i++){
    XCal[i] = analogRead(A0);
    YCal[i] = analogRead(A1);
    ZCal[i] = analogRead(A2);
  }
  xCorrection = averages (XCal); //calculating and returning x average
  yCorrection = averages (YCal); //calculating and returning x average
  zCorrection = averages (ZCal); //calculating and returning x average
  
  Serial.println(xCorrection);
  Serial.println(yCorrection);
  Serial.println(zCorrection);

}


void calibrationSetup() {
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  
  delay (1000);  //this avoids the spike in accelerometer when arduino turned on
  calibration();
  analogRead(A0);
  analogRead(A1);
  analogRead(A2);
  delay (1000);
    //would be good to a beep at the end of setup so everyone knows it is complete
 }

// Tests calibration
void debug() {
  //inputting data from each axes of accelerometer
  int XValue = analogRead(A0);
  int YValue = analogRead(A1);
  int ZValue = analogRead(A2);
  delay(1000);
 
  float XCorrected = XValue-xCorrection;    //this corrects for initial condition of accelerometer
  float YCorrected = YValue-yCorrection;
  float ZCorrected = ZValue-zCorrection;
  
  float VX = (XCorrected/1023.0*3.3);  //converts the corrected XValue input into volts
  float VY = (YCorrected/1023.0*3.3);
  float VZ = (ZCorrected/1023.0*3.3);
  
  float Xg = VX*7.281;  //converts corrected volts into gees for g-select mode (gs pin)(g forces)
  float Yg = VY*7.281;
  float Zg = ((VZ*7.281)+1);
    
  Serial.print(Xg);    //this can be deleted - but allows us to see if accelerometer is calibrated
  Serial.print(",");
  Serial.print(Yg);
  Serial.print(",");
  Serial.println(Zg);
  delay(1000);        //this delay is not necessary, but reduces load when printing the X,Y,Z values
}
