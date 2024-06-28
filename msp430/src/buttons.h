#pragma once

#include <msp430.h>
#include <msp430g2553.h>
#include <stdint.h>
#include <Arduino.h>

#include "main.h"

#define buttonRows 8 //Rows are outputs
#define buttonCols 7 //Columns are inputs

#define btn_OFF 1
#define btn_ACTIVITIES 2
#define btn_HELP 3
#define btn_L_LCD_1 4
#define btn_L_LCD_2 5
#define btn_L_LCD_3 6
#define btn_L_LCD_4 7
#define btn_R_LCD_1 8
#define btn_R_LCD_2 9
#define btn_R_LCD_3 10
#define btn_R_LCD_4 11
#define btn_LCD_LEFT 12
#define btn_LCD_RIGHT 13
#define btn_GLOW 14
#define btn_DEVICE 15
#define btn_MEDIA 16
#define btn_MUTE 17
#define btn_PREV 18
#define btn_VOL_UP 19
#define btn_VOL_DOWN 20
#define btn_CH_UP 21
#define btn_CH_DOWN 22
#define btn_DPAD_UP 23
#define btn_DPAD_LEFT 24
#define btn_DPAD_RIGHT 25
#define btn_DPAD_DOWN 26
#define btn_DPAD_OK 27
#define btn_PG_UP 28
#define btn_PG_DOWN 29
#define btn_MENU 30
#define btn_EXIT 31
#define btn_GUIDE 32
#define btn_INFO 33
#define btn_STOP 34
#define btn_REPLAY 35
#define btn_SKIP 36
#define btn_PLAY 37
#define btn_REC 38
#define btn_REW 39
#define btn_FWD 40
#define btn_PAUSE 41
#define btn_KP_1 42
#define btn_KP_2 43
#define btn_KP_3 44
#define btn_KP_4 45
#define btn_KP_5 46
#define btn_KP_6 47
#define btn_KP_7 48
#define btn_KP_8 49
#define btn_KP_9 50
#define btn_KP_0 51
#define btn_KP_CLEAR 52
#define btn_KP_ENTER 53

typedef enum{ RELEASED, DEBOUNCE, PRESSED, HELD  } ButtonState;



void process_buttons(void);