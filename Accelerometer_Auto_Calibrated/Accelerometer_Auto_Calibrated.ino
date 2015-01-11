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


void setup() {
  Serial.begin(9600);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  delay (1000);  //this avoids the spike in accelerometer when arduino turned on
  Calibration();
  int XValue = analogRead(A0);
  int YValue = analogRead(A1);
  int ZValue = analogRead(A2);
  delay (1000);
    //would be good to a beep at the end of setup so everyone knows it is complete
 }

void loop() {
  
  //inputting data from each axes of accelerometer
  int XValue = analogRead(A0);
  int YValue = analogRead(A1);
  int ZValue = analogRead(A2);
  delay(1000);
 
  float XCorrected = XValue-Xave;    //this corrects for initial condition of accelerometer
  float YCorrected = YValue-Yave;
  float ZCorrected = ZValue-Zave;
  
  float VX = (XCorrected/1023.0*3.3);  //converts the corrected XValue input into volts
  float VY = (YCorrected/1023.0*3.3);
  float VZ = (ZCorrected/1023.0*3.3);
  
  float Xg = VX*7.281;  //converts corrected volts into gees for g-select mode (gs pin)(g forces)
  float Yg = VY*7.281;
  float Zg = (VZ*7.281+1);
    
  Serial.print(Xg);    //this can be deleted - but allows us to see if accelerometer is calibrated
  Serial.print(",");
  Serial.print(Yg);
  Serial.print(",");
  Serial.println(Zg);
  delay(1000);        //this delay is not necessary, but reduces load when printing the X,Y,Z values

}
