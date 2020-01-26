/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    leds.c
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/

#include "leds.h"												//Declarations

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void ledsInitialize(void){
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* Enable Clock to Port B */ 
	PORTB->PCR[8] = PORT_PCR_MUX(1UL);  /* Pin PTB8 is GPIO */
	PORTB->PCR[9] = PORT_PCR_MUX(1UL);  /* Pin PTB9 is GPIO */
	PORTB->PCR[10] = PORT_PCR_MUX(1UL);  /* Pin PTB10 is GPIO */

	PTB->PDDR |= led_mask[ledGreen];  /* enable PTB9 as Output */
	PTB->PDDR |= led_mask[ledRed];  /* enable PTB10 as Output */
	PTB->PDDR |= led_mask[ledBlue];  /* enable PTB11 as Output */

	PTB->PSOR = led_mask[ledGreen];  /* switch Green LED off */
	PTB->PSOR = led_mask[ledRed];  /* switch Red LED off */
	PTB->PSOR = led_mask[ledBlue];  /* switch Red LED off */
}

/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void ledsOff(void) {
		PTB->PSOR = led_mask[ledGreen];          /* switch Red LED off  */
	  PTB->PSOR = led_mask[ledRed];       /* switch Green LED off  */
}
/*----------------------------------------------------------------------------
  Function that turns all LEDs on
 *----------------------------------------------------------------------------*/
void ledsOn(void) {
		PTB->PCOR = led_mask[ledGreen];      	/* switch Red LED on  */
	  PTB->PCOR = led_mask[ledRed];     	/* switch Green LED on */
}

