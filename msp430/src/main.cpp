
#ifndef EXTERN 
#define EXTERN 
#endif

#include <Arduino.h>
#include <Wire.h>  //comment out line in twi_disable for 'UCBzCTLW0' undeclared error


#include "main.h"
#include "buttons.h"
#include "setup.h"


//P1.0 ESP Enable
//P1.6 ESP to GPIO7 HIGH Backlight on


#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR_HOOK(void) {
  //Disable interrupt and configure for matrix scanning when button press detected
  P2IFG = 0;
  P3OUT = BIT0;
  P2IE = 0;
  last_button_scan=0;
  last_button_press=millis();
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void) {
  // CCIFG is reset automatically;
  __bic_SR_register_on_exit(LPM0_bits);
}




void setup()
{
  Serial.println("Setup()");
  mcu_init();

  pinMode(P1_1, INPUT_PULLUP);  //Fuelgauge alert
  pinMode(P1_3, INPUT_PULLUP);  //Battery Powered
  pinMode(P1_4, INPUT_PULLDOWN);  //ChargeStatus
  pinMode(P1_5, INPUT_PULLUP);  //3v3VP Enable

  Serial.begin(115200);
  Wire.begin();
	
	last_button_scan=0;
	last_button_press = 0;
  
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(P1_5, HIGH);

  Serial.println("loop");
  
  //Start timer in up mode for 1ms wakeups
  TA0CTL |= MC_1;  
 
}

void loop()
{

	if(millis()-last_button_scan > 5) {
    last_button_scan = millis();
    process_buttons();
	}

	if(millis()-last_button_press > 75 ) {
		Serial.write(0xFF);
	}

	if(millis()-last_button_press > 10000) {
    //Stop active scanning after last press
    //Setup port 2 interrupt with all rows HIGH
		P3OUT = 0xFE;
    P2IFG = 0;
		P2IE = 0xFF;
		digitalWrite(P1_5, LOW);
	} else {
		digitalWrite(P1_5, HIGH);
	}

  __bis_SR_register(LPM0_bits);
  
}

/*
__bic_SR_register_on_exit(LPM0_bits);
__bis_SR_register(LPM0_bits);
__no_operation();
__bis_SR_register(LPM0_bits | GIE);
__enable_interrupt();
__disable_interrupt(); */

/*


*/