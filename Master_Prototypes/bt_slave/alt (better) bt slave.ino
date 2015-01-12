#include <SoftwareSerial.h>                  // Include serial library
#include <Servo.h>                           // Include servo library 

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

const int RxD = 6;                           // Set up connection
const int TxD = 7;

long et = 1;

int f = 0;
int b = 0;

SoftwareSerial btSerial(RxD, TxD);

void setup() {
  Serial.begin(9600);
  btSerial.begin(38400);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.println("running");
}


void loop() {

  if (btSerial.available()) {
    //stuff
    while (btSerial.available()) {
      int i = btSerial.read();
      if (millis() < 10) {
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        et = 1;    
      }
      if ( i == '0' ) {                     // if 0 is recived from cereal, back
        ton(500, 200);
        if ( f == 1 ) {
          b = 1;
          f = 0;
          et = 1;
        }
        b = 1;
        motor(1700, 1300);
      }
      if ( i == '1' ) {                     // if 1 received from sensor, forward
        ton(2000, 200);
        if ( b == 1 ) {
          b = 0;
          f = 1;
          et = 1;
        }
        Serial.println("run!");
        f = 1;
        motor(1300, 1700);
      }
      if ( i == '2' ) {
        digitalWrite(8, HIGH);
      }      
      if ( i == '3' ) {
        digitalWrite(9, HIGH);
      }
      if ( i == '4' ) {
        digitalWrite(10, HIGH);
      }
      if ( i == '5' ) {
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
      }
      if ( i == '6' ) {
        ton(2000, 4000);
      }
      if ( i == '7' ) {
      }
      if ( i == '8' ) {
      }
      if ( i == '9' ) {
        et = 1;
      }
    }
  }
  if(et < millis()) {
    servoLeft.detach();
    servoRight.detach();
    et = 1;
    f = 0;
    b = 0;
  }
}


void motor(int l, int r) {
  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12
  servoLeft.writeMicroseconds(l);            // Left wheel clockwise
  servoRight.writeMicroseconds(r);           // Right wheel counterclockwise
  Serial.println(et);
  if(et == 1) {
    et = millis() + 3000;
    Serial.println("3000");
  } else {
    et = 3000 + et;
  }
}

void ton(int t, int d) {
  tone(4, t, d);                             // play tonbe
}
