/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    leds.h
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/

#ifndef leds_h
#define leds_h

#include "MKL05Z4.h"   /* Device header */
//#include "extra.h"

#define ledRed 0  //Green led is first in led_mask
#define ledGreen 1  //Red led is second in led_mask
#define ledBlue 2  //Red led is second in led_mask

const static uint32_t led_mask[] = {1UL << 8, 1UL << 9, 1UL << 10};  //Green led is Port D bit 5, Red led is Port E bit 29

void ledsInitialize(void);

void ledsOff (void);
void ledsOn (void);

#endif
