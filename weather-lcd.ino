// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

// called once on startup
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

int num = 0;

void setup() {
    // For simplicity, we'll format our weather data as text, and pipe it to serial.
    // but you could just as easily display it in a webpage or pass the data to another system.

    // Learn more about the serial commands at https://docs.particle.io/reference/firmware/photon/#serial
    //  for the Photon, or https://docs.particle.io/reference/firmware/core/#serial for the Core
    // You can also watch what's sent over serial with the particle cli with
    //  particle serial monitor
    Serial.begin(115200);
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
    display.clearDisplay();   // clears the screen and buffer

    // text display tests
    display.setCursor(0,0);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("Hello, world!");
    display.display();

    // Lets listen for the hook response
    Particle.subscribe("hook-response/get_weather", gotWeatherData, MY_DEVICES);

    // Lets give ourselves 5 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<5;i++) {
        Serial.println("waiting " + String(5-i) + " seconds before we publish");
        delay(1000);
    }
}


// called forever really fast
void loop() {

    // Let's request the weather, but no more than once every 30 seconds.
    display.clearDisplay();   // clears the screen and buffer
    display.setCursor(0,0);
    Serial.println("Requesting Weather!");
    display.println("Requesting Weather!");
    display.display();
    // publish the event that will trigger our Webhook
    Particle.publish("get_weather");

    // and wait at least 30 seconds before doing it again
    delay(30000);
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
    String locationStr = tryExtractString(str, "<location>", "</location>");
    String weatherStr = tryExtractString(str, "<weather>", "</weather>");
    String tempStr = tryExtractString(str, "<temp_f>", "</temp_f>");
    String windStr = tryExtractString(str, "<wind_string>", "</wind_string>");

    if (locationStr != NULL) {
        Serial.println("At location: " + locationStr);
        display.println(locationStr);
    }

    if (weatherStr != NULL) {
        Serial.println("The weather is: " + weatherStr);
        display.println(weatherStr);
    }

    if (tempStr != NULL) {
        Serial.println("The temp is: " + tempStr + String(" *F"));
        display.println(tempStr + String(" *F"));
    }

    if (windStr != NULL) {
        Serial.println("The wind is: " + windStr);
        display.println(windStr);
    }
    
    display.display();
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