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
// int digitalR = 8;
int analogR = A0;
// int digitalL = 9;
int analogL = A1;

int l_black = 0;
int r_black = 0;

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
  // pinMode(digitalR, INPUT);
  pinMode(analogR, INPUT);
  // pinMode(digitalL, INPUT);
  pinMode(analogL, INPUT);

  Serial.begin(9600);
}

void goStraight(int time) {
  // Turn on turning
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);

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

void rotateLeft(int deg) {
  // Turn on turning
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
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

void rotateRight(int deg) {
  // Turn on turning
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
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

void ultrasonic() {
  // If there is no object or reflected pulse, the Echo
  // pin will time-out after 38ms and get back to low state.

  double distance, duration;

  // Reset the pin before we begin
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(1); // Added this line
  
  // In order to generate the ultrasound we need to set
  // the Trig pin on a High State for 10 µs.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  // Then echo pin gets turned on until it receives 
  digitalWrite(trigPin, LOW);

  // Read duration of the echo pin
  // Confirm this calculation later
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 500 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}

int rightIRblack() {
  return analogRead(analogR);
}

int leftIRblack() {
  return analogRead(analogL);
}

void loop() {

  l_black = 1 ? leftIRblack() > 700 : 0;
  r_black = 1 ? rightIRblack() >  700 : 0;
  // goStraight(1000);
  if (l_black == 0 && r_black == 0) {
    // go straight
    goStraight(25);
  }  else if (l_black == 0 && r_black == 1) {
    rotateRight(25);
  } else if (l_black == 1 && r_black == 0) {
    rotateLeft(25);
  } else {
    rotateRight(25);
  }
  // } else if () {
  //   rotateRight(50);
  // } else if () {
  //   rotateRight(50);
  // } else if () {
  //   rotateRight(50);
  // }
  // rotateRight(50);
  // delay(1000);
  // rotateLeft(50);
  // delay(1000);
  // ultrasonic();
  Serial.print("Left: ,");
  Serial.print(l_black);
  Serial.print(" | ");
  Serial.print("Right: ");
  Serial.print(r_black);
  Serial.println();
  delay(35);
}
