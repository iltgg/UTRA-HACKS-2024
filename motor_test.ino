/*
MOTOR:
pins 2 and 3 direction
pins 4 and 5
power with up to 12 volts

*/

int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

void setup() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void loop() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
}
