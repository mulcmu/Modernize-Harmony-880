/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

//Macros for bitwise operations
#define BitSet(arg,bits) ((arg) |= (bits))
#define BitClear(arg,bits) ((arg) &= ~(bits))
#define BitFlip(arg,bits) ((arg) ^= (bits))
#define BitTest(arg,bits) ((arg) & (bits))

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/Grace.h>

/*
 *  ======== main ========
 */
int main(void)
{
    Grace_init();                   // Activate Grace-generated configuration

    __enable_interrupt();

    /* Clear MCx bits to stop timer */
	TA0CTL &= ~(MC1 + MC0);
    
    while(1)  {

    }

}
