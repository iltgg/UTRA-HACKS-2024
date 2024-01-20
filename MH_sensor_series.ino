const int IN_A0 = A0; // analog input

void setup() {
  pinMode (IN_A0, INPUT);
}

int value_A0;

void loop() {
  // A0 pin is the distance between the object and the obstacle
  value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor
  
  if (value_A0 > 900) {
    Serial.println("BLACK DETECTED");
  }
  
  delay(1000);
}

