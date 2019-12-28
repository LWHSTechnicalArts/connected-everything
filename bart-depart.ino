void setup() {
    Serial.begin(115200);
    pinMode(D7, OUTPUT);
    Particle.subscribe("hook-response/get_bartdepart", gotBartData, MY_DEVICES);
    // 5 seconds before we actually start the program which will give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }
}

void loop() {
    Serial.println("Requesting Balboa Park Bart Northbound Departure Status!");
    // publish the event that will trigger our Webhook
    Particle.publish("get_bartdepart");
    // and wait at least 30 seconds before doing it again
    delay(30000);
}

// This function will get called when train data comes in
void gotBartData(const char *name, const char *data) {
    // Important note!  -- Right now the response comes in 512 byte chunks.
    //  This code assumes we're getting the response in large chunks, and this
    //  assumption breaks down if a line happens to be split across response chunks.
    String rawData = String(data);
    //Serial.println(str); 
    String minStr = tryExtractString(rawData, "<minutes>" ,"</minutes>" );    //extract the min before a train leaves

    Serial.println("Min to depart: " + minStr);

     if (minStr.toInt()<11 && minStr.toInt()>4){       //LED is lit if train is coming inbetween 5 and 10 min
            digitalWrite(D7,HIGH);
            delay(30000);
            digitalWrite(D7,LOW);
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
