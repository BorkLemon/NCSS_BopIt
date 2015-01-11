#include <SoftwareSerial.h>
#include <Servo.h>                           // Include servo library 

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

const int RxD = 6;                           // Set up connection
const int TxD = 7;

int motor_speed = 0;
SoftwareSerial btSerial(RxD, TxD);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  btSerial.begin(38400);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

  if (btSerial.available()) {
    //stuff
    while (btSerial.available()) {
      int i = btSerial.read();

      if ( i == '0' ) {                     // if 0 is recived from cereal, back
          ton(500, 200);
          motor(1300, 1700);
      }
      if ( i == '1' ) {                     // if 1 received from sensor, forward
          ton(2000, 200);
          motor(1700, 1300);
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
        motor_speed = 6;
      }
      if ( i == '7' ) {
        motor_speed = 7;
      }
      if ( i == '8' ) {
        motor_speed = 8;
      }
    }
  }
}

void motor(int l, int r) {
  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12
  servoLeft.writeMicroseconds(l);            // Left wheel clockwise
  servoRight.writeMicroseconds(r);           // Right wheel counterclockwise
  delay(3000);
  servoLeft.detach();                        // detach the wheels to stop the robot
  servoRight.detach();
}

void ton(int t, int d) {
  tone(4, t, d);                             // play tone
}
