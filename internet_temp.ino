void setup() { 
  Serial.begin(9600); 
} 
 
void loop() { 
  int val = analogRead(A0); 
  float voltage = val * 3.3 / 4096; // Convert analog reading to voltage value
  float tempC = (voltage - 0.5) * 100;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  Serial.printlnf("Temp F: %3.1f  Temp C: %3.1f", tempF, tempC);  //%3.1 allows for a 3 or more digit value with 1 decimal place
  delay(5000); 
}