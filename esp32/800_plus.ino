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

  USB_Serial.begin(115200);
  MSP_Serial.begin(115200, SERIAL_8N1, 18, 17);

  tft.init();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  digitalWrite(LCD_BL_GPIO,HIGH);
  digitalWrite(BUTTON_LED_GPIO,HIGH);
  
  tft.fillScreen(TFT_RED);
  delay(500);

  tft.fillScreen(TFT_WHITE);
  delay(500);

  tft.fillScreen(TFT_BLUE);
  delay(500);
  
  digitalWrite(LCD_BL_GPIO,LOW);
  digitalWrite(BUTTON_LED_GPIO,LOW);
  delay(500);


  // Getting lots of random stuff from Msp430
  // It is on the right pin, noise stops when MSP430 held in reset
  while(MSP_Serial.available()) {
    USB_Serial.println(MSP_Serial.read());
  }

  USB_Serial.println("loop");
}
