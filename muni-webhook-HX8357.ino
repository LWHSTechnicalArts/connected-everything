//Don't forget to include Adafruit_HX8357 library!!!

// Use software SPI
Adafruit_HX8357 tft = Adafruit_HX8357(D6, D7, D5, D3, -1, D4); //(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);


void setup() {
  Serial.begin(115200);
  tft.begin(HX8357D);
  tft.setRotation(1);

      // Lets listen for the hook response
    Particle.subscribe("hook-response/get_muni", gotMuniData, MY_DEVICES);

    // 5 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(0, 0);
        tft.setTextSize(2);
        tft.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }

}

void loop(void) {
    tft.fillScreen(HX8357_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    Serial.println("Requesting Muni!");
    tft.println("Requesting Muni!");

    // publish the event that will trigger our Webhook
    Particle.publish("get_muni");

    // and wait at least 30 seconds before doing it again
    delay(30000);
}

void gotMuniData(const char *name, const char *data) {

    Serial.println(data);

    char dataBuffer[256]="";
    strcpy(dataBuffer, data);
    strtok(0,0);
    int muni1 = atof(strtok(dataBuffer, "*"));
    int muni2 = atof(strtok(NULL, "~*"));
    int muni3 = atof(strtok(NULL, "~*"));
    int muni4 = atof(strtok(NULL, "~*"));
    int muni5 = atof(strtok(NULL, "~*"));


    Serial.println(muni1);
    Serial.println(muni2);
    Serial.println(muni3);
    Serial.println(muni4);
    Serial.println(muni5);

    tft.fillScreen(HX8357_BLACK);
    //unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(HX8357_WHITE);
    tft.setTextSize(5);

    tft.print(" muni5= ");
    tft.println(muni5);

    tft.print(" muni4= ");
    tft.println(muni4);

    tft.print(" muni3= ");
    tft.println(muni3);

    tft.print(" muni2= ");
    tft.println(muni2);

    tft.setTextColor(HX8357_GREEN);
    tft.print(" muni1= ");
    tft.println(muni1);

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
