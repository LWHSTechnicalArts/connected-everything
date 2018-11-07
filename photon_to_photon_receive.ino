//both photons need to be on the same account
//toggles a single LED on digital pin 7

int relayPin = D7;   
int presses = 0;

void setup() {
    pinMode(relayPin, OUTPUT);
    Particle.subscribe("hellophoton", lightUp);   //function name must match in sending sketch
}

void loop() {
    //nothing needed here
    }

void lightUp(const char *event, const char *data) {
    presses++;
    
    if(presses%2==0){
    digitalWrite(relayPin, HIGH);
    delay(100);
    }
    
    if(presses%2==1){
    digitalWrite(relayPin, LOW);
    delay(100);
    }
    
}
