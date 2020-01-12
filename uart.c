#include "MKL05Z4.h"                    	/* Device header */
#include "uart.h"													/* Leds functions for FRDM46-KL46 */
#include <stdio.h>
#include <string.h>
 void uartInitialization()
{
	//MCG->C1 |=MCG_C1_IRCLKEN_MASK;
	uint32_t divisor;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
  SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB->PCR[1] = PORT_PCR_MUX(2);  /* Pin PTB1 is TX */
	PORTB->PCR[2] = PORT_PCR_MUX(2);  /* Pin PTB2 is RX */
	
	SIM->SOPT2 |=SIM_SOPT2_UART0SRC(1);
	
		//Disable UART0 before changing registers
  UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
	
	UART0->C4 = UART0_C4_OSR(31);
	
	divisor = 41943040/(9600*32);
	UART0->BDH = UART0_BDH_SBR(divisor>>8);
	UART0->BDL = UART0_BDL_SBR(divisor);

	UART0->C1 = 0;
	
	UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );
}    

void transmitString(char ch[])
{
	uint8_t len = (uint8_t)strlen(ch);
	for(uint8_t i = 0; i< len; i++)
	{
			while (!(UART0->S1 & UART0_S1_TDRE_MASK));
			UART0->D = ch[i];
	}
	while (!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = (uint8_t)'\n';
}

void uartTest(void)
{
	char test[10] = "Test UART";
	transmitString(&test[0]);
	char press[10] = "Press 'q'";
	transmitString(&press[0]);
	while(UART0->D != 'q')
	{}
	char completed[15] = "Test Completed";
	transmitString(&completed[0]);
}
