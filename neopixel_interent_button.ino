#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 24
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup()
{
  Particle.function("led",ledToggle);

  strip.begin();
  strip.setBrightness(30);
   for(int j=0; j<256; j++) {
            for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, 0, 0, 0);
        }
   strip.show(); // Initialize all pixels to 'off'
   }
}


void loop(){
}


int ledToggle(String command) {

    if (command=="on") {
        int colorR = random(255);
        int colorG = random(255);
        int colorB = random(255);
        for(int j=0; j<256; j++) {
            for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, colorR, colorG,colorB);
        }
        strip.show();
        }
        return 1;
    }
    else if (command=="off") {
        for(int j=0; j<256; j++) {
            for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, 0, 0, 0);
        }
        strip.show();
        }
        return 0;
    }
    else {
        return -1;
    }
}
