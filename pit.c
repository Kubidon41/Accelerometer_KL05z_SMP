
#include "MKL05Z4.h"                    	/* Device header */
#include "leds.h"													/* Leds functions for FRDM46-KL46 */
#include "accelerometer.h"
#include "pit.h"													

//#include "buttons.h"
#define GreenLED 0

//global varieble
int vCounter = 0;
int8_t accel = 0;

void PitInitialize(void)
{
//	Led initialization function
	ledsInitialize();
	
  SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; // clock to PIT
  PIT->MCR = 0x00;   // enable PIT module

	// timer enable 
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;	
	
	// set load value
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(0x00040000);
	//drugi kanal:
	//PIT->CHANNEL[1].LDVAL = PIT_LDVAL_TSV(0x00100000);
	
	
	// interrupt enable
	PIT->CHANNEL[0].TCTRL |=PIT_TCTRL_TIE_MASK;	
	//PIT->CHANNEL[1].TCTRL |=PIT_TCTRL_TIE_MASK;	
	
	//set priority and clear pending interrupts   1.9
	NVIC_SetPriority(PIT_IRQn,2);
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
	

	// start counting
		PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
		//PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void PIT_IRQHandler()
{
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PIT_IRQn);
	{
		//clearing status flag for this channel:
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		//PTB->PTOR = led_mask[ledGreen];
		//PTB->PTOR = led_mask[ledRed];	
		accel = 1;
	}
}
int8_t get_accel()
{
	return accel;
}

void clear_accel()
{
	accel = 0;
}