/*
 * avr_timer.h
 *
 * Created: 10/8/2019 6:46:31 AM
 *  Author: Mahmo
 */ 

#if 0
#ifndef AVR_TIMER_H_
#define AVR_TIMER_H_
#include <avr/io.h>
#include <stdint.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#define CTC_MODE 2

typedef enum
{
	TMR_NO_ER,
	TMR_INV_PARAMS,
}timer_err_t;

typedef enum
{
	OFF=0,
	NO_PRESCALER=1,
	PRESCALER_8=2,
	PRESCALER_64=3,
	PRESCALER_256=4,
	PRESCALER_1024=5,
	EXT_FALLING_EDGE=6,
	EXT_RISING_EDGE=7,
}prescaller_select_t;

typedef enum
{
	TIMER_0=0x53,
	TIMER_1=0x4e,
	TIMER_2=0x45,
}timer_bases_t;

typedef struct
{
	timer_bases_t	    timer_base_obj;
	uint16_t			timer_ocr_val_obj;
	prescaller_select_t timer_prescaller_obj;
}timer_object;

//NOTES_NOTES_NOTES
//INTERRUPTABLE_AT_OC
//NO EFFECT ON THE OC PIN
//ALWAYS CTC MODE
timer_err_t init_timer(timer_object *given_obj);
timer_err_t read_timer_val(timer_object *given_obj,uint16_t *return_res);
timer_err_t update_comp_timer(timer_object *given_obj,uint16_t *val);
timer_err_t deinit_timer(timer_object *given_obj);

#endif /* AVR_TIMER_H_ */
#endif //0