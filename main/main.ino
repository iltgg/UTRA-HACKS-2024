int PC = 0;
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
//int digitalR = 8;
int analogR = A0;
//int digitalL = 9;
int analogL = A2;

// LED
int led_red = 10;
int led_green = 11;

//Button
int button = 19;
int buttonState = 0;

double distance;

int ena_max = 255;
int enb_max = 210;

const int state = 1;
bool wait = false;

int l_black = 0;
int r_black = 0;

void setup() {
  //Serial.begin(9600);
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
  //pinMode(digitalR, INPUT);
  pinMode(analogR, INPUT);
  //pinMode(digitalL, INPUT);
  pinMode(analogL, INPUT);

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);

  pinMode(button, INPUT);

  //Serial.begin(9600);
}

void goStraight(int time) {
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

int rightIRblack() {
  return analogRead(analogR);
}

int leftIRblack() {
  return analogRead(analogL);
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

void lineFollow() {
  l_black = 1 ? leftIRblack() > 50 : 0;
  r_black = 1 ? rightIRblack() >  50 : 0;
  // goStraight(1000);
  if (l_black == 0 && r_black == 0) {
    // go straight
    goStraight(20);
  }  else if (l_black == 0 && r_black == 1) {
    rotateRight(75);
  } else if (l_black == 1 && r_black == 0) {
    rotateLeft(75);
  } else {
    rotateRight(75);
  }

  Serial.print("Left: ,");
  Serial.print(l_black);
  Serial.print(" | ");
  Serial.print("Right: ");
  Serial.print(r_black);
  Serial.println();

}

void randomWalk() {
  // First interaction: with the box, then turn left
  // Going to see the ling
  // Second box: turn 45 degrees align itself
  l_black = 1 ? leftIRblack() > 70 : 0;
  r_black = 1 ? rightIRblack() >  70 : 0;
  
  // Default state: moving forward
  ultrasonic();
  if (distance < 40) {
    if (PC == 0) {
      rotateLeft(201);
      delay(1000);
      goStraight(500);
      PC++;
    } else if (PC == 1) {
      rotateRight(201);
      delay(1000);
      goStraight(500);
      PC++;
    }
  }
  else if (l_black == 0 && r_black == 0) {
    goStraight(25);
  } else if (l_black == 0 && r_black == 1) {
    rotateRight(25);
  } else if (l_black == 1 && r_black == 0) {
    rotateLeft(25);
  } else {
    rotateRight(100);
  }
  
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

  if (buttonState == HIGH) {
    if (wait == false)
    {
      wait = true;
      //state++;
      if (state > 2)
      {
        //state = 0;
      }
    }
  }
  else {
      wait = false;
  }
}

void loop() {
  // StateSelection();
  // LedSelection();
  if(state == 0)
  {
    delay(35);
    lineFollow();
  }
  else if(state == 1)
  {
    delay(35);
    randomWalk();
  }
  else if(state == 2)
  {
    delay(100);
    mazeCodePlus();
  }
  // r_black = rightIRblack();
  // l_black = leftIRblack();
  // Serial.print("L: ");
  // Serial.print(l_black);
  // Serial.print("| R: ");
  // Serial.print(r_black);
  // Serial.println();
  // delay(100);
}

