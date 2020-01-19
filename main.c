#include "MKL05Z4.h"                    	/* Device header */
#include "leds.h"
#include "TPM.h"
#include "uart.h"
#include "I2C.h"
#include "pit.h"
#include "accelerometer.h"
#include <stdio.h>

#include <stdlib.h>

int main()
{

	ledsInitialize();
	PitInitialize();
	uartInitialization();
	uartTest();
	//TPMInitialize();
	I2CInitialization();
	//init_mma();
	//i2c_read_setup(MMA_ADDR, REG_WHOAMI);
	Delay(100);
	while(1)
	{
		if (get_accel() ==1)
		{
			showX();
			clear_accel();
		}
		//i2c_read_byte(MMA_ADDR, REG_WHOAMI);
		//showAcceleration();
		//int8_t t;
		//read_full_x();
		//t = i2c_read_byte(MMA_ADDR, REG_XHI);
		//sprintf(temp, "%d", t);
		//sprintf(temp, "%d", get_acc_X());
		//transmitString(&temp[0]);
		//Delay(1000);
	}

}
