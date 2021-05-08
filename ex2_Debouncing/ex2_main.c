/******************************************************************************
 *                                                                            *
 * Exercise 2                                                                 *
 *                                                                            *
 * Task 1: Push Da Button                   X /  4 Points                     *
 * Task 2: Advanced Button Handling         X /  4 Points                     *
 * Comprehension Questions                  X /  2 Points                     *
 *                                        ----------------                    *
 *                                         XX / 10 Points                     *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * name:                    Santosh Kumar Kasam                               *
 * matriculation number:    1533833                                           *
 * e-mail:                  santosh.kasam@student.uni-siegen.de               *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * Hardware Setup                                                             *
 *                                                                            *
 *                               MSP430FR5969                                 *
 *                            -----------------                               *
 *                           |                 |                              *
 *                   (S1) -->|P4.5         P4.6|--> (LED1)                    *
 *                   (S2) -->|P1.1         P1.0|--> (LED2)                    *
 *                           |                 |                              *
 *                            -----------------                               *
 *                                                                            *
 ******************************************************************************/

// Select the task you are working on:
//#define TASK_1
#define TASK_2

#include <msp430fr5969.h>



#ifdef TASK_1
/*******************************************************************************
** Task 1
*******************************************************************************/

/* MAIN PROGRAM */
void main(void)
{
    // Stop watchdog timer.
    WDTCTL = WDTPW | WDTHOLD;

    // Initialize the clock system to generate 1 MHz DCO clock.
    CSCTL0_H    = CSKEY_H;              // Unlock CS registers.
    CSCTL1      = DCOFSEL_0;            // Set DCO to 1 MHz, DCORSEL for
                                        //   high speed mode not enabled.
    CSCTL2      = SELA__VLOCLK |        // Set ACLK = VLOCLK = 10 kHz.
                  SELS__DCOCLK |        //   Set SMCLK = DCOCLK.
                  SELM__DCOCLK;         //   Set MCLK = DCOCLK.
                                        // SMCLK = MCLK = DCOCLK = 1 MHz.
    CSCTL3      = DIVA__1 |             //   Set ACLK divider to 1.
                  DIVS__1 |             //   Set SMCLK divider to 1.
                  DIVM__1;              //   Set MCLK divider to 1.
                                        // Set all dividers to 1.
    CSCTL0_H    = 0;                    // Lock CS registers.

    /* TODO INITIALIZATION */
    // Initialize unused GPIOs to minimize energy-consumption.
    // Port 1:
    P1DIR = 0xFF;
    P1OUT = 0x00;
    // Port 2:
    P2DIR = 0xFF;
    P2OUT = 0x00;
    // Port 3:
    P3DIR = 0xFF;
    P3OUT = 0x00;
    // Port 4:
    P4DIR = 0xFF;
    P4OUT = 0x00;
    // Port J:
    PJDIR = 0xFFFF;
    PJOUT = 0x0000;

    // Initialize port 1:
    P1DIR |= BIT0;                      // P1.0 is set as output pin for LED2
    P1OUT &= ~BIT0;                     // P1.0 - output for LED2, off.

    P1DIR &= ~BIT1;                     // P1.1 is set as an input pin
    P1REN |= BIT1;                      // The resistor is enabled
    P1OUT |= BIT1;                      // The resistor is set to be pullup resistor

    // Initialize port 4:
    P4DIR |= BIT6;                      // P4.6 is set as output pin for LED1
    P4OUT &= ~BIT6;                     // P4.6 - output for LED1, off.

    P4DIR &= ~BIT5;                     // P4.5 is set as input pin
    P4REN |= BIT5;                      // The resistor is enabled
    P4OUT |= BIT5;                      // The resistor is set to be pullup resistor

    // Disable the GPIO power-on default high-impedance mode to activate the
    // previously configured port settings.
    PM5CTL0 &= ~LOCKLPM5;

    /* MAIN LOOP */
    while(1)
    {
        /* TODO POLLING */

        /* The below conditions are written to enable the LED outputs.
         * The number of writing operations are minimized by checking if
         * The corresponding pin is already equal to the required value*/

        // Condition to switch LED2 green
        if( !( P1IN & BIT1 ) && !(P1OUT & BIT0)) {           // Condition: if Switch is ON and P1.1 output not enabled already
            P1OUT |= BIT0;
        }else if( ( P1IN & BIT1 ) && (P1OUT & BIT0) ) {     // Condition: if Switch is OFF and P1.1 output is ON
            P1OUT &= ~BIT0;
        }

        // Condition to switch LED1 red
        if( !( P4IN & BIT5 ) & !(P4OUT & BIT6) ) {          // Condition: if Switch is ON and P4.6 output not enabled already
            P4OUT |= BIT6;
        }else if( (P4IN & BIT5) && (P4OUT & BIT6)) {        // Condition: if Switch is OFF and P4.6 output is ON
            P4OUT &= ~BIT6;
        }
    }
}

/******************************************************************************/
#endif /* TASK_1 */



#ifdef TASK_2
/*******************************************************************************
** Task 2
*******************************************************************************/

/* MAIN PROGRAM */
void main(void)
{
    // Stop watchdog timer.
    WDTCTL = WDTPW | WDTHOLD;

    // Initialize the clock system to generate 1 MHz DCO clock.
    CSCTL0_H    = CSKEY_H;              // Unlock CS registers.
    CSCTL1      = DCOFSEL_0;            // Set DCO to 1 MHz, DCORSEL for
                                        //   high speed mode not enabled.
    CSCTL2      = SELA__VLOCLK |        // Set ACLK = VLOCLK = 10 kHz.
                  SELS__DCOCLK |        //   Set SMCLK = DCOCLK.
                  SELM__DCOCLK;         //   Set MCLK = DCOCLK.
                                        // SMCLK = MCLK = DCOCLK = 1 MHz.
    CSCTL3      = DIVA__1 |             //   Set ACLK divider to 1.
                  DIVS__1 |             //   Set SMCLK divider to 1.
                  DIVM__1;              //   Set MCLK divider to 1.
                                        // Set all dividers to 1.
    CSCTL0_H    = 0;                    // Lock CS registers.

    /* TODO INITIALIZATION */
    // Initialize unused GPIOs to minimize energy-consumption.
    // Port 1:
    P1DIR = 0xFF;
    P1OUT = 0x00;
    // Port 2:
    P2DIR = 0xFF;
    P2OUT = 0x00;
    // Port 3:
    P3DIR = 0xFF;
    P3OUT = 0x00;
    // Port 4:
    P4DIR = 0xFF;
    P4OUT = 0x00;
    // Port J:
    PJDIR = 0xFFFF;
    PJOUT = 0x0000;

    // Initialize port 1:
    P1DIR |= BIT0;                      // P1.0 is set as output pin for LED2
    P1OUT &= ~BIT0;                     // P1.0 - output for LED2, off.

    P1DIR &= ~BIT1;                     // P1.1 is set as an input pin
    P1REN |= BIT1;                      // The resistor is enabled
    P1OUT |= BIT1;                      // The resistor is set to be a pullup resistor

    P1IE |= BIT1;                       // Enabling interrupt capability for P1.1
    P1IES |= BIT1;                      // Selecting falling edge for interrupts

    // Initialize port 4:
    P4DIR |= BIT6;                      // P4.6 is set as output pin for LED1
    P4OUT &= ~BIT6;                     // P4.6 - output for LED1, off.

    P4DIR &= ~BIT5;                     // P4.5 is set as input pin
    P4REN |= BIT5;                      // The resistor is enabled
    P4OUT |= BIT5;                      // The resistor is set to be a pullup resistor

    P4IE |= BIT5;                       // Enabling interrupt capability for P1.1
    P4IES |= BIT5;                      // Selecting falling edge for interrupts

    // Disable the GPIO power-on default high-impedance mode to activate the
    // previously configured port settings.
    PM5CTL0 &= ~LOCKLPM5;

    // Clear interrupt flags that have been raised due to high-impedance settings.
    P1IFG &= ~BIT1;
    P4IFG &= ~BIT5;

    // Enable interrupts globally.
    __bis_SR_register(GIE);

    /* MAIN LOOP */
    while(1)
    {

    }
}

/* ISR PORT 1 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    switch(P1IV)
    {
    case P1IV_P1IFG0:                   // P1.0
        break;
    case P1IV_P1IFG1:                   // P1.1

        /* TODO PORT ISR */

        __delay_cycles(30000);          // ISR is delayed by 30,000 micro seconds (30ms)

        P1IFG &= ~BIT1;                 // Flags raised meanwhile are cleared

        if ( !(P1IN & BIT1) ){          // Checking if the push button P1.1 is still ON
            P1OUT ^= BIT0;                  // Toggle P1.0 on each interrupt.
        }

        break;
    case P1IV_P1IFG2:                   // P1.2
        break;
    case P1IV_P1IFG3:                   // P1.3
        break;
    case P1IV_P1IFG4:                   // P1.4
        break;
    case P1IV_P1IFG5:                   // P1.5
        break;
    case P1IV_P1IFG6:                   // P1.6
        break;
    case P1IV_P1IFG7:                   // P1.7
        break;
    }
}

/* ISR PORT 4 */
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
    switch(P4IV)
    {
    case P4IV_P4IFG0:                   // P4.0
        break;
    case P4IV_P4IFG1:                   // P4.1
        break;
    case P4IV_P4IFG2:                   // P4.2
        break;
    case P4IV_P4IFG3:                   // P4.3
        break;
    case P4IV_P4IFG4:                   // P4.4
        break;
    case P4IV_P4IFG5:                   // P4.5

        /* TODO PORT ISR */
        __delay_cycles(30000);          // ISR is delayed by 30,000 micro seconds (30ms)

        P4IFG &= ~BIT5;                 // Flags raised meanwhile are cleared

        if ( !(P4IN & BIT5) ) {         // Checking if the push button P4.5 is still ON
            P4OUT ^= BIT6;                  // Toggle P4.6 on each interrupt.
        }

        break;
    case P4IV_P4IFG6:                   // P4.6
        break;
    case P4IV_P4IFG7:                   // P4.7
        break;
    }
}

/******************************************************************************/
#endif /* TASK_2 */
