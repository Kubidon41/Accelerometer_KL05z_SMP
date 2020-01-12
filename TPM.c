#include "MKL05Z4.h"  
#include "leds.h"


void TPMInitialize(void)
{
	ledsInitialize();

	// clock enable for port D
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	// set clock source
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); //2.4 Multipurpose Clock Generator Internal Reference Clock (MCGIRCLK)
	
	//2.5 - configuration:
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;	// MCGIRCLK active
	MCG->C1 |= MCG_C1_IREFS_MASK;	// The slow internal reference clock is selected
	
	// set counting up
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;
	
	// set prescaler:
	TPM0->SC |= TPM_SC_PS(5); //	Divide by 32
	
	// set counter value:
	TPM0->CNT &= TPM_CNT_COUNT(0x0000);
	// set modulo
	TPM0->MOD &=TPM_MOD_MOD(2000);
		
	// set timer in output compare mode
	TPM0->CONTROLS[0].CnSC &= ~TPM_CnSC_MSB_MASK;
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_MSA_MASK;
	TPM0->CONTROLS[0].CnSC &= ~TPM_CnSC_ELSA_MASK;
	TPM0->CONTROLS[0].CnSC &= ~TPM_CnSC_ELSB_MASK;

	
	// enable timer TPM
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM0->SC |= TPM_SC_TOIE_MASK;
  // set priority and clear pending interrupts
	NVIC_SetPriority(TPM0_IRQn,3);
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
}

void TPM0_IRQHandler(void)
{
	static uint16_t counter =0;
	// clear pending interrupts
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	
	//clearing status flag
	TPM0->SC |=TPM_SC_TOF_MASK;   								 
	
	// toggle diod
	if (counter % 2 == 0)
	PTB->PTOR = (led_mask[ledGreen]);
	else
	PTB->PTOR = (led_mask[ledRed]);	
	counter++;
}

