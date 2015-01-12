#define SAMPLES 10
#define BUZZPIN 11
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
boolean BowStart=false;



void Cal2ndAccel(){ //Calibration function - no return because of global variables.
  float sumX= 0.0; //Arrays for averaging calibration values for X, Y and Z 
  float sumY= 0.0;
  float sumZ= 0.0;
  for (int i=0; i<SAMPLES; i++){
    XValue = analogRead(A3); //read the Analogue inputs
    YValue = analogRead(A4);
    ZValue = analogRead(A5);
    xV = XValue*3.3/1023; //convert to voltages

    yV = YValue*3.3/1023;
    zV = ZValue*3.3/1023;
    xG = xV*1.5/0.8; //convert to Gravities
    yG = yV*1.5/0.8+1;
    zG = zV*1.5/0.8;   
    sumX+=xG;
    sumY+=yG;
    sumZ+=zG;
  xCal = sumX/SAMPLES; //Calibration values for X Y and Z
  yCal = sumY/SAMPLES;
  zCal = sumZ/SAMPLES;
  delay(50);
  }
  
}
//z<.2 z>=.9
boolean Bow(float x, float y, float z){ //Returns T or F based on whether the movement sent was a valid bow
  
  Serial.print(y);
  Serial.print("--");
  Serial.print(z);
  Serial.println();
  
  if (!BowStart && y<=-0.9){
    BowStart = true;
    tone(BUZZPIN,400,500);
    Serial.println("Hooray - start");
    delay(500);
  }
  else if(BowStart && y<0.10 && y>=-0.1){
    Serial.println("Hooray - finish");
    BowStart = false;
    return true;
  }
  else{
    return false;
  }
  //If we're going to use this function more than once we need to set ARaiseStart to false before we enter the loop
}

void setup(){
  Serial.begin(9600); //Turn on the Serial Bus for the Srial Monitor
  delay(2000); //delay to pass by the spike in voltages on pins at startup
  Cal2ndAccel();
  pinMode(BUZZPIN,OUTPUT); 
}

void loop (){
  XValue = analogRead(A3);
  YValue = analogRead(A4);
  ZValue = analogRead(A5);
  xV = XValue*3.3/1023;
  yV = YValue*3.3/1023;
  zV = ZValue*3.3/1023;
  xG = xV*1.5/0.8-xCal;
  yG = yV*1.5/0.8-yCal;
  zG = zV*1.5/0.8-zCal;  
  if (Bow(xG,yG,zG)){
    tone(BUZZPIN,800,500);
    delay(500);
  }
  
  Serial.print("x - ");
  Serial.println(xG);
  Serial.print("y - ");
  Serial.println(yG);
  Serial.print("z - ");
  Serial.println(zG);
  Serial.println();
  delay (1000);
}
  
