const int IN_A0 = A0; // analog input

void setup() {
  pinMode(IN_A0, INPUT);
  Serial.begin(9600);
}

int value_A0;

void loop() {
  // A0 pin is the distance between the object and the obstacle
  value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor
  Serial.println(value_A0);
  delay(100);
}
