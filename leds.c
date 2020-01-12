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

	PTB->PDDR |= led_mask[ledGreen];  /* enable PTD5 as Output */
	PTB->PDDR |= led_mask[ledRed];  /* enable PTD5 as Output */
	PTB->PDDR |= led_mask[ledBlue];  /* enable PTD5 as Output */

	
	PTB->PSOR = led_mask[ledGreen];  /* switch Green LED off */
	PTB->PSOR = led_mask[ledRed];  /* switch Red LED off */
	PTB->PSOR = led_mask[ledBlue];  /* switch Red LED off */
}
/*----------------------------------------------------------------------------
  Function that blinks (x) times green led with (y) delay in mc
 *----------------------------------------------------------------------------*/
void ledgreenBlink(uint32_t x, uint32_t y){
	uint32_t count;
	
	for(count = 0; count < x; count++){	
		PTB->PCOR = led_mask[ledGreen];
		//delay_mc(y);		
		PTB->PSOR = led_mask[ledGreen];
		//delay_mc(y);
	}
}
/*----------------------------------------------------------------------------
  Function that blinks (x) times red led with (y) delay in mc
 *----------------------------------------------------------------------------*/
void ledredBlink(uint32_t x, uint32_t y){
	uint32_t count;
	
	for(count = 0; count < x; count++){	
		PTB->PCOR = led_mask[ledRed];
		//delay_mc(y);		
		PTB->PSOR = led_mask[ledRed];
	//	delay_mc(y);	
	}
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

