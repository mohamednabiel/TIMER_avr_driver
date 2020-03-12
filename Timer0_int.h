/*
 * Timer0_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: MANSI-PC
 */

#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

/*
 * TIMER0_INT.h
 *
 *  Created on: JAN 25, 2020
 *      Author: NABIL
 */
#include "utils.h"
/*REGISTE MEMORY MAPPING*/

#define TIMSK *((volatile u8*)   (0x59))
#define TIFR  *((volatile U8*)   (0X58))
#define TCCR0 *((volatile u8*)	 (0x53))
#define OCR0	*((volatile u8*) (0x5C))
#define TCNT0 *((volatile u8*)	 (0x52))


#define Timer0_NormanlMode 0
#define Timer0_CTCMode 	   1
#define Timer0_ErrorMode   2

#define Timer0_OVFlowINTEnable  0
#define Timer0_OVFlowINTDisable 1
#define Timer0_OVFlowINTError	2

#define Timer0_OPCompINTEnable  0
#define Timer0_OPCompINTDisable 1
#define Timer0_OPCompINTError   2


#define Timer0_NOPRENOCLK      0 //disable timer
#define Timer0_NOPRECLK        1
#define Timer0_NOPRECLK_8      2
#define Timer0_NOPRECLK_64     3
#define Timer0_NOPRECLK_256    4
#define Timer0_NOPRECLK_1024   5
#define Timer0_EXTCLK_FALLING  6
#define Timer0_EXTCLK_RISING   7
#define Timer0_ErroePresck     8

#define TIMER0_u8OK  0
#define TIMER0_u8NOK 1

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)


//comment type in dio
/*
!Comment:
Description: this Function Sets the DIO Pin Direction
Input: 1)u8PortNbCpy->the Port Index. [0:3]
	   2)u8PinNbCpy-> the Pin number. [0:7]
	   3)u8PinDirCpy-> the required Pin Direction,[0]for Input,
												  [1]for output4
Output: Function Error State.[0] for No Error, [1] if Error Existed
*/
void TIMER0_INT(u8 Timer0Mode , u8 Timer0OVINTEnable , u8 Timer0OPCompINTEnable , u8 PreSckMode);

void TIMER0_ReadCounterValue(u8* Timer0CounterVal);

void TIMER0_SetCompValue(u8 Timer0CompareVal);

void TIMER0_SetCOUNTERValue(u8 TimerCOUNTERValue);

void TMR0_Set_TOV_Number(u8 u8Val);

void TIMR0_GetTOVValue(u8* Timer0OVVal);

extern void TIMR0_Get_Ticks_of_SWcounter (u32 *u8Val);

//ISR
extern void callback_TIMR0_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void));
extern void callback_OCR0_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void));




#endif /* TIMER0_INT_H_ */
