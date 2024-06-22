
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


void delay_ms(unsigned int ms) {
  while (ms) {
    __delay_cycles(16000);
    ms--;
  }
}

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR_HOOK(void) {
  //start timer A0 and configure for matrix scanning when button press detected
  P2IFG = 0;
  P3OUT = BIT0;

  /* Start timer in up mode */
  TA0CTL |= MC_1;
  P2IE = 0;
  ticks = 0;
  last_button_scan=0;
  last_button_press=0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void) {
  // CCIFG is reset automatically;
  ticks++;
  __bic_SR_register_on_exit(LPM0_bits);
}




void setup()
{
  Serial.println(TA0CCR0);
  mcu_init();

  pinMode(P1_6, OUTPUT);
  pinMode(P1_0, OUTPUT);

  Serial.begin(9600);
  Wire.begin();
	
  ticks=0;
	last_button_scan=0;
	last_button_press = -5000;
  
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(P1_0, HIGH);
  digitalWrite(P1_6, HIGH);
  Serial.println(TA0CCR0);

}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(RED_LED, HIGH);
  // wait for a second
  delay(500);
  // turn the LED off by making the voltage LOW
  digitalWrite(RED_LED, LOW);
  // wait for a second
  delay(500);
  Serial.println(millis());

	// if(ticks-last_button_scan > 5) {
  //   process_buttons();
	// 	last_button_scan = ticks;
	// }

	// if(ticks-last_button_press == 60 ) {
	// 	Serial.print(37);
	// }

	// if(ticks-last_button_press > 3000) {
  //       //Stop active scanning after last press
  //       //Setup port 2 interrupt with all rows HIGH
	// 	TA0CTL &= ~(MC1 + MC0);
	// 	P3OUT = 0xFE;
	// 	P2IE = 0xFF;
		// BitClear(P1OUT, BIT6);
	// } else {
	// 	BitSet(P1OUT, BIT6);
	// }

  //  __bis_SR_register(LPM0_bits);
  
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