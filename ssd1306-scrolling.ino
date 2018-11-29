/*****************************************************************************
NOTE: This code example requires the Adafruit_SSD1306 library to be included,
so make sure to add it via the Libraries tab in the left sidebar.
******************************************************************************/

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

int  x, minX; // variables for scrolling code

void setup()   {
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)

  display.setTextSize(7);       // text size
  display.setTextColor(WHITE); // text color
  display.setTextWrap(false); // turn off text wrapping so we can do scrolling
  x = display.width(); // set scrolling frame to display width
  minX = -800; // determines how long the scroll is
}

void loop() {
    
  display.clearDisplay();
  display.setCursor(x, 7);
  display.print("Hello from the Void!");
  display.display();
  x-=8;
  if(x < minX) x = display.width()*2;
}