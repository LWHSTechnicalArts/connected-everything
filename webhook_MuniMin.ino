// called once on startup
void setup() {
    // For simplicity, we'll format our weather data as text, and pipe it to serial.
    // but you could just as easily display it in a webpage or pass the data to another system.

    // Learn more about the serial commands at https://docs.particle.io/reference/firmware/photon/#serial
    //  for the Photon, or https://docs.particle.io/reference/firmware/core/#serial for the Core
    // You can also watch what's sent over serial with the particle cli with
    //  particle serial monitor
    Serial.begin(115200);

    // Lets listen for the hook response
    Particle.subscribe("hook-response/get_muni", gotWeatherData, MY_DEVICES);

    // Lets give ourselves 10 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }
}


// called forever really fast
void loop() {

    // Let's request the weather, but no more than once every 60 seconds.
    Serial.println("Requesting Muni!");

    // publish the event that will trigger our Webhook
    Particle.publish("get_muni");

    // and wait at least 60 seconds before doing it again
    delay(60000);
}

// This function will get called when weather data comes in
void gotWeatherData(const char *name, const char *data) {
    // Important note!  -- Right now the response comes in 512 byte chunks.
    //  This code assumes we're getting the response in large chunks, and this
    //  assumption breaks down if a line happens to be split across response chunks.
    //
    // Sample data:
    //  <location>Minneapolis, Minneapolis-St. Paul International Airport, MN</location>
    //  <weather>Overcast</weather>
    //  <temperature_string>26.0 F (-3.3 C)</temperature_string>
    //  <temp_f>26.0</temp_f>


    String str = String(data);
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
