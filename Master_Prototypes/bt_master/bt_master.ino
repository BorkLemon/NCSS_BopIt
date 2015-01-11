/*commands (that should work) :

0 --> motor moves backwards
1 --> motor moves forwards
2 --> red (RGB led)
3 --> green (RGB led)
4 --> blue (RGB led)
5 --> clear all (RGB led)
6 --> aution buzzer
7 --> fail buzzer
8 --> success
9 --> stop motor function*/


#include <SoftwareSerial.h>

const int RxD = 6;
const int TxD = 7;

SoftwareSerial btSerial(RxD, TxD);

void setup(){
  Serial.begin(9600);
  btSerial.begin(38400);
 pinMode(RxD, INPUT);
 pinMode(TxD, OUTPUT);
}

void loop(){
    if(Serial.available()) {
      while(Serial.available()) {
        btSerial.write(Serial.read());
        delay(10);
      }
    }
}
