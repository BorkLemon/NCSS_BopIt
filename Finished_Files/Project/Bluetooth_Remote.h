#ifndef _Bluetooth_Remote_h
#define _Bluetooth_Remote_h

#include <SoftwareSerial.h>

const int RxD = 6;
const int TxD = 7;

const char ROBOT_FORWARD = '1';

extern SoftwareSerial btSerial;

void bluetoothSetup();

#endif
