#pragma once

#include <msp430.h>
#include <msp430g2553.h>
#include <stdint.h>
#include <Arduino.h>

// Macros for bitwise operations
#define BitSet(arg, bits) ((arg) |= (bits))
#define BitClear(arg, bits) ((arg) &= ~(bits))
#define BitFlip(arg, bits) ((arg) ^= (bits))
#define BitTest(arg, bits) ((arg) & (bits))

// 65535 gives 65 seconds max duration
EXTERN volatile unsigned long ticks;
EXTERN unsigned long last_button_scan;
EXTERN unsigned long last_button_press;

EXTERN uint16_t counter;