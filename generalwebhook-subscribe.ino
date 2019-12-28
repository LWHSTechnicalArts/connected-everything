void setup() {
    Serial.begin(115200);

    pinMode(D7, OUTPUT);

    // Lets listen for the hook response
    Particle.subscribe("hook-response/my_webhook", gotData, MY_DEVICES);

    // 5 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }
}

void loop() {

    // Let's request the train data, but no more than once every 60 seconds.
    Serial.println("Checking Your Webhook!");

    // publish the event that will trigger our Webhook
    Particle.publish("my_webhook");

    // and wait at least 20 seconds before doing it again
    delay(20000);
}

// This function will get called when data comes in
void gotData(const char *name, const char *data) {
    Serial.println(data);
}

// Returns any text found between a start and end string inside 'str'
// example: startfooend  -> returns foo
String tryExtractString(String str, const char* start, const char* end) {
    if (str == NULL) {
        return "";
    }

    int idx = str.indexOf(start);
    if (idx < 0) {
        return "";
    }

    int endIdx = str.indexOf(end);
    if (endIdx < 0) {
        return "";
    }

    return str.substring(idx + strlen(start), endIdx);
}
