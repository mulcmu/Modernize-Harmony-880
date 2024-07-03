//ESP32-S3-WROOM-1-N16R8 16 MB (Quad SPI) 8 MB (Octal SPI)
//FQBN: esp32:esp32:esp32s3:CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi

//ESP 2.0.15, 2.0.16, 2.0.17,  3.x have issue with ST7789 screen and TFT_eSPI, panic on tft.init()
//2.0.14 works
//https://github.com/espressif/arduino-esp32/issues/9618#issuecomment-2114839060
//Fixed with USE_HSPI_PORT


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

#define IR_RECEIVE_PIN          21 
#define IR_SEND_PIN              2  
#define NO_LED_FEEDBACK_CODE
// #define USE_OPEN_DRAIN_OUTPUT_FOR_SEND_PIN
#include <IRremote.hpp> // include the library

#define BUZZER_PIN          4 
// const char * arkanoid = "Arkanoid:d=4,o=5,b=140:8g6,16p,16g.6,2a#6,32p,8a6,8g6,8f6,8a6,2g6";
// #include <NonBlockingRtttl.h>
char StarWarsInRam[] =
        "StarWars:d=32,o=5,b=45,l=2,s=N:p,f#,f#,f#,8b.,8f#.6,e6,d#6,c#6,8b.6,16f#.6,e6,d#6,c#6,8b.6,16f#.6,e6,d#6,e6,8c#6";
#include <PlayRtttl.hpp>


#define i2c_SDA 15
#define i2c_SCL 16
#include <Wire.h>
#include <SparkFun_VEML7700_Arduino_Library.h>
VEML7700 lightSensor; 

#define INPUT_5V_SUPPLY 47  //High for USB, LOW for Cradle

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
  pinMode(IR_SEND_PIN,OUTPUT);
  
  digitalWrite(LCD_BL_GPIO,HIGH);
  digitalWrite(BUTTON_LED_GPIO,HIGH);  
  digitalWrite(IR_SEND_PIN,HIGH);  

  pinMode(INPUT_5V_SUPPLY,INPUT);

  //bool begin(int sdaPin, int sclPin, uint32_t frequency)
  Wire.begin(i2c_SDA, i2c_SCL,400000);


  // pinMode(BUZZER_PIN, OUTPUT);
  // digitalWrite(BUZZER_PIN,HIGH);

  // tone(BUZZER_PIN, 700, 1000);


  if (lightSensor.begin() == false)
  {
    Serial.println("Unable to communicate with the VEML7700. Please check the wiring. Freezing...");
    while (1)
      ;
  }  

  lightSensor.setSensitivityMode(VEML7700_SENSITIVITY_x2);


  //blocks on 2.0.14 code,okay in 3.0.2 & 2.0.17
  USB_Serial.begin(115200);
  
  MSP_Serial.begin(115200, SERIAL_8N1, 18, 17);

  USB_Serial.println("Serial started....");



  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, 0);  
  // IrSender.begin();
  
  USB_Serial.println("IrReceiver started....");

  lv_init();
  lv_log_register_print_cb(log_print);
  lv_tick_set_cb(my_tick);

  USB_Serial.println("lvgl started....");


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

  USB_Serial.println("ui_init started....");

  if(digitalRead(INPUT_5V_SUPPLY)==HIGH)
    USB_Serial.println("5V from USB");
  else
    USB_Serial.println("5V from USB");

  ledcAttachPin(LCD_BL_GPIO, 1); // assign RGB led pins to channels
  ledcAttachPin(BUTTON_LED_GPIO, 2);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);

  //0 full, 255 off
  ledcWrite(1, 128);
  ledcWrite(2, 128);

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
    if (button != 255) {
      USB_Serial.printf("millis %d:\tbutton: %d\n", millis(), button);
     }
  }

  if(button>0 && button < 0xFE) {
    sprintf(button_value, "%d", button);
    // USB_Serial.println(button_value);
    tick_screen_main();
    //IrSender.sendNEC(0x0101, button, 0);
    if(button==19) 
      IrSender.sendKaseikyo_Denon(0x014, 0x09, 5);
    if(button==20)
      IrSender.sendKaseikyo_Denon(0x114, 0x17, 5);
    // tone(BUZZER_PIN, 700, 1000);
    Serial.printf("Lux: %.2f\n",lightSensor.getLux()); 
  }
  else {
    sprintf(button_value, "880+");
    // USB_Serial.println(button_value);
    tick_screen_main();
    // noTone(BUZZER_PIN);
    // digitalWrite(BUZZER_PIN,HIGH);
  }
  //USB_Serial.printf("loop %d:\t%d\n", millis(), button);

    if (IrReceiver.decode()) {
      USB_Serial.println("IR decode:");
        /*
         * Print a summary of received data
         */
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print extended info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
        } else {
            IrReceiver.resume(); // Early enable receiving of the next IR frame
            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x10) {
            // do something
        } else if (IrReceiver.decodedIRData.command == 0x11) {
            // do something else
        }
    }

  lv_task_handler();  // let the GUI do its work
  delay(2);     
}
