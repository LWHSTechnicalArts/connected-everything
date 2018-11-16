int val = 0;
double voltage = 0;
double tempC = 0;
double tempF = 0;

void setup()
{
    Serial.begin(9600);
    Particle.variable("tempC", &tempC, DOUBLE);
    Particle.variable("tempF", &tempF, DOUBLE);
}

void loop()
{
    val = analogRead(A0);
    voltage = val * 3.3 / 4096; // Convert analog reading to voltage value
    tempC = (voltage - 0.5) * 100;
    tempF = (tempC * 9.0 / 5.0) + 32.0;
    Serial.printlnf("Temp F: %3.1f  Temp C: %3.1f", tempF, tempC); //%3.1 allows for a 3 or more digit value with 1 decimal place
    delay(2000);
}