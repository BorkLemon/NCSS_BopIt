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

int fr = 1;

SoftwareSerial btSerial(RxD, TxD);

void setup(){
  Serial.begin(9600);
  btSerial.begin(38400);
 pinMode(RxD, INPUT);
 pinMode(TxD, OUTPUT);
 Serial.println("Arduino online...");
}

void loop(){
  if(fr == 1){Serial.println("Serial input online, you can now send commands!!!");fr++;}
  if(btSerial.available()) {
      while(btSerial.available()) {
          Serial.write(btSerial.read());
      }
    }
    if(Serial.available()) {
      while(Serial.available()) {
        btSerial.write(Serial.read());
      }
    }
}
