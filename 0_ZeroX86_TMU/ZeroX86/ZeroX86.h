/*
 * ZeroX86.h
 *
 * Created: 10/8/2019 1:05:33 PM
 *  Author: Mahmoud saad
 */ 


#ifndef ZEROX86_H_
#define ZEROX86_H_

#include <stdint.h>
#include <stdbool.h>
#include "timer_port.h"
#include "ZeroX86_cfg.h"


typedef enum
{
	PERIODIC_TASK=0,			//0
	ONESHOOT_TASK,				//1
}task_type_t;

typedef enum
{
	ZEROX86_ER_NO,
	ZEROX86_ER_INV_PARAMS,
	ZEROX86_ER_PRIO_NOT_AVAILABLE,
	ZEROX86_ER_TASK_ALREADY_REMOVED,
}ZeroX86_err_t;
typedef enum
{
	TASK_ST_RUNNING,
	TASK_ST_READY,
	TASK_ST_WAITING,	
}task_stat_t;

typedef struct 
{
	uint16_t	task_period_obj;	  //the period needed for every task i.e task x needs to be executed ever 10systicks or 25systicks...etc
	int32_t		task_rem_time_obj;	  //internal/non-user modified variable used for scheduling		//V0.0.4>>extended to 32-bit var to handle large values and delays
	void		(*tpf_cb_obj)(void);  //task pointer to function will be called
	task_type_t task_type_obj;		  //whether the task works forever or it's a one-time task
	uint8_t		task_priority_obj;	  //defines the task priority, the lower the priority value,the higher the task priority
	task_stat_t task_state_obj;		  //defines the task state i.e, task currently running, task currently waiting
	uint16_t    ptcb_next_obj;		  //a pointer to (the next/the lower in priority) Task //V0.0.1
	bool	    task_paused_obj;	  //V0.0.3>> added to achieve the Pause/Resume functionalities 
	//uint16_t	task_starting_time_obj;	  //a value after-which the scheduler begins taking the task in calculations/begins scheduling the task //V0.0.1
										  //>>i think it's not needed to be stored since it's used just once at the beginning so y not just add the wanted val
										  //to the remaining_time variable and that's it.	//V0.0.1
}task_ctrlblock_t; 

ZeroX86_err_t ZeroX86_init(timer_elect_t timer_select,uint16_t systic_resolution);
ZeroX86_err_t ZeroX86_add_task(task_ctrlblock_t* task_cb,uint16_t task_period,uint16_t starting_time,task_type_t task_type,uint8_t task_periority,void(*task_cbf)(void));
ZeroX86_err_t ZeroX86_rem_task(task_ctrlblock_t* task_cb);
ZeroX86_err_t ZeroX86_pause_task(task_ctrlblock_t* task_cb);
ZeroX86_err_t ZeroX86_resume_task(task_ctrlblock_t* task_cb);
//V0.0.4>> achieving the task delay functionality
ZeroX86_err_t ZeroX86_delay_task(task_ctrlblock_t* task_cb,uint16_t numb_of_ticks);
ZeroX86_err_t ZeroX86_delay_hmsm_task(task_ctrlblock_t* task_cb,uint8_t hours,uint8_t minutes,uint8_t seconds,uint16_t milli);
ZeroX86_err_t ZeroX86_deinit(timer_elect_t timer_select);
void		  ZeroX86_dispatch(void);
#endif /* ZEROX86_H_ */