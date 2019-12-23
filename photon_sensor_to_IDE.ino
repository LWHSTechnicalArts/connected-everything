int photoresistor = A0; // This is where your photoresistor is plugged in.
int analogvalue; // Here we are declaring the integer variable analogvalue, which we will use later to store the value of the photoresistor.

void setup() {
    pinMode(photoresistor,INPUT);  // Our photoresistor pin is input (reading the photoresistor)
    // We are going to declare a Particle.variable() here so that we can access the value of the photoresistor from the cloud.
    Particle.variable("analogvalue", analogvalue);
}

void loop() {
    // check to see what the value of the photoresistor is and store it in the int variable analogvalue
    analogvalue = analogRead(A0);
    //store analogvalue as a String variable to publish
    String photoresistor = String(analogvalue);
    //publish the name of the event and the value of the sensor
    Particle.publish("sensor value", photoresistor);
    
    delay(1000);
}
