/*

 * Timer0_Prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: MANSI-PC
 */
#include "Timer0_int.h"
u8 TOV_Number ;
static void (*Ptr_To_OVFI)(void);
static void (*Ptr_To_OCMI)(void);

void TIMER0_INT(u8 Timer0Mode , u8 Timer0OVINTEnable , u8 Timer0OPCompINTEnable , u8 PreSckMode)
{
	/*Local Varibales*/

	/*Error State*/
	u8 u8ErrLoc = TIMER0_u8OK;

	if(Timer0Mode >= Timer0_ErrorMode)
	{
		u8ErrLoc = TIMER0_u8NOK ;
	}
	else if (Timer0OVINTEnable >=Timer0_OVFlowINTError )
	{
		u8ErrLoc = TIMER0_u8NOK ;
	}
	else if (Timer0OPCompINTEnable >=Timer0_OPCompINTError )
	{
		u8ErrLoc = TIMER0_u8NOK ;
	}
	else if(PreSckMode >=Timer0_ErroePresck )
	{
		u8ErrLoc = TIMER0_u8NOK ;
	}
	else
	{
		u8ErrLoc = TIMER0_u8OK;
		switch (Timer0Mode)
		{
		case Timer0_NormanlMode :
			TCCR0 = 0X00;
			break;
		case Timer0_CTCMode :
			Set_Bit(TCCR0, 3);
			break;
		default :

		}
		switch (Timer0OVINTEnable)
		{
		case Timer0_OVFlowINTEnable :
			Set_Bit(TIMSK, 0);
			break ;
		case Timer0_OVFlowINTDisable:
			Rst_Bit(TIMSK , 0);
			break ;
		default :
		}
		switch (Timer0OPCompINTEnable)
		{
		case Timer0_OPCompINTEnable:
			Set_Bit(TIMSK, 1);
			break;
		case Timer0_OPCompINTDisable:
			Rst_Bit(TIMSK , 1);
			break;
		default :
		}
		switch(PreSckMode)
		{
		case Timer0_NOPRENOCLK     :
			TCCR0  = (TCCR0 ||(0U));
			break;
		case Timer0_NOPRECLK       :
			TCCR0  = (TCCR0 ||(1U));
			break;
		case Timer0_NOPRECLK_8     :
			TCCR0  = (TCCR0 ||(2U));
			break;
		case Timer0_NOPRECLK_64    :
			TCCR0  = (TCCR0 ||(3U));
			break;
		case Timer0_NOPRECLK_256   :
			TCCR0  = (TCCR0 ||(4U));
			break;
		case Timer0_NOPRECLK_1024  :
			TCCR0  = (TCCR0 ||(5U));
			break;
		case Timer0_EXTCLK_FALLING :
			TCCR0  = (TCCR0 ||(6U));
			break;
		case Timer0_EXTCLK_RISING  :
			TCCR0  = (TCCR0 ||(7U));
			break;
		default:
		}
	}

}


void TIMER0_SetCompValue(u8 Timer0CompareVal)
{
	OCR0 = Timer0CompareVal ;
}

void void TIMER0_SetCOUNTERValue(u8 TimerCOUNTERValue)
{
	TCNT0 = TimerCOUNTERValue;
}

void TIMER0_ReadCounterValue(u8* Timer0CounterVal)
{
	*Timer0CounterVal = TCNT0;
}


extern void TMR0_Set_TOV_Number(u8 u8Val)
{
	TOV_Number = u8Val;

}
void TIMR0_GetTOVValue(u8* Timer0OVVal)
{
	*Timer0OVVal = TOV_Number ;
}

extern void TIMR0_Get_Ticks_of_SWcounter (u32 *u8Val)
{
	*u8Val =  256*TOV_Number + TCNT0;
}
//ISR
extern void callback_TIMR0_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void))
{
	Ptr_To_OVFI = Ptr_to_OVI_Function ;
}
extern void callback_OCR0_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void))
{
	Ptr_To_OCMI = Ptr_to_OCM_Function ;
}

ISR(__vector_10)
{
	(*Ptr_To_OCMI)();
}
ISR(__vector_11)
{
	TOV_Number++;
	(*Ptr_To_OVFI)();
}
