/*
 * ZeroXPort.h
 *
 *  Date	: Nov 29, 2019
 *  Author  : MahmoudSaad.ZeroX-86
 *  Email   : Mahmoud.S.AbdElhares@gmail.com
 *  Github  : github.com/zerox-86
 *  LinkedIn: www.linkedin.com/in/mahmoudsaad96
 *  FaceBook: www.facebook.com/ZeroX86.MSA
 */
/*
 * timer_port.h
 *
 * Created: 10/8/2019 1:18:34 PM
 *  Author: Mahmoud
 */ 

#ifndef AVRPORT_H_
#define AVRPORT_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ZeroX86CFG.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef enum
{
	PRT_NO_ER,
	PRT_INV_PARAMS,
}port_err_t;

typedef enum
{
	TIMER_0=0x53,
	TIMER_1=0x4e,
	TIMER_2=0x45,
}timer_elect_t;

port_err_t systick_init(timer_elect_t systick_timer,int16_t systick_resolution,void(*timer_interrupt_cbf)(void));
port_err_t systick_deinit(timer_elect_t systick_timer);
#endif /* AVRPORT_H_ */