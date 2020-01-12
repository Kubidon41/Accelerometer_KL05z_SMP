#include "MKL05Z4.h"                    	/* Device header */
#include "leds.h"
#include "TPM.h"
#include "uart.h"
#include "I2C.h"
#include "accelerometer.h"
#include <stdio.h>

#include <stdlib.h>

int main()
{
	ledsInitialize();
	uartInitialization();
	uartTest();
	//TPMInitialize();
	I2CInitialization();
	//init_mma();

	Delay(100);
	while(1)
	{
		showAcceleration();
		Delay(1000);
	}

}
