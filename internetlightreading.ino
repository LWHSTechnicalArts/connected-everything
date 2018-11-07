int reading = 0;
double volts = 0.0;
int analogPin = A0;

void setup() {
    Serial.begin(9600);
    Particle.variable("analog", &reading, INT);
    Particle.variable("volts", &volts, DOUBLE);
}

void loop() {
  reading = analogRead(analogPin);
  volts = reading * 3.3 / 4096.0;
  Serial.println(volts);
  delay(1000);
}
