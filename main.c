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
	// I N I T I A L I Z A T I O N
	ledsInitialize();
	PitInitialize();
	uartInitialization();
	I2CInitialization();
	
	Delay(100);
	while(1)
	{
		// CHECKING IF INTERRUPT OCCURS
		if (get_accel() ==1)
		{
			// Sendding full 16-bit X accelerations by UART and switching suitable led on.
			showX();	// 
			// Clearing interrupt flag
			clear_accel();
		}
	}

}
