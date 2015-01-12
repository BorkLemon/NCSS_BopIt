#include "Bluetooth_Remote.h"
#include <SoftwareSerial.h>

SoftwareSerial btSerial(RxD, TxD);

void bluetoothSetup() {
  btSerial.begin(38400);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
}
