#include <MKL05Z4.H>
#include "accelerometer.h"
#include "I2C.h"
#include "uart.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int16_t acc_X=0, acc_Y=0, acc_Z=0;



void Delay (uint32_t dly) {
  volatile uint32_t t;

	for (t=dly*1000; t>0; t--)
		;
}

/*
 Initializes mma8451 sensor. I2C has to already be enabled.
 */
int init_mma()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;       // Turn on clock to Port A module

  PORTA->PCR[10] |= (0|PORT_PCR_ISF_MASK|     // Clear the interrupt flag
                       PORT_PCR_MUX(0x1)|     // PTA10 is configured as GPIO
                       PORT_PCR_IRQC(0xA));   // PTA10 is configured for falling edge interrupts  
	Delay(100);	
	//check for e vice
	if(i2c_read_byte(MMA_ADDR, REG_WHOAMI) == WHOAMI)	
		{
		  Delay(100);
		  //turn on data ready irq; defaults to int2 (PTA10)
		  i2c_write_byte(MMA_ADDR, REG_CTRL4, 0x01);
		  Delay(100);
		  //set active 14bit mode and 100Hz (0x19)
		  i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
		  return 1;
		}
		//else error
		return 0;
}
void read_full_xyz()
{
	//Delay(1);
	int i;
	uint8_t data[6];
	Delay(100);
	i2c_read_setup(MMA_ADDR , REG_XHI);
	
	for( i=0;i<6;i++)	{
		if(i==5)
			data[i] = i2c_repeated_read(1);
		else
			data[i] = i2c_repeated_read(0);
	}
	
	acc_X = (((int16_t) data[0])<<8) | data[1];
	acc_Y = (((int16_t) data[2])<<8) | data[3];
	acc_Z = (((int16_t) data[4])<<8) | data[5];
}
int16_t get_acc_X()
{
	return acc_X;
}

int16_t get_acc_Y()
{
	return acc_Y;
}

int16_t get_acc_Z()
{
	return acc_Z;
}

void showAcceleration(void)
{
		char strx[6];
		char stry[6];
		char strz[6];	
		read_full_xyz();
		char text[14] = "Acceleration:";
		transmitString(&text[0]);
		sprintf(strx, "%d", get_acc_X());
		sprintf(stry, "%d", get_acc_Y());
		sprintf(strz, "%d", get_acc_Z());
		while (!(UART0->S1 & UART0_S1_TDRE_MASK));
		transmitString(&strx[0]);
		while (!(UART0->S1 & UART0_S1_TDRE_MASK));
		transmitString(&stry[0]);
		while (!(UART0->S1 & UART0_S1_TDRE_MASK));
		transmitString(&strz[0]);
}
