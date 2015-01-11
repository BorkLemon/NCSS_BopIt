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
    if(btSerial.available()) {
       while(btSerial.available()) {
          Serial.write(btSerial.read());
          delay(10);
       } 
    }
    if(Serial.available()) {
      while(Serial.available()) {
        btSerial.write(Serial.read());
        delay(10);
      }
    }
}
