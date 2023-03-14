/*
 *  This file is automatically generated and does not require a license
 *
 *  ==== WARNING: CHANGES TO THIS GENERATED FILE WILL BE OVERWRITTEN ====
 *
 *  To make changes to the generated code, use the space between existing
 *      "USER CODE START (section: <name>)"
 *  and
 *      "USER CODE END (section: <name>)"
 *  comments, where <name> is a single word identifying the section.
 *  Only these sections will be preserved.
 *
 *  Do not move these sections within this file or change the START and
 *  END comments in any way.
 *  ==== ALL OTHER CHANGES WILL BE OVERWRITTEN WHEN IT IS REGENERATED ====
 *
 *  This file was generated from
 *      C:/ti/grace_3_10_00_82/packages/ti/mcu/msp430/csl/interrupt_vectors/InterruptVectors_init.xdt
 */
#include <msp430.h>
#include "_Grace.h"

/* USER CODE START (section: InterruptVectors_init_c_prologue) */
char counter=0;
/* USER CODE END (section: InterruptVectors_init_c_prologue) */

/*
 *  ======== InterruptVectors_graceInit ========
 */
void InterruptVectors_graceInit(void)
{
}


/* Interrupt Function Prototypes */



/*
 *  ======== PORT2 Interrupt Service Routine ========
 *
 * Here are several important notes on using PORTx interrupt Handler:
 *
 * 1. User must explicitly clear the port interrupt flag before exiting
 *
 *    PxIFG &= ~(BITy);
 *
 * 2. User could also exit from low power mode and continue with main
 *    program execution by using the following instruction before exiting
 *    this interrupt handler.
 *
 *    __bic_SR_register_on_exit(LPMx_bits);
 *
 */
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR_HOOK(void)
{
    /* USER CODE START (section: PORT2_ISR_HOOK) */

	P2IFG = 0;

	P1OUT ^= BIT6;

	P3OUT=BIT0;

	/* Start timer in up mode */
    TA0CTL |= MC_1;

    P2IE = 0;

    counter=1;

    /* USER CODE END (section: PORT2_ISR_HOOK) */
}

/*
 *  ======== Timer0_A3 Interrupt Service Routine ======== 
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void)
{
    /* USER CODE START (section: TIMER0_A0_ISR_HOOK) */

	char button = 0;

	switch (P3OUT)  {
	case BIT0: //ROWA
		switch (P2IN) {
		case BIT0:
			button = 1;
			break;
		case BIT1:
			button = 5;
			break;
		case BIT2:
			button = 9;
			break;
		case BIT3:
			button = 13;
			break;
		case BIT4:
			button = 17;
			break;
		case BIT5:
			button = 21;
			break;
		case BIT6:
			button = 25;
			break;
		}
		break;
	case BIT1:  //ROWB
		switch (P2IN) {
		case BIT0:
			button = 2;
			break;
		case BIT1:
			button = 6;
			break;
		case BIT2:
			button = 10;
			break;
		case BIT3:
			button = 14;
			break;
		case BIT4:
			button = 18;
			break;
		case BIT5:
			button = 22;
			break;
		case BIT6:
			button = 26;
			break;
		}
		break;
	case BIT2:  //ROWC
		switch (P2IN) {
		case BIT0:
			button = 3;
			break;
		case BIT1:
			button = 7;
			break;
		case BIT2:
			button = 11;
			break;
		case BIT3:
			button = 15;
			break;
		case BIT4:
			button = 19;
			break;
		case BIT5:
			button = 23;
			break;
		case BIT6:
			button = 27;
			break;
		}
		break;
	case BIT3: //ROWD
		switch (P2IN) {
		case BIT0:
			button = 4;
			break;
		case BIT1:
			button = 8;
			break;
		case BIT2:
			button = 12;
			break;
		case BIT3:
			button = 16;
			break;
		case BIT4:
			button = 20;
			break;
		case BIT5:
			button = 24;
			break;
		case BIT6:
			button = 28;
			break;
		}
		break;
	case BIT4: //ROWE
		switch (P2IN) {
		case BIT0:
			button = 42;
			break;
		case BIT1:
			button = 46;
			break;
		case BIT2:
			button = 50;
			break;
		case BIT3:
			button = 29;
			break;
		case BIT4:
			button = 33;
			break;
		case BIT5:
			button = 37;
			break;
		case BIT6:
			button = 41;
			break;
		}
		break;
	case BIT5: //ROWF
		switch (P2IN) {
		case BIT0:
			button = 43;
			break;
		case BIT1:
			button = 47;
			break;
		case BIT2:
			button = 51;
			break;
		case BIT3:
			button = 30;
			break;
		case BIT4:
			button = 34;
			break;
		case BIT5:
			button = 38;
			break;
		}
		break;
	case BIT6: //ROWG
		switch (P2IN) {
		case BIT0:
			button = 44;
			break;
		case BIT1:
			button = 48;
			break;
		case BIT2:
			button = 52;
			break;
		case BIT3:
			button = 31;
			break;
		case BIT4:
			button = 35;
			break;
		case BIT5:
			button = 39;
			break;
		}
		break;
	case BIT7: //ROWH
		switch (P2IN) {
		case BIT0:
			button = 45;
			break;
		case BIT1:
			button = 49;
			break;
		case BIT2:
			button = 53;
			break;
		case BIT3:
			button = 32;
			break;
		case BIT4:
			button = 36;
			break;
		case BIT5:
			button = 40;
			break;
		}
		break;


	}  //switch P3OUT


	if(button == 0)
		counter++;
	else
	  UCA0TXBUF = button;

	P3OUT = P3OUT << 1;

	if (P3OUT==0)
		P3OUT = BIT0;

	if (counter == 0xFF) {
		TA0CTL &= ~(MC1 + MC0);
		P3OUT = 0xFF;
		UCA0TXBUF = 0xFF;
		P2IE = 0xFF;
	}


    /* USER CODE END (section: TIMER0_A0_ISR_HOOK) */
}

