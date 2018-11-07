// called once on startup
void setup() {
    // For simplicity, we'll format our data as text, and pipe it to serial.
    // but you could just as easily display it in a webpage or pass the data to another system.

    // Learn more about the serial commands at https://docs.particle.io/reference/firmware/photon/#serial
    //  for the Photon, or https://docs.particle.io/reference/firmware/core/#serial for the Core
    // You can also watch what's sent over serial with the particle cli with
    //  particle serial monitor
    Serial.begin(115200);

    RGB.control(true);

    pinMode(D7, OUTPUT);

    // Lets listen for the hook response
    Particle.subscribe("hook-response/get_bartdepart", gotBartData, MY_DEVICES);

    // Lets give ourselves 10 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }
}


// called forever really fast
void loop() {

    // Let's request the train data, but no more than once every 60 seconds.
    Serial.println("Requesting Balboa Park Bart Northbound Departure Status!");

    // publish the event that will trigger our Webhook
    Particle.publish("get_bartdepart");

    // and wait at least 60 seconds before doing it again
    delay(60000);
}

// This function will get called when train data comes in
void gotBartData(const char *name, const char *data) {
    // Important note!  -- Right now the response comes in 512 byte chunks.
    //  This code assumes we're getting the response in large chunks, and this
    //  assumption breaks down if a line happens to be split across response chunks.
    String str = String(data);
    String minStr = tryExtractString(str, "<minutes>" ,"</minutes>" );    //extract the min before a train leaves

    Serial.println("Min to depart: " + minStr);
    Serial.println();



     if (minStr.toInt()<11 && minStr.toInt()>4){       //LED is green if train is coming in between 5 and 10 min
            RGB.color(0,255,0);
            delay(100000);
            RGB.color(0,0,0);
         }
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
