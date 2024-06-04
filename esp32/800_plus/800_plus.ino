//ESP32-S3-WROOM-1-N16R8 16 MB (Quad SPI) 8 MB (Octal SPI)
//FQBN: esp32:esp32:esp32s3:CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi


//ESP 2.0.15 and 2.0.16 have issue with ST7789 screen and TFT_eSPI, panic on tft.init()
#include <TFT_eSPI.h>

//LVGL 9.0 and 9.1 have bug with TFT_espi rotate.  Manual update src from github work around until 9.2
#include <lvgl.h>

// #include <examples/lv_examples.h>
// #include <demos/lv_demos.h>
// #include "WiFi.h"

#include "ui.h"

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
// #define TFT_INVERSION_ON

#define LCD_BL_GPIO          1       //HIGH is ON
#define BUTTON_LED_GPIO      38  //LOW is ON

#define USB_Serial Serial
#define MSP_Serial Serial1

// TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

#define SCREEN_WIDTH TFT_WIDTH
#define SCREEN_HEIGHT TFT_HEIGHT
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// LVGL logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  USB_Serial.println(buf);
  USB_Serial.flush();
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void)
{
    return millis();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LCD_BL_GPIO,OUTPUT);
  pinMode(BUTTON_LED_GPIO,OUTPUT);
  pinMode(7,INPUT_PULLUP);

  USB_Serial.begin(115200);
  MSP_Serial.begin(115200, SERIAL_8N1, 18, 17);

  // tft.init();

  digitalWrite(LCD_BL_GPIO,HIGH);
  digitalWrite(BUTTON_LED_GPIO,LOW);
  
  // tft.fillScreen(TFT_WHITE);
  
  // tft.setRotation(2);
  // tft.setTextSize(4);  
  // tft.setTextColor(TFT_BLACK, TFT_WHITE);
  // tft.setTextDatum(MC_DATUM);  
  // tft.setTextPadding(100);

  // Start LVGL
  lv_init();
  // Register print function for debugging
  lv_log_register_print_cb(log_print);

      /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

  //Check vertical and horizontal resolution of what lvgl sees
  lv_coord_t hor_res = lv_disp_get_hor_res(NULL);
  USB_Serial.print("LVGL Horizontal Resolution: ");
  USB_Serial.println(hor_res);
  

  //Check vertical and horizontal resolution of what lvgl sees
  lv_coord_t ver_res = lv_disp_get_ver_res(NULL);
  USB_Serial.print("LVGL Vertical Resolution: ");
  USB_Serial.println(ver_res);

  lv_coord_t disp_dpi = lv_disp_get_dpi(NULL);
  USB_Serial.print("LVGL Display DPI: ");
  USB_Serial.println(disp_dpi);

  // lv_obj_t *label = lv_label_create( lv_screen_active() );
  // lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
  // lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );  

  ui_init();

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

  // if(button>0 && button < 0xFE)
  //   tft.drawNumber(button,120,160);
  // else
  //   tft.drawString("880+",120,160);

  //USB_Serial.printf("loop %d:\t%d\n", millis(), button);

  //delay(1);

  lv_task_handler();  // let the GUI do its work
  // lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(2);     
}
