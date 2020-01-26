#include <MKL05Z4.H>
#include "accelerometer.h"
#include "I2C.h"
#include "uart.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "leds.h"													/* Leds functions for FRDM46-KL46 */	
int16_t acc_X=0;

void Delay (uint32_t dly) 
{
  volatile uint32_t t;
	for (t=dly*1000; t>0; t--);
}

// Reading full 16-bit X accelerations.
void read_full_x()
{
	uint8_t data[2];

	data[0] = i2c_read_byte(MMA_ADDR, REG_XHI);
	Delay(100);
	data[1] = i2c_read_byte(MMA_ADDR, REG_XLO);

	acc_X = (((int16_t)data[0])<<8) | data[1];
	acc_X/=4;
}
// Sendding full 16-bit X accelerations by UART and switching suitable led on.
void showX()
{
	int16_t Xcalibrated;
	char temp[8];	
	read_full_x();
	sprintf(temp, "%d", acc_X);
	transmitString(&temp[0]);
	// Acceleration > 2g  =>  Violet color 
	if(acc_X > 4000)
	{
		PTB->PSOR = led_mask[ledGreen];	
		PTB->PCOR = led_mask[ledRed];	
		PTB->PCOR = led_mask[ledBlue];	
		Delay(100);
	}
	// Acceleration > 0.25g  =>  Red color 
	else if(acc_X > 500)
	{
		PTB->PSOR = led_mask[ledGreen];	
		PTB->PCOR = led_mask[ledRed];	
		PTB->PSOR = led_mask[ledBlue];	
	}
	// Acceleration < 0.25g  =>  Green color 
	else if(acc_X < -500)
	{
		PTB->PCOR = led_mask[ledGreen];	
		PTB->PSOR = led_mask[ledRed];	
		PTB->PSOR = led_mask[ledBlue];	
	}
	else
	{
		PTB->PSOR = led_mask[ledGreen];	
		PTB->PSOR = led_mask[ledRed];	
		PTB->PSOR = led_mask[ledBlue];	
	}

}
int16_t get_acc_X()
{
	return acc_X;
}
