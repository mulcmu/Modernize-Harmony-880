
#ifndef EXTERN 
#define EXTERN 
#endif

#include "main.h"
#include "buttons.h"
#include "setup.h"


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

int main(void) {

  mcu_init();
  //16 Mhz clock frequency
  //timer A0 1ms CCR0, paused
  //UART 115200 8N1
  //P1.0 drives ESP EN pin
  //P1.6 ESP GPIO7 for backlight control
  //Port 3 outputs for button rows
  //Port 2 inputs for button columns, Interrupts enabled
  //Interrupts enabled


	ticks=0;
	last_button_scan=0;
	last_button_press = -5000;

  	while (1) {

	if(ticks-last_button_scan > 5) {
    	process_buttons();
		last_button_scan = ticks;
	}

	if(ticks-last_button_press == 60) {
		UCA0TXBUF = 0xFF;
	}

	if(ticks-last_button_press > 3000) {
        //Stop active scanning after last press
        //Setup port 2 interrupt with all rows HIGH
		TA0CTL &= ~(MC1 + MC0);
		P3OUT = 0xFE;
		P2IE = 0xFF;
		BitClear(P1OUT, BIT6);
	} else {
		BitSet(P1OUT, BIT6);
	}

    __bis_SR_register(LPM0_bits);
  }
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