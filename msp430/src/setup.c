#ifndef EXTERN 
#define EXTERN extern
#endif

#include "setup.h"

//Cut and paste from the grace configuration to initialize the MSP

void mcu_init(void) {
        // Stop watchdog timer 
    WDTCTL = WDTPW | WDTHOLD;

    /* Port 1 Port Select 2 Register */
    P1SEL2 = BIT1 | BIT2;

    /* Port 1 Output Register */
    P1OUT = BIT0;

    /* Port 1 Port Select Register */
    P1SEL = BIT1 | BIT2;

    /* Port 1 Direction Register */
    P1DIR = BIT0 + BIT6;

    /* Port 1 Interrupt Edge Select Register */
    P1IES = 0;

    /* Port 1 Interrupt Flag Register */
    P1IFG = 0;

    /* Port 2 Output Register */
    P2OUT = BIT7;  //PULL UP reistor for 2.7

    /* Port 2 Port Select Register */
    P2SEL &= ~(BIT6 | BIT7);

    /* Port 2 Direction Register */
    P2DIR = 0;

    /* Port 2 Resistor Enable Register */
    P2REN = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;

    /* Port 2 Interrupt Edge Select Register */
    P2IES = 0;

    /* Port 2 Interrupt Flag Register */
    P2IFG = 0;

    /* Port 2 Interrupt Enable Register */
    P2IE = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;

    /* Port 3 Output Register */
    P3OUT = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;

    /* Port 3 Direction Register */
    P3DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;

    /* 
     * Basic Clock System Control 2
     * 
     * SELM_0 -- DCOCLK
     * DIVM_0 -- Divide by 1
     * ~SELS -- DCOCLK
     * DIVS_0 -- Divide by 1
     * ~DCOR -- DCO uses internal resistor
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;

    if (CALBC1_16MHZ != 0xFF) {
        /* Adjust this accordingly to your VCC rise time */
        __delay_cycles(100000);

        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
        DCOCTL = CALDCO_16MHZ;
    }

    /* 
     * Basic Clock System Control 1
     * 
     * XT2OFF -- Disable XT2CLK
     * ~XTS -- Low Frequency
     * DIVA_0 -- Divide by 1
     * 
     * Note: ~XTS indicates that XTS has value zero
     */
    BCSCTL1 |= XT2OFF | DIVA_0;

    /* 
     * Basic Clock System Control 3
     * 
     * XT2S_0 -- 0.4 - 1 MHz
     * LFXT1S_2 -- If XTS = 0, XT1 = VLOCLK ; If XTS = 1, XT1 = 3 - 16-MHz crystal or resonator
     * XCAP_1 -- ~6 pF
     */
    BCSCTL3 = XT2S_0 | LFXT1S_2 | XCAP_1;


   /* Disable USCI */
    UCA0CTL1 |= UCSWRST;

    /* 
     * Control Register 1
     * 
     * UCSSEL_2 -- SMCLK
     * ~UCRXEIE -- Erroneous characters rejected and UCAxRXIFG is not set
     * ~UCBRKIE -- Received break characters do not set UCAxRXIFG
     * ~UCDORM -- Not dormant. All received characters will set UCAxRXIFG
     * ~UCTXADDR -- Next frame transmitted is data
     * ~UCTXBRK -- Next frame transmitted is not a break
     * UCSWRST -- Enabled. USCI logic held in reset state
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCA0CTL1 = UCSSEL_2 | UCSWRST;
    
    /* 
     * Modulation Control Register
     * 
     * UCBRF_0 -- First stage 0
     * UCBRS_7 -- Second stage 7
     * ~UCOS16 -- Disabled
     * 
     * Note: ~UCOS16 indicates that UCOS16 has value zero
     */
    UCA0MCTL = UCBRF_0 | UCBRS_7;
    
    /* Baud rate control register 0 */
    UCA0BR0 = 138;
    
    /* Enable USCI */
    UCA0CTL1 &= ~UCSWRST;

    /* 
     * TA0CCTL0, Capture/Compare Control Register 0
     * 
     * CM_0 -- No Capture
     * CCIS_0 -- CCIxA
     * ~SCS -- Asynchronous Capture
     * ~SCCI -- Latched capture signal (read)
     * ~CAP -- Compare mode
     * OUTMOD_0 -- PWM output mode: 0 - OUT bit value
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    TA0CCTL0 = CM_0 | CCIS_0 | OUTMOD_0 | CCIE;

    /* TA0CCR0, Timer_A Capture/Compare Register 0 */
    TA0CCR0 = 15999;

	//1ms timer

    /* 
     * TA0CTL, Timer_A3 Control Register
     * 
     * TASSEL_2 -- SMCLK
     * ID_0 -- Divider - /1
     * MC_1 -- Up Mode
     */
    TA0CTL = TASSEL_2 | ID_0 | MC_1;

     /* Clear MCx bits to stop timer */
	TA0CTL &= ~(MC1 + MC0);


    do
    {
        // Clear OSC fault flag
        IFG1 &= ~OFIFG;

        // 50us delay
        __delay_cycles(800);
    } while (IFG1 & OFIFG);

    /* 
     * SR, Status Register
     * 
     * ~SCG1 -- Disable System clock generator 1
     * ~SCG0 -- Disable System clock generator 0
     * ~OSCOFF -- Oscillator On
     * ~CPUOFF -- CPU On
     * GIE -- General interrupt enable
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
   
    __bis_SR_register(GIE);



}