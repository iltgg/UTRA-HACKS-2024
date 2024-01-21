#include <Wire.h>

void setup() {
  Wire.begin();  // join i2c bus (address optional for master)
}

short d = 0;
stop = 0;

void loop() {
  if (stop == 1) { return; }
  sendPosition(-99);
  for (int i = 0; i < 126; i++) {
    sendPosition(d);
    d++;
  }
  sendPosition(-300);
  stop = 1;
}

void sendPosition(short distance) {
  Wire.beginTransmission(4);  // transmit to device #4
  Wire.write(distance);
  Wire.endTransmission();  // stop transmitting
}