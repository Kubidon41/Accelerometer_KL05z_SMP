#include "MKL05Z4.h"                    	/* Device header */
#include "I2C.h"													/* Leds functions for FRDM46-KL46 */
#include <stdio.h>
#include <string.h>
#include "accelerometer.h"

#define I2C_M_START I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART I2C0->C1 |= I2C_C1_RSTA_MASK
#define I2C_TRAN I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC I2C0->C1 &= ~I2C_C1_TX_MASK
#define BUSY_ACK while(I2C0->S & 0x01)
#define TRANS_COMP while(!(I2C0->S & 0x80))
#define I2C_WAIT i2c_wait();

#define NACK I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK I2C0->C1 &= ~I2C_C1_TXAK_MASK
void i2c_start()
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}
 void I2CInitialization()
{
	uint8_t temp;
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
  SIM->SCGC5 |= (SIM_SCGC5_PORTB_MASK);

	PORTB->PCR[3] = PORT_PCR_MUX(2);  
	PORTB->PCR[4] = PORT_PCR_MUX(2);  
	
	//	I2C baud rate = bus speed (Hz)/(mul � SCL divider)
	//	bus speed (Hz) = 21000000000
	//	ICR = 14 => SCL = 56		mul = 0
	//	set to 375k baud

 	I2C0->F = (I2C_F_ICR(14));
		
	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);
	I2C0->C1 |= (I2C_C1_IICIE_MASK);
	
	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
	i2c_write_byte(MMA_ADDR, XYZ_DATA_CFG, 1);
	Delay(100);
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 1);

}  


void i2c_wait(void) {
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {
	} 
  I2C0->S |=I2C_S_IICIF_MASK;
}


//send device and register addresses
//read a byte and ack/nack as appropriate
// #pragma no_inline 

//////////funcs for reading and writing a single byte
//using 7bit addressing reads a byte from dev:address
// #pragma no_inline 
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;
	i2c_start();							/*set to transmit mode */
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */
	
	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */
		
	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */
	
	I2C_REC;						   /*set to recieve mode */
	NACK;									 /*set NACK after read	*/
	
	data = I2C0->D;					/*dummy read	*/
	I2C_WAIT								/*wait for completion */
	
	I2C_M_STOP;							/*send stop	*/
	data = I2C0->D;					/*read data	*/

	return data;
}



//using 7bit addressing writes a byte data to dev:address
#pragma no_inline 
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{
	
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */
	
	I2C0->D =  address;		/*send write address	*/
	I2C_WAIT
		
	I2C0->D = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;
}
