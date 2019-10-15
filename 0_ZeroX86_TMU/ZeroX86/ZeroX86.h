/*
 * ZeroX86.h
 *
 * Created: 10/8/2019 1:05:33 PM
 *  Author: Mahmoud saad
 */ 


#ifndef ZEROX86_H_
#define ZEROX86_H_

#include "timer_port.h"
#include <stdint.h>
#include "ZeroX86_cfg.h"

#define MAX_TASKS_NO 25
#define MEANINGLESS_VAL 5	//it's used as the resolution but it's not implemented yet :(

typedef enum
{
	PERIODIC_TASK=0,			//0
	ONESHOOT_TASK,				//1
}task_type_t;

typedef enum
{
	TMU_ER_NO,
	TMU_ER_INV_PARAMS,
	TMU_ER_PRIO_NOT_AVAILABLE,
	TMU_ER_TASK_ALREADY_REMOVED,
}tmu_err_t;
typedef enum
{
	TASK_ST_RUNNING,
	TASK_ST_READY,
	TASK_ST_WAITING,	
}task_stat_t;

typedef struct task_ctrlblock
{
	uint16_t	task_period_obj;	  //the period needed for every task i.e task x needs to be executed ever 10systicks or 25systicks...etc
	int16_t		task_rem_time_obj;	  //internal/non-user modified variable used for scheduling
	void		(*tpf_cb_obj)(void);  //task pointer to function will be called
	task_type_t task_type_obj;		  //whether the task works forever or it's a one-time task
	uint8_t		task_priority_obj;	  //defines the task priority, the lower the priority value,the higher the task priority
	task_stat_t task_state_obj;		  //defines the task state i.e, task currently running, task currently waiting
	struct task_ctrlblock* ptcb_next_obj; //a pointer to (the next/the lower in priority) Task //V0.0.1
	//uint16_t	task_starting_time_obj;	  //a value after-which the scheduler begins taking the task in calculations/begins scheduling the task //V0.0.1
										  //>>i think it's not needed to be stored since it's used just once at the beginning so y not just add the wanted val
										  //to the remaining_time variable and that's it.	//V0.0.1
}task_ctrlblock_t; 

task_ctrlblock_t tcb_test;
tmu_err_t zerox86_tmu_init(timer_elect_t* timer_select,uint16_t systic_resolution);
tmu_err_t zerox86_tmu_add_task(task_ctrlblock_t* task_cb,uint16_t task_period,task_type_t task_type,uint8_t task_periority,void(*task_cbf)(void));
tmu_err_t zerox86_tmu_rem_task(task_ctrlblock_t* task_cb);
tmu_err_t zerox86_tmu_pause_task(task_ctrlblock_t* task_cb);
tmu_err_t zerox86_tmu_resume_task(task_ctrlblock_t* task_cb);
tmu_err_t zerox86_tmu_deinit(timer_elect_t timer_select);
void	  zerox86_tmu_dispatch(void);
#endif /* ZEROX86_H_ */