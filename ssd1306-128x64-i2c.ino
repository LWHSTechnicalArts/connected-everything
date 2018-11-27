// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

int num = 0;

void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();   // clears the screen and buffer

  // text display tests
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.14);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("KOOL KIDZ");
  display.setTextSize(3);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println("BIGGY");
  display.display();
  delay(5000);
}


void loop() {
  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0,0);
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.println(num);
  display.display();
  delay(1000);
  num++;
}

