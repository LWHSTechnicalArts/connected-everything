
int reading = 0;
double volts = 0.0;
int analogPin = A0;

boolean bright = false;

void setup() {
    Serial.begin(9600);
    Particle.variable("analog", &reading, INT);
    Particle.variable("volts", &volts, DOUBLE);
}

void loop() {
  reading = analogRead(analogPin);
  volts = reading * 3.3 / 4096.0;
  Serial.println(volts);
  if (volts > 1.5 && bright == false) {
      Particle.publish("bright");
      bright = true;
  }
  if (volts <= 1.5 && bright == true) {
      Particle.publish("dim");
      bright = false;
  }
    delay(1000);
}

