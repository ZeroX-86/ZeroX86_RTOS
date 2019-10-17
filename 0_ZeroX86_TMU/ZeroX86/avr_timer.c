/*
 * avr_timer_cfg.c
 *
 * Created: 10/8/2019 6:46:06 AM
 *  Author: Mahmoud
 */ 
#if 0
#include "avr_timer.h"

#define WGMn1			2	//for timer 0 and 2
#define WGMn0			6	//for timer 0 and 2
#define COMn			4	//for timer 0 and 2
#define CTC_MODE		2	//for timer 1
#define WGM10			0	//for timer 1
#define WGM12			3	//for timer 1
#define TCCR1A_OFFSET	1	//for timer 1
#define T1_CTC_MODE		1	//for timer 1

//NOTES_NOTES_NOTES		init_timer
//INTERRUPTABLE_AT_OC
//NO EFFECT ON THE OC PIN
//ALWAYS CTC MODE
timer_err_t init_timer(timer_object *given_obj)
{
	if (given_obj != NULL)
	{
		//test data for safety
		if((given_obj->timer_base_obj == TIMER_0)||(given_obj->timer_base_obj == TIMER_2))
		{
			*(volatile uint8_t*)(given_obj->timer_base_obj)|=( (( CTC_MODE & 0x02)<<WGMn1) |((( CTC_MODE & 0x01)<<WGMn0)) );     
			*(volatile uint8_t*)(given_obj->timer_base_obj)|= given_obj->timer_prescaller_obj;
		} 
		else if (given_obj->timer_base_obj == TIMER_1)
		{
			*(volatile uint8_t*)(given_obj->timer_base_obj)|= T1_CTC_MODE<<WGM12;
			*(volatile uint8_t*)(given_obj->timer_base_obj)|= given_obj->timer_prescaller_obj;
		} 
		else
		{
			return TMR_INV_PARAMS;
		}
		
		if (given_obj->timer_base_obj == TIMER_0)
		{
			TCNT0=0;
			OCR0=(uint8_t)given_obj->timer_ocr_val_obj;
			TIMSK|=(1<<OCIE0);	//enable interrupt at output 
		} 
		else if (given_obj->timer_base_obj == TIMER_2)
		{
			TCNT2=0;
			OCR2=(uint8_t)given_obj->timer_ocr_val_obj;
	        TIMSK|=(1<<OCIE2);	//enable interrupt at output compare			
		}
		else if(given_obj->timer_base_obj == TIMER_1)
		 {
			 //handle later for timer 1
			 TCNT1=0;
			 OCR1A=(uint16_t)given_obj->timer_ocr_val_obj;
			 TIMSK|=(1<<OCIE1A);
		 }
		 else
		 {
			 return TMR_INV_PARAMS;
		 }
	return TMR_NO_ER;	
	}
	return TMR_INV_PARAMS;
}

timer_err_t read_timer_val(timer_object *given_obj,uint16_t *val)
{
	if ((given_obj != NULL) && (val!=NULL))
	{
		if(given_obj->timer_base_obj == TIMER_0)
		{
			*val=TCNT0 + ((TIFR&(1<<OCF0))*(given_obj->timer_ocr_val_obj));
		}
		else if(given_obj->timer_base_obj == TIMER_1)
		{
			*val=TCNT1 + ((TIFR&(1<<OCF1A))*(given_obj->timer_ocr_val_obj));
		}
		else if(given_obj->timer_base_obj == TIMER_2)
		{
			*val=TCNT2 + ((TIFR&(1<<OCF2))*(given_obj->timer_ocr_val_obj));
		}
		else
		{
			return TMR_INV_PARAMS;
		}
		return TMR_NO_ER;
	}
	return TMR_INV_PARAMS;
}


timer_err_t update_comp_timer(timer_object *given_obj,uint16_t *val)
{
	if ((given_obj != NULL) && (val!=NULL))
	{
		given_obj->timer_ocr_val_obj=*val;
		if (given_obj->timer_base_obj == TIMER_0)
		{
			OCR0=(uint8_t)given_obj->timer_ocr_val_obj;
		}
		else if(given_obj->timer_base_obj == TIMER_2)
		{
			OCR2=(uint8_t)given_obj->timer_ocr_val_obj;
		}
		else if(given_obj->timer_base_obj == TIMER_1)
		{
			OCR1A=(uint16_t)given_obj->timer_ocr_val_obj;
		}
		else
		{
			return TMR_INV_PARAMS;
		}
	return TMR_NO_ER;
		
	}
		return TMR_INV_PARAMS;
}
timer_err_t deinit_timer(timer_object *given_obj)
{
	if(given_obj != NULL)
	{
		*(volatile uint8_t*)(given_obj->timer_base_obj)=0;	//stopping the hw module
		given_obj->timer_prescaller_obj=0;
		given_obj->timer_ocr_val_obj=0;
		given_obj->timer_base_obj=0;
		return TMR_NO_ER;
	}
	return TMR_INV_PARAMS;
}
#endif //0