//ESP32-S3-WROOM-1-N16R8 16 MB (Quad SPI) 8 MB (Octal SPI)
//FQBN: esp32:esp32:esp32s3:CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi

//ESP 2.0.15, 2.0.16, 2.0.17,  3.x have issue with ST7789 screen and TFT_eSPI, panic on tft.init()
//2.0.14 works
//https://github.com/espressif/arduino-esp32/issues/9618#issuecomment-2114839060

//3.0.2 working with CONFIG_IDF_TARGET_ESP32S3
//https://github.com/espressif/arduino-esp32/issues/9618#issuecomment-2107459271
//#define REG_SPI_BASE(i) (DR_REG_SPI1_BASE + (((i) > 1) ? (((i) * 0x1000) + 0x20000) : (((~(i)) & 1) * 0x1000)))
//hack in tft_espi_esp32_s3.h
//tested sat without the hack too!

#include <TFT_eSPI.h>

//LVGL 9.0 and 9.1 have bug with TFT_espi rotate.  Manual update src from github work around until next release
#include <lvgl.h>

// #include "WiFi.h"

//About 7 pixels obscured at top and 20 at bottom
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

// #define TFT_SPI_MODE SPI_MODE0
// #define USE_HSPI_PORT

#define LCD_BL_GPIO          1       //LOW is ON
#define BUTTON_LED_GPIO      38      //LOW is ON

#define USB_Serial Serial
#define MSP_Serial Serial1

#define SCREEN_WIDTH TFT_WIDTH
#define SCREEN_HEIGHT TFT_HEIGHT
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

char button_value[10];

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

const char *get_var_lv_btn_press(){
  return button_value;
}

void set_var_lv_btn_press(const char *value){
  //ignore lvgl set request
}

void setup() {

  pinMode(LCD_BL_GPIO,OUTPUT);
  pinMode(BUTTON_LED_GPIO,OUTPUT);
  pinMode(7,INPUT_PULLUP);

  //blocks on 2.0.14 code,okay in 3.0.2
  USB_Serial.begin(115200);
  
  MSP_Serial.begin(115200, SERIAL_8N1, 18, 17);

  digitalWrite(LCD_BL_GPIO,LOW);
  digitalWrite(BUTTON_LED_GPIO,LOW);
  
  lv_init();
  lv_log_register_print_cb(log_print);
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

  ui_init();

}

int button=0;

void loop() {
  
  if(digitalRead(7)==HIGH) {
    digitalWrite(LCD_BL_GPIO,LOW);
    digitalWrite(BUTTON_LED_GPIO,LOW);
  } else{
    digitalWrite(LCD_BL_GPIO,LOW);
    digitalWrite(BUTTON_LED_GPIO,LOW);
  }

  while(MSP_Serial.available()) {
    button = MSP_Serial.read();
    USB_Serial.printf("millis %d:\tbutton: %d\n", millis(), button);
  }

  if(button>0 && button < 0xFE) {
    sprintf(button_value, "%d", button);
    // USB_Serial.println(button_value);
    tick_screen_main();
  }
  else {
    sprintf(button_value, "880+");
    // USB_Serial.println(button_value);
    tick_screen_main();
}
  //USB_Serial.printf("loop %d:\t%d\n", millis(), button);

  lv_task_handler();  // let the GUI do its work
  delay(2);     
}
