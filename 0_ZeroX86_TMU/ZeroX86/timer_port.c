/*
 * timer_port.c
 *
 * Created: 10/8/2019 1:18:24 PM
 *  Author: Mahmoud saad
 */ 
#include "timer_port.h"
void(*timer_ctc_cbf)(void)=NULL;

port_err_t systick_init(timer_elect_t systick_timer,int16_t systick_resolution,void(*timer_interrupt_cbf)(void))
{
	#ifdef AVR_AT32
	#warning "NOTICE CURRENTLY I SUPPORT ONLY A SYSTICK OF 1mS"
	//notice currently we support only a systick of 1ms,
	//TODO:for later on development
	if (systick_timer == TIMER_0)
	{
		//notice, i dont depend on the resolution actually, currently i support 1ms only :(
		//notice,, unfortunately i'm not using the driver till now :(
		//TODO:LATER_DEVELOPMENT
		sei();
		#if (F_CPU == 1000000UL)
			OCR0 = 124;
			TCCR0 = 0x28;
			TCCR0 |= 0x02;
		#elif  (F_CPU == 2000000UL)
			OCR0 = 249;
			TCCR0 = 0x28;
			TCCR0 |= 0x02;
		#elif  (F_CPU == 3000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR0 = 46;
			TCCR0 = 0x28;
			TCCR0 |= 0x03;
		
		#elif  (F_CPU == 4000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR0 = 62;
			TCCR0 = 0x28;
			TCCR0 |= 0x03;
		#elif  (F_CPU == 8000000UL)
			OCR0 = 124;
			TCCR0 = 0x28;
			TCCR0 |= 0x03;
		#elif  (F_CPU == 10000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR0 = 155;
			TCCR0 = 0x28;
			TCCR0 |= 0x03;
		#elif  (F_CPU == 12000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR0 = 186;
			TCCR0 = 0x28;
			TCCR0 |= 0x03;
		#elif  (F_CPU == 16000000UL)
			OCR0 = 249;
			TCCR0 = 0x28;
			TCCR0 |= 0x03;
		#endif
		TIMSK|=(1<<OCIE0);	//enable interrupt at output
	}
	else if (systick_timer == TIMER_1)
	{
		//notice, i dont depend on the resolution actually, currently i support 1ms only :(
		//notice,, unfortunately i'm not using the driver till now :(
		//TODO:LATER_DEVELOPMENT
		sei();
		#if (F_CPU == 1000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x03;
			OCR1AL = 0xE7;
		#elif  (F_CPU == 2000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x07;
			OCR1AL = 0xCF;
		#elif  (F_CPU == 3000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x0B;
			OCR1AL = 0xB7;
		#elif  (F_CPU == 4000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x0F;
			OCR1AL = 0x9F;
		#elif  (F_CPU == 8000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x1F;
			OCR1AL = 0x3F;
		#elif  (F_CPU == 10000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x27;
			OCR1AL = 0x0F;
		#elif  (F_CPU == 12000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x2E;
			OCR1AL = 0xDF;
		#elif  (F_CPU == 16000000UL)
			TCCR1A = 0x80;
			TCCR1B = 0x09;
			OCR1AH = 0x3E;
			OCR1AL = 0x7F;
		#endif
		TIMSK|=(1<<OCIE1A);//enable interrupt at output compare
	}
	else if (systick_timer == TIMER_2)
	{
		//notice, i dont depend on the resolution actually, currently i support 1ms only :(
		//notice,, unfortunately i'm not using the driver till now :(
		//TODO:LATER_DEVELOPMENT
		sei();
		#if (F_CPU == 1000000UL)
			OCR2 = 124;
			TCCR2 = 0x28;
			TCCR2 |= 0x02;
		#elif  (F_CPU == 2000000UL)
			OCR2 = 249;
			TCCR2 = 0x28;
			TCCR2 |= 0x02;
		#elif  (F_CPU == 3000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR2 = 93;
			TCCR2 = 0x28;
			TCCR2 |= 0x03;
		#elif  (F_CPU == 4000000UL)
			OCR2 = 124;
			TCCR2 = 0x28;
			TCCR2 |= 0x03;
		#elif  (F_CPU == 8000000UL)
			OCR2 = 249;
			TCCR2 = 0x28;
			TCCR2 |= 0x03;
		#elif  (F_CPU == 10000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR2 = 155;
			TCCR2 = 0x28;
			TCCR2 |= 0x04;
		#elif  (F_CPU == 12000000UL)
			#warning "There is a difference in the actual Interrupt Time."
			OCR2 = 186;
			TCCR2 = 0x28;
			TCCR2 |= 0x04;
		#elif  (F_CPU == 16000000UL)
			OCR2 = 249;
			TCCR2 = 0x28;
			TCCR2 |= 0x04;
		#endif
		TIMSK|=(1<<OCIE2);	//enable interrupt at output compare
	}
	else
	{
		return PRT_INV_PARAMS;
	}
	timer_ctc_cbf=timer_interrupt_cbf;
	#endif	//AVR_AT32
	
	#ifdef PIC_PI18
	
	#endif	//PIC_PI18
	
	#ifdef ARM_TM4C
	
	#endif	//ARM_TM4C
	
	#ifdef ARM_ST32
	
	#endif	//ARM_ST32
	
	return PRT_NO_ER;
}

port_err_t systick_deinit(timer_elect_t systick_timer)
{
	#ifdef AVR_AT32
	if (systick_timer == TIMER_0)
	{
		TIMSK&=~(1<<OCIE0);	//disable timer interrupt 
		OCR0  = 0X00;
		TCCR0 = 0X00;
	}
	else if (systick_timer == TIMER_1)
	{
		TIMSK&=~(1<<OCIE1A);	//disable timer interrupt 
		TCCR1A = 0X00;
		TCCR1B = 0X00;
		OCR1AH = 0X00;
		OCR1AL = 0X00;
	}
	else if (systick_timer == TIMER_2)
	{
		TIMSK&=~(1<<OCIE2);	//disable timer interrupt 
		OCR2 = 0X00;
		TCCR2 = 0X00;
	}
	else
	{
		return PRT_INV_PARAMS;
	}
	
	timer_ctc_cbf=NULL;	//deleting the callback function task
	#endif	//AVR_AT32
	
	#ifdef PIC_PI18
	
	#endif	//PIC_PI18
	
	#ifdef ARM_TM4C
	
	#endif	//ARM_TM4C
	
	#ifdef ARM_ST32
	
	#endif	//ARM_ST32
	
	return PRT_NO_ER;
}
ISR(TIMER0_COMP_vect)
{
	if (timer_ctc_cbf != NULL)
	{
		(*timer_ctc_cbf)();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if (timer_ctc_cbf != NULL)
	{
		(*timer_ctc_cbf)();
	}
	
}
ISR(TIMER2_COMP_vect)
{
	if (timer_ctc_cbf != NULL)
	{
		(*timer_ctc_cbf)();
	}
	
}