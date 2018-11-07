int relayPin = D7;

void setup() {
    pinMode(relayPin, OUTPUT);
    Spark.subscribe("bright", lightUp);
    Spark.subscribe("dim", stayOff);
}

void loop() {
}

void lightUp(const char *event, const char *data) {
    digitalWrite(relayPin, HIGH);
}

void stayOff(const char *event, const char *data) {
    digitalWrite(relayPin, LOW);
}
