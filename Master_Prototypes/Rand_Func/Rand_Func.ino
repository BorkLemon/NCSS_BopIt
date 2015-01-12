#define NUM 3 //this is the number of moves in the game
long time_to_print=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int Randomise(){
  return millis()%NUM;
}
void loop() {
  // put your main code here, to run repeatedly:
  int r = Randomise(); 
  if (time_to_print<=millis()){
    Serial.print(r);
    time_to_print = millis()+2000;
  }
  
  
}


