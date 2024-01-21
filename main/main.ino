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

<<<<<<< HEAD:main/main.ino
// LED
int led_red = 10;
int led_green = 11;

//Button
int button = 1;
int buttonState = 0;

double distance;

int ena_max = 255;
int enb_max = 210;

int state = 0;
bool wait = false;
=======
int l_black = 0;
int r_black = 0;
>>>>>>> main:line_follow.ino

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

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);

  pinMode(button, INPUT);

  Serial.begin(9600);
}

void goStraight(int time) {
<<<<<<< HEAD:main/main.ino
=======
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
>>>>>>> main:line_follow.ino
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

  //if (distance >= 500 || distance <= 0){
  //  Serial.println("Out of range");
  //}
  //else {
    Serial.print(distance);
    Serial.println(" cm");
  //}
}

int rightIRblack() {
  return analogRead(analogR);
}

int leftIRblack() {
  return analogRead(analogL);
}

void lineFollow() {
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

  Serial.print("Left: ,");
  Serial.print(l_black);
  Serial.print(" | ");
  Serial.print("Right: ");
  Serial.print(r_black);
  Serial.println();

}

<<<<<<< HEAD:main/main.ino
void mazeCode(){
  rotateRight(300);
  delay(1000);
  ultrasonic();
  if (distance < 10){
    rotateLeft(300);
    delay(1000);
    ultrasonic();
    if(distance < 10){
      rotateLeft(300);
      ultrasonic();
      if(distance < 10)
      {
        rotateLeft(300);
      }
    }
    else{
      goStraight(100);
    }
  }
  else{
    goStraight(100);
  }
=======
void loop() {
  lineFollow();
  delay(35);
>>>>>>> main:line_follow.ino
}

void LedSelection(){
  if(state == 0)
  {
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, LOW);
  }
  else if(state == 1)
  {
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, LOW);
  }
  else if(state == 2)
  {
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, HIGH);
  }
}

void StateSelection()
{
  buttonState = digitalRead(button);
  if (wait == false)
  {
    if (buttonState == HIGH) {
      wait = true;
      state++;
      Serial.print("State Change:" + state);
      if (state > 2)
      {
        state = 0;
      }
    } 
  }
  if (buttonState == LOW){
      wait = false;
  }
}

void loop() {
  //delay(1000);
  //mazeCode();
  Serial.println(state);
  StateSelection();
  LedSelection();
}

