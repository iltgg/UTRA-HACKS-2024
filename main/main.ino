// MOTOR
int en1 = 6;
int motor1pin1 = 2;
int motor1pin2 = 3;
int en2 = 7;
int motor2pin1 = 5;
int motor2pin2 = 4;

// ULTRASONIC SENSOR
int echoPin = 12;
int trigPin = 13;

// IR SENSORS
int digitalR = 8;
int analogR = A0;
int digitalL = 9;
int analogL = A1;

float distance;

int ena_max = 255;
int enb_max = 210;

void setup() {
  // Left wheel
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(en1, OUTPUT);

  // Right wheel
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(en2, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // IR sensor pins
  pinMode(digitalR, INPUT);
  pinMode(analogR, INPUT);
  pinMode(digitalL, INPUT);
  pinMode(analogL, INPUT);

  Serial.begin(9600);
}

void goStraight(int time) {
ena_max = 255;
enb_max = 210;

  // Turn on turning
  analogWrite(en1, ena_max);
  analogWrite(en2, enb_max);

  // CW right wheel
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  // CCW left wheel
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(time);
  // Turn off turning
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}

void rotateRight(int deg) {
ena_max = 255;
enb_max = 160;

  // Turn on turning
  analogWrite(en1, ena_max);
  analogWrite(en2, enb_max);
  // CW right wheel
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  // CCW left wheel
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  // By a certain number of degrees
  delay(deg);
  // Turn off turning
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}

void rotateLeft(int deg) {
ena_max = 255;
enb_max = 210;

  // Turn on turning
  analogWrite(en1, ena_max);
  analogWrite(en2, enb_max);
  // CW right wheel
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  // CCW left wheel
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  // By a certain number of degrees
  delay(deg);
  // Turn off turning
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}


void ultrasonic() {
  // If there is no object or reflected pulse, the Echo
  // pin will time-out after 38ms and get back to low state.

  double duration;

  // Reset the pin before we begin
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(1);        // Added this line

  // In order to generate the ultrasound we need to set
  // the Trig pin on a High State for 10 µs.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  // Added this line
  // Then echo pin gets turned on until it receives
  digitalWrite(trigPin, LOW);

  // Read duration of the echo pin
  // Confirm this calculation later
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // if (distance >= 1500 || distance <= 0) {
  //  Serial.println("Out of range");
  // }
  //else {
  // Serial.print(distance);
  // Serial.println(" cm");
  //}
}

void ultrasonicPlus() {
ultrasonic:
  double duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance >= 1500 || distance <= 0) {
    delay(10);
    goto ultrasonic;
  }
}

void leftIR() {
  int isBlack = digitalRead(digitalL);
  Serial.print("Left: ");
  Serial.println(isBlack);
}

void rightIR() {
  int isBlack = digitalRead(digitalR);
  Serial.print("Right: ");
  Serial.println(isBlack);
}

void mazeCode() {
  rotateRight(300);
  delay(1000);
  ultrasonicPlus();
  if (distance < 30) {
    rotateLeft(300);
    delay(1000);
    ultrasonicPlus();
    if (distance < 30) {
      rotateLeft(300);
      ultrasonicPlus();
      if (distance < 30) {
        rotateLeft(300);
      }
    } else {
      goStraight(500);
    }
  } else {
    goStraight(500);
  }
}

#define dly delay(1000)
float forward;
float right;
float left;
void mazeCodePlus() {
  forward = 0;
  right = 0;
  left = 0;

  ultrasonicPlus();
  forward = distance;

  rotateRight(300);
  dly;
  ultrasonicPlus();
  right = distance;

  if (forward > 30) {
    rotateLeft(300);
  dly;
    goStraight(500);
    return;
  }
  if (right > 30) {
    goStraight(500);
    return;
  }

  rotateLeft(300);
  dly;
  rotateLeft(300);
  dly;

  ultrasonicPlus();
  left = distance;
  if (left > 30) {
    goStraight(500);
    return;
  }
  rotateLeft(300);
  dly;
  goStraight(500);
}

void loop() {
  delay(2000);
  mazeCodePlus();
  // delay(5000);
  // rotateRight(300);
  // delay(5000);
  // rotateLeft(250);
}
