int val = 0;
double voltage = 0.0;
double tempC = 0.0;
double tempF = 0.0;

void setup()
{
    Serial.begin(9600);
    Particle.variable("tempC", tempC);
    Particle.variable("tempF", tempF);
}

void loop()
{
    val = analogRead(A0);
    voltage = val * 3.3 / 4096;              // Convert analog reading to voltage value
    tempC = (voltage - 0.5) * 100;
    tempC = round(tempC * 10) / 10.0;        //rounds the value for IFTTT
    tempF = (tempC * 9.0 / 5.0) + 32.0;
    tempF = round(tempF * 10) / 10.0;        //rounds the value for IFTTT
    delay(10000);
}
