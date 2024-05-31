//ESP32-S3-WROOM-1-N16R8 16 MB (Quad SPI) 8 MB (Octal SPI)
//FQBN: esp32:esp32:esp32s3:CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi


//ESP 2.0.15 and 2.0.16 have issue with ST7789 screen and TFT_eSPI, panic on tft.init()
#include <TFT_eSPI.h>
// #include "WiFi.h"


//Configuration for tft_espi user_setup.h
// #define ST7789_DRIVER  
// #define TFT_RGB_ORDER TFT_BGR
// #define TFT_WIDTH  240
// #define TFT_HEIGHT 320 
// #define TFT_MOSI            10
// #define TFT_SCLK            11
// #define TFT_CS              12
// #define TFT_DC              13
// #define TFT_RST             9

#define LCD_BL_GPIO          1       //HIGH is ON
#define BUTTON_LED_GPIO      38  //LOW is ON

#define USB_Serial Serial
#define MSP_Serial Serial1

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library


void setup() {
  // put your setup code here, to run once:
  pinMode(LCD_BL_GPIO,OUTPUT);
  pinMode(BUTTON_LED_GPIO,OUTPUT);
  pinMode(7,INPUT_PULLUP);

  USB_Serial.begin(115200);
  MSP_Serial.begin(115200, SERIAL_8N1, 18, 17);

  tft.init();

  digitalWrite(LCD_BL_GPIO,HIGH);
  digitalWrite(BUTTON_LED_GPIO,LOW);
  
  tft.fillScreen(TFT_WHITE);
  
  tft.setRotation(2);
  tft.setTextSize(4);  
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(MC_DATUM);  
  tft.setTextPadding(100);

}

int button=0;

void loop() {
  
  if(digitalRead(7)==HIGH) {
    digitalWrite(LCD_BL_GPIO,HIGH);
    digitalWrite(BUTTON_LED_GPIO,LOW);
  } else{
    digitalWrite(LCD_BL_GPIO,LOW);
    digitalWrite(BUTTON_LED_GPIO,HIGH);
  }



  while(MSP_Serial.available()) {
    button = MSP_Serial.read();
    USB_Serial.printf("millis %d:\tbutton: %d\n", millis(), button);
  }

  if(button>0 && button < 0xFE)
    tft.drawNumber(button,120,160);
  else
    tft.drawString("880+",120,160);

  //USB_Serial.printf("loop %d:\t%d\n", millis(), button);

  //delay(1);
}
