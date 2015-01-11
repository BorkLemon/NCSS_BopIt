#define SAMPLES 10
float xCal = 0.0; //Calibration values for X Y and Z
float yCal = 0.0;
float zCal = 0.0;
int XValue;  //vlues read from X Y and Z
int YValue;
int ZValue;
float xV; //voltages from X Y and Z
float yV;
float zV;
float xG; //Acceleration readings for X, Y and Z
float yG;
float zG; 



void Cal(){ //Calibration function - no return because of global variables.
  float sumX= 0.0; //Arrays for averaging calibration values for X, Y and Z 
  float sumY= 0.0;
  float sumZ= 0.0;
  for (int i=0; i<SAMPLES; i++){
    XValue = analogRead(A0); //read the Analogue inputs
    YValue = analogRead(A1);
    ZValue = analogRead(A2);
    xV = XValue*3.3/1023; //convert to voltages

    yV = YValue*3.3/1023;
    zV = ZValue*3.3/1023;
    xG = xV*1.5/0.8; //convert to Gravities
    yG = yV*1.5/0.8;
    zG = zV*1.5/0.8-1;   
    sumX+=xG;
    sumY+=yG;
    sumZ+=zG;
  xCal = sumX/SAMPLES; //Calibration values for X Y and Z
  yCal = sumY/SAMPLES;
  zCal = sumZ/SAMPLES;
  delay(50);
  }
  
}

void setup(){
  Serial.begin(9600); //Turn on the Serial Bus for the Srial Monitor
  delay(2000); //delay to pass by the spike in voltages on pins at startup
  Cal();
}

void loop (){
  XValue = analogRead(A0);
  YValue = analogRead(A1);
  ZValue = analogRead(A2);
  xV = XValue*3.3/1023;
  yV = YValue*3.3/1023;
  zV = ZValue*3.3/1023;
  xG = xV*1.5/0.8;
  yG = yV*1.5/0.8;f
  zG = zV*1.5/0.8;  
  
  Serial.print("x - ");
  Serial.println(xG-xCal);
  Serial.print("y - ");
  Serial.println(yG-yCal);
  Serial.print("z - ");
  Serial.println(zG-zCal);
  Serial.println();
  delay (1000);
}
  
