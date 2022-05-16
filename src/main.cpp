/*
 An example digital clock using a TFT LCD screen to show the time.
 Demonstrates use of the font printing routines. (Time updates but date does not.)

 It uses the time of compile/upload to set the time
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo...

 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################

 Based on clock sketch by Gilchrist 6/2/2014 1.0

A few colour codes:

code	color
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink

 */

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <ArduinoOTA.h>

const char *ssid         = "IOT";
const char *password     = "ac1ce0ss6#iot";
#define TFT_GREY 0x5AEB
long rssi = 0; 
int bars = 0;
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

unsigned int colour = 0;

void setup(void) {
  //Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawCentreString("Iniciando..",120,40,2);
  WiFi.begin ( ssid, password );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 10 );
  }
  tft.drawRoundRect(0,0,240,240,10,TFT_WHITE);
  tft.drawCentreString("Wifi Conectado",120,40,2);
   tft.setTextColor(TFT_YELLOW, TFT_BLACK,false);
   
   tft.setTextColor(0xFFE0);
  tft.drawCentreString("IP: "+WiFi.localIP().toString(),120,60,2);
  delay(5000);
        /*tft.drawFastHLine(107,10,20,TFT_WHITE);
        tft.drawFastHLine(107,17,20,TFT_WHITE);
        tft.drawFastVLine(127,10,7,TFT_WHITE);
        tft.drawFastVLine(107,10,7,TFT_WHITE);
        
        tft.drawRect(103,8,3,3,TFT_WHITE);
       
        for (int b=0; b <= bars; b++) {
    //display.fillRect(59 + (b*5),33 - (b*5),3,b*5,WHITE); 
    tft.fillRect(123 - (b*5),8,2,3,TFT_YELLOW);
  }*/
  // Do some simple loop math to draw rectangles as the bars
// Draw one bar for each "bar" Duh...
  
}

void loop() {
  
    tft.drawCentreString("Maquina 1 Manutencao",120,80,2);
  //  int bars = map(RSSI,-80,-44,1,6); // this method doesn't refelct the Bars well
  // simple if then to set the number of bars
  rssi  = WiFi.RSSI();
  if (rssi > -55) { 
    bars = 5;
  } else if (rssi < -55 & rssi > -65) {
    bars = 4;
  } else if (rssi < -65 & rssi > -70) {
    bars = 3;
  } else if (rssi < -70 & rssi > -78) {
    bars = 2;
  } else if (rssi < -78 & rssi > -82) {
    bars = 1;
  } else {
    bars = 0;
  }
  
  for (int b=0; b <= bars; b++) {
    //display.fillRect(59 + (b*5),33 - (b*5),3,b*5,WHITE); 
    tft.fillRect(100 + (b*5),20 - (b*2),3,b*2,TFT_WHITE);
  }
  
  delay(300);
  for (int b=0; b <= bars; b++){
    tft.fillRect(100+(b*5),20-(b*2),3,b*2,TFT_BLACK);
  }
  //tft.fillScreen(TFT_BLACK);
}

