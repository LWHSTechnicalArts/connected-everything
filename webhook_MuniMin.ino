void setup() {
    
    Serial.begin(115200);

    Particle.subscribe("hook-response/get_muni", gotWeatherData, MY_DEVICES);
    // 5 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }
}

void loop() {
    // Let's request the weather, but no more than once every 60 seconds.
    Serial.println("Requesting Muni! J Church Balboa bound from Day Street stop");

    // publish the event that will trigger our Webhook
    Particle.publish("get_muni");

    // and wait at least 30 seconds before doing it again
    delay(30000);
}

// This function will get called when weather data comes in
void gotWeatherData(const char *name, const char *data) {

    Serial.println(data);

    char dataBuffer[256]="";
    strcpy(dataBuffer, data);
    strtok(0,0);
    int muni1 = atof(strtok(dataBuffer, "*"));
    int muni2 = atof(strtok(NULL, "~*"));
    int muni3 = atof(strtok(NULL, "~*"));
    int muni4 = atof(strtok(NULL, "~*"));
    int muni5 = atof(strtok(NULL, "~*"));
    int muni6 = atof(strtok(NULL, "~*"));

    Serial.println(muni1);
    Serial.println(muni2);
    Serial.println(muni3);
    Serial.println(muni4);
    Serial.println(muni5);
    Serial.println(muni6);

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
