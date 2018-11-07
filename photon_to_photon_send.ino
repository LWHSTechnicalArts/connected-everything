// photon_to_photon_send.ino
//both photons need to be on the same account


int reading = 0;
int digitalPin = D0;

void setup() {
    Serial.begin(9600);
    pinMode(D0,INPUT_PULLUP);   //does not require an external resistor
}

void loop() {
  reading = digitalRead(digitalPin);
  Serial.println(reading);
  
  if (reading == 0) {
      Particle.publish("hellophoton");   //function name must match in receiving sketch
      delay(350);
  }
  delay(50);
}
