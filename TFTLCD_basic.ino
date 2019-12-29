//Don't forget to include the Adafruit_HX8357.h library!!

 /* WIRING:
 Screen-->Photon
 -------------
 GND --> GND
 VIN --> 3V3
 CLK --> D3
 MISO--> D4
 MOSI--> D5
 CS --> D6
 DC --> D7
 RST-->RST
 */


// Color definitions
// #define	HX8357_BLACK   0x0000
// #define	HX8357_BLUE    0x001F
// #define	HX8357_RED     0xF800
// #define	HX8357_GREEN   0x07E0
// #define HX8357_CYAN    0x07FF
// #define HX8357_MAGENTA 0xF81F
// #define HX8357_YELLOW  0xFFE0
// #define HX8357_WHITE   0xFFFF

// Use software SPI
Adafruit_HX8357 tft = Adafruit_HX8357(D6, D7, D5, D3, -1, D4); //(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

void setup() {
  tft.begin(HX8357D);
  tft.setRotation(1); //choose 1-4
}


void loop() {
    tft.fillScreen(HX8357_BLACK); //clears the screen
    delay(1000);

    tft.setTextColor(HX8357_RED);  //text color
    tft.setTextSize(6);             //text size (1-10)
    tft.setCursor(10,100);            //cursor location x,y
    tft.println("Hello World!");    //actual text
    delay(1000);                    //display time

    tft.setTextColor(HX8357_BLUE);  //text color
    tft.setTextSize(6);
    tft.setCursor(10,100);
    tft.println("Hello World!");
    delay(1000);

    tft.fillCircle(40,220,30,HX8357_YELLOW);  //x,y,radius,color
    tft.drawCircle(105,220,30,HX8357_CYAN);  //x,y,radius,color
    tft.fillRect(160,200,30,40,HX8357_WHITE);  //x,y,width,height,color
    tft.drawRect(200,200,30,50,HX8357_MAGENTA);  //x,y,width,height,color
    tft.drawTriangle(270,220,290,240,250,240,HX8357_GREEN);  //x1,y1,x2,y2,x3,y3,color
    tft.drawRoundRect(320,200,40,40,5,HX8357_GREEN);  //x,y,width,height,rounded radius,color
    tft.fillRoundRect(380,200,40,60,8,HX8357_YELLOW);  //x,y,width,height,rounded radius,color
    tft.drawLine(0,175,480,175,HX8357_WHITE);  //x1,y1,x2,y2,color
    delay(4000);

}
