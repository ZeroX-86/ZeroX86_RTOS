/*
 * timer_port.h
 *
 * Created: 10/8/2019 1:18:34 PM
 *  Author: Mahmoud
 */ 


#ifndef TIMER_PORT_H_
#define TIMER_PORT_H_
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ZeroX86_cfg.h"

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


#endif /* TIMER_PORT_H_ */