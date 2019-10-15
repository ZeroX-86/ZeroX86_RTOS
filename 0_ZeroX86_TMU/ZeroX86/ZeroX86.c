/*
 * ZeroX86.c
 *
 * Created: 9/1/2019 10:07:41 PM
 * Author : msams
 */ 

#include <avr/io.h>
#include "timer_port.h"
#include "ZeroX86.h"

static task_ctrlblock_t * tmu_internal_tasks_buffer[MAX_TASKS_NO];

static void tmu_cbf(void);

tmu_err_t zerox86_tmu_init(timer_elect_t timer_select,uint16_t systic_resolution)
{
	//internal buffer initialization
	uint8_t iter=0;
	while (iter< MAX_TASKS_NO)
	{
		tmu_internal_tasks_buffer[iter]=NULL;
	}
	systick_init(timer_select,systic_resolution,tmu_cbf);	//TODO:check exec result.
}

static void tmu_cbf(void)
{
	uint8_t iter=0;
	while(iter < MAX_TASKS_NO)
	{
		if (tmu_internal_tasks_buffer[iter] != NULL)
		{
			tmu_internal_tasks_buffer[iter]->task_rem_time_obj--;
		}
	}
}
//release time/ starting point
//arr of priorities
//sort before sys_begin
//resort or circular array of structures

tmu_err_t zerox86_tmu_add_task(task_ctrlblock_t* task_cb,uint16_t task_period,task_type_t task_type,uint8_t task_periority,void(*task_cbf)(void))
{
	cli();
	if ((task_cb != NULL)&&((task_type == ONESHOOT_TASK)||(task_type == PERIODIC_TASK))&&(task_cbf != NULL))
	{
		if (tmu_internal_tasks_buffer[task_periority] == NULL)
		{
			tmu_internal_tasks_buffer[task_periority]=task_cb;								//store the task control block object in the internal tmu buffer
			tmu_internal_tasks_buffer[task_periority]->task_period_obj=task_period;			//store the task period	//TODO:revise the need of dividing on the resolution
			tmu_internal_tasks_buffer[task_periority]->task_rem_time_obj=task_period;		//set the remaining time to the task period as it's first added here
			tmu_internal_tasks_buffer[task_periority]->task_type_obj=task_type;				//store the task type
			tmu_internal_tasks_buffer[task_periority]->tpf_cb_obj=task_cbf;					//assign the task function to the internal buffer task pointer
			tmu_internal_tasks_buffer[task_periority]->task_priority_obj=task_periority;	//store the task priority
			tmu_internal_tasks_buffer[task_periority]->task_state_obj=TASK_ST_READY;
			sei();
		}
		else
		{
			sei();
			return TMU_ER_PRIO_NOT_AVAILABLE;
		}
	}
	else
	{
		sei();
		return TMU_ER_INV_PARAMS;
	}
	return TMU_ER_NO;
}

tmu_err_t zerox86_tmu_rem_task(task_ctrlblock_t* task_cb)
{
	cli();
	if (task_cb != NULL)
	{
		if (tmu_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]=NULL;								//store the task control block object in the internal tmu buffer
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_period_obj=0;				//store the task period	//TODO:revise the need of dividing on the resolution
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_rem_time_obj=0;				//set the remaining time to the task period as it's first added here
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_type_obj=0;					//store the task type
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->tpf_cb_obj=NULL;					//assign the task function to the internal buffer task pointer
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_priority_obj=0;				//store the task priority
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_state_obj=TASK_ST_WAITING;	//
			sei();
		}
		else
		{
			sei();
			return TMU_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return TMU_ER_INV_PARAMS;
	}
	return TMU_ER_NO;
}

tmu_err_t zerox86_tmu_pause_task(task_ctrlblock_t* task_cb)
{
	cli();
	if (task_cb != NULL)
	{
		if (tmu_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_state_obj=TASK_ST_WAITING;	//set the task state to the waiting state
			sei();
		}
		else
		{
			sei();
			return TMU_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return TMU_ER_INV_PARAMS;
	}
	return TMU_ER_NO;
}

tmu_err_t zerox86_tmu_resume_task(task_ctrlblock_t* task_cb)
{
	cli();
	if (task_cb != NULL)
	{
		if (tmu_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			tmu_internal_tasks_buffer[task_cb->task_priority_obj]->task_state_obj=TASK_ST_READY;	//set the task state back to the ready state
			sei();
		}
		else
		{
			sei();
			return TMU_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return TMU_ER_INV_PARAMS;
	}
	return TMU_ER_NO;
}

tmu_err_t zerox86_tmu_deinit(timer_elect_t timer_select)
{
	//internal buffer initialization
	uint8_t iter=0;
	while (iter< MAX_TASKS_NO)
	{
		tmu_internal_tasks_buffer[iter]=NULL;
	}
	systick_deinit(timer_select);	//TODO:check exec result.
}

void zerox86_tmu_dispatch(void)
{
	uint8_t iter=0;
	while (iter < MAX_TASKS_NO)
	{
		if (tmu_internal_tasks_buffer[iter] != NULL)
		{
			if ( (tmu_internal_tasks_buffer[iter]->task_rem_time_obj <= 0) && (tmu_internal_tasks_buffer[iter]->task_state_obj == TASK_ST_READY) )
			{
				if(tmu_internal_tasks_buffer[iter]->task_type_obj == PERIODIC_TASK)
				{
					tmu_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_RUNNING;
					(*tmu_internal_tasks_buffer[iter]->tpf_cb_obj)();
					tmu_internal_tasks_buffer[iter]->task_rem_time_obj=tmu_internal_tasks_buffer[iter]->task_period_obj;
					tmu_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_WAITING;
					iter=0;	//to make the highest priority task to run next TODO:think about it
				}
				else
				{	//one-shoot>>remove after finishing it
					tmu_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_RUNNING;
					(*tmu_internal_tasks_buffer[iter]->tpf_cb_obj)();
					zerox86_tmu_rem_task(tmu_internal_tasks_buffer[iter]);
					
				}
			}
		}
		iter++;
	}
}
/*
typedef enum ret_t{
	no_error,
	error_same_prio,
	
}ret_ms;
/*
typedef struct  
{
	task_prio;
	ptr_stak;
}tsk_tcb;
/*
tasks_t sys_arr[max]; 
*/
//init tmu timer @ 1 ms

//tmu add task(task add, priority,timer/precedence 

//tmu rem task(task add)

//tmu pause task(priority,timer/precedence?)

//tmu resume task(priority,timer/precedence?)

//de-init tmu();

/*
no sound!!! :(
*/
/*
int ZeroX86Init(void)
{
	/* Replace with your application code */
	while (1)
	{
		zerox86_tmu_dispatch();
	}
}

int main(void)
{
    /* Replace with your application code */
  /**//*  while (1) 
  /*  {
		/*
		dispatch();
		_sleep();*/
 /*   }
}
/*
dispatch()
{
	for(int i=0;i< ;i++)
	{
		if( ( tasks_arr[i] != NULL) && tasks_arr[i]->state  tasks_arr[i] % )
			tasks_arr[i]();
			i=0;
	}
			
}

sys_tick =1ms
isr
{
	counter++;
	
}
alooooo?
?
ana sam3*/
