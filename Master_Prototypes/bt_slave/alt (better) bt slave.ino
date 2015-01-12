#include <SoftwareSerial.h>                  // Include serial library
#include <Servo.h>                           // Include servo library 

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

const int RxD = 6;                           // Set up connection
const int TxD = 7;

long et = 1;

int f = 0;
int b = 0;

int tru = 0;

SoftwareSerial btSerial(RxD, TxD);

void setup() {
  Serial.begin(9600);
  btSerial.begin(38400);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.println("running");
}


void loop() {

  if (btSerial.available()) {
    //stuff
    while (btSerial.available()) {
      int i = btSerial.read();
      Serial.println(i);
      if (millis() < 10) {
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
       digitalWrite(10, LOW);
        et = 1;    
      }
      if ( i == '0' ) {                     // if 0 is recived from cereal, back
        sadtone();
        tru--;
        btSerial.write("you lost a point! D: you are now at   | ");
        btSerial.println(tru);
        if ( f == 1 ) {
          b = 1;
          f = 0;
          et = 1;
        }
        b = 1;
        motor(1600, 1300);
      }
      if ( i == '1' ) {                     // if 1 received from sensor, forward
        happytone();
        tru++;
        btSerial.write("you gained a point! :D you are now at | ");
        btSerial.println(tru);
        if ( b == 1 ) {
          b = 0;
          f = 1;
          et = 1;
        }
        Serial.println("run!");
        f = 1;
        motor(1200, 1700);
      }
      if ( i == 'r' ) {
        digitalWrite(8, HIGH);
      }
      if ( i == 't') {
        digitalWrite(3, HIGH);
      }     
      if ( i == 'g' ) {
        digitalWrite(9, HIGH);
      }
      if ( i == 'h') {
        digitalWrite(4, HIGH);
      }   
      if ( i == 'b' ) {
        digitalWrite(10, HIGH);
      }
      if ( i == 'n') {
        digitalWrite(5, HIGH);
      }   
      if ( i == 'c' ) {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
      }
      if ( i == 'x' ) {
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
      }
      if ( i == '6' ) {
        ton(2000, 4000);
      }
      if ( i == '7' ) {
        happytone();
      }
      if ( i == '8' ) {
        sadtone();
      }
      if ( i == '9' ) {
        et = 1;
      }
      if ( i == 'f') {
        et = 1;
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        b = 0;
        f = 0;
        tru = 0;
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
  Serial.println(tru);
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
  tone(11, t, d);                             // play tone
}

void happytone() {
  tone(11, 262, 400);
  delay(150);
  tone(11, 330, 400);
  delay(150);
  tone(11, 392, 400);
  delay(150);
  tone(11, 523, 400);
}

void sadtone() {
  tone(11, 262, 400);
  delay(150);
  tone(11, 196, 400);
  delay(150);
  tone(11, 156, 400);
  delay(150);
  tone(11, 131, 400);
}
