/*
 * ZeroX86.c
 *
 * Created: 9/1/2019 10:07:41 PM
 * Author : msams
 */ 

#include <avr/io.h>
#include "timer_port.h"
#include "ZeroX86.h"
//#include <util/delay.h>

volatile static task_ctrlblock_t * ZeroX86_internal_tasks_buffer[MAX_TASKS_NO];	//an array of pointers to task-control-blocks	//V0.0.1 the"+1"
volatile static uint16_t		   ZeroX86_internal_tcbs_buffer_top=MAX_TASKS_NO;	//V0.0.1>>a variable will point to the first TCB 
volatile static uint16_t           ZeroX86_internal_tcbs_buffer_counter=0;			//a variable will have the current number of TCBs  //V0.0.1
volatile static void ZeroX86_cbf(void);

ZeroX86_err_t ZeroX86_init(timer_elect_t timer_select,uint16_t systic_resolution)
{
	//PORTA=0xff;/*_delay_ms(250);*/PORTA=0x00;/*_delay_ms(250);*/
	//internal buffer initialization
	volatile uint8_t iter=0;
	while (iter< MAX_TASKS_NO)
	{
		ZeroX86_internal_tasks_buffer[iter++]=NULL;
	}
	systick_init(timer_select,systic_resolution,ZeroX86_cbf);	//TODO:check exec result.
	return ZEROX86_ER_NO;
}

static void ZeroX86_cbf(void)
{
	volatile uint8_t iter=0;
	while(iter < MAX_TASKS_NO)
	{
		if ((ZeroX86_internal_tasks_buffer[iter] != NULL) && (ZeroX86_internal_tasks_buffer[iter]->task_paused_obj == false) )	//V0.0.3>>if remaining time is 3 and sent to PAUSE state,it wont be scheduled and once it's sent back to RESUME state, the remaining is the same before being paused
		{
			ZeroX86_internal_tasks_buffer[iter]->task_rem_time_obj--;
			if(ZeroX86_internal_tasks_buffer[iter]->task_rem_time_obj <= 0)	//V0.0.2>>needs to reset the task state back to the ready state
			{
				ZeroX86_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_READY;	//V0.0.2
			}
		}
		iter++;
	} 
		//PORTD++;
}
//release time/ starting point	//starting time//V0.0.1
//arr of priorities				//will use a"top holder" plus a ptr_next within each tcb_structure	//V0.0.1
//sort before sys_begin
//resort or circular array of structures

//V0.0.1>>starting/release time
ZeroX86_err_t ZeroX86_add_task(task_ctrlblock_t* task_cb,uint16_t task_period,uint16_t starting_time,task_type_t task_type,uint8_t task_periority,void(*task_cbf)(void))
{
	cli();
	if ((task_cb != NULL)&&((task_type == ONESHOOT_TASK)||(task_type == PERIODIC_TASK))&&(task_cbf != NULL))
	{
		if (ZeroX86_internal_tasks_buffer[task_periority] == NULL)
		{
			ZeroX86_internal_tasks_buffer[task_periority]=task_cb;										//store the task control block object in the internal ZeroX86 buffer
			ZeroX86_internal_tasks_buffer[task_periority]->task_period_obj=task_period;					//store the task period	//TODO:revise the need of dividing on the resolution
			ZeroX86_internal_tasks_buffer[task_periority]->task_rem_time_obj=task_period+starting_time;	//set the remaining time to the task period as it's first added here //V0.0.1>>plus the starting time
			ZeroX86_internal_tasks_buffer[task_periority]->task_type_obj=task_type;						//store the task type
			ZeroX86_internal_tasks_buffer[task_periority]->tpf_cb_obj=task_cbf;							//assign the task function to the internal buffer task pointer
			ZeroX86_internal_tasks_buffer[task_periority]->task_priority_obj=task_periority;			//store the task priority
			ZeroX86_internal_tasks_buffer[task_periority]->task_state_obj=TASK_ST_READY;
			//do the tasks buffer linking //V0.0.1
			if (ZeroX86_internal_tcbs_buffer_top > task_periority)
			{
				ZeroX86_internal_tasks_buffer[task_periority]->ptcb_next_obj=ZeroX86_internal_tcbs_buffer_top;
				ZeroX86_internal_tcbs_buffer_top=task_periority;
			}
			else
			{
				uint8_t temp_search=task_periority-1;//temp_search var used to fined the higher-priority task to point to this new one
				while (ZeroX86_internal_tasks_buffer[temp_search]== NULL) {temp_search--;}	//found a higher prio-task
				ZeroX86_internal_tasks_buffer[task_periority]->ptcb_next_obj=ZeroX86_internal_tasks_buffer[temp_search]->ptcb_next_obj;	//save the task lower than the current pointed to by the found high-prio-task
				ZeroX86_internal_tasks_buffer[temp_search]->ptcb_next_obj=task_periority;	//make it point to this new lower-prio task
			}
			ZeroX86_internal_tcbs_buffer_counter++; //V0.0.1
			sei();
		}
		else
		{
			sei();
			return ZEROX86_ER_PRIO_NOT_AVAILABLE;
		}
	}
	else
	{
		sei();
		return ZEROX86_ER_INV_PARAMS;
	}
	return ZEROX86_ER_NO;
}

ZeroX86_err_t ZeroX86_rem_task(task_ctrlblock_t* task_cb)
{
	cli();
	if (task_cb != NULL)
	{
		if (ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			//do the tasks buffer linking //V0.0.1
			if (ZeroX86_internal_tcbs_buffer_top == ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_priority_obj)
			{
				ZeroX86_internal_tcbs_buffer_top=ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->ptcb_next_obj;
			}
			else
			{
				volatile uint8_t temp_search=ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_priority_obj-1; //temp_search var used to fined the higher-priority task that points to this being removed task
				while (ZeroX86_internal_tasks_buffer[temp_search]== NULL) {temp_search--;}	//found a higher prio-task
				ZeroX86_internal_tasks_buffer[temp_search]->ptcb_next_obj=ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->ptcb_next_obj;	//make the higher-prio task point to this new lower-prio task
			}
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]=NULL;								//store the task control block object in the internal ZeroX86 buffer
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_period_obj=0;				//store the task period	//TODO:revise the need of dividing on the resolution
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_rem_time_obj=0;				//set the remaining time to the task period as it's first added here
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_type_obj=0;					//store the task type
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->tpf_cb_obj=NULL;					//assign the task function to the internal buffer task pointer
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_priority_obj=0;				//store the task priority
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_state_obj=TASK_ST_WAITING;	//
			
			ZeroX86_internal_tcbs_buffer_counter--; //V0.0.1
			sei();
		}
		else
		{
			sei();
			return ZEROX86_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return ZEROX86_ER_INV_PARAMS;
	}
	return ZEROX86_ER_NO;
}
ZeroX86_err_t ZeroX86_pause_task(task_ctrlblock_t* task_cb)
{
	cli();
	if (task_cb != NULL)
	{
		if (ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_paused_obj=true;	//V0.0.3>> setting the paused var true so even the time had come, the task wont be executed
			sei();
		}
		else
		{
			sei();
			return ZEROX86_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return ZEROX86_ER_INV_PARAMS;
	}
	return ZEROX86_ER_NO;
}

ZeroX86_err_t ZeroX86_resume_task(task_ctrlblock_t* task_cb)
{
	cli();
	if (task_cb != NULL)
	{
		if (ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_paused_obj=false;	//V0.0.3>> setting the paused var false so the task is back to normal nd been scheduled
			sei();
		}
		else
		{
			sei();
			return ZEROX86_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return ZEROX86_ER_INV_PARAMS;
	}
	return ZEROX86_ER_NO;
}
//V0.0.4>> achieving the task delay functionality
ZeroX86_err_t ZeroX86_delay_task(task_ctrlblock_t* task_cb,uint16_t numb_of_ticks)
{
	cli();
	if (task_cb != NULL)
	{
		if (ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_rem_time_obj+=numb_of_ticks;	//V0.0.4>> achieving a task delay functionality by adding the required no of ticks delay to the remaining time variable
			sei();
		}
		else
		{
			sei();
			return ZEROX86_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return ZEROX86_ER_INV_PARAMS;
	}
	return ZEROX86_ER_NO;
}
//V0.0.4>> achieving the task delay functionality
ZeroX86_err_t ZeroX86_delay_hmsm_task(task_ctrlblock_t* task_cb,uint8_t hours,uint8_t minutes,uint8_t seconds,uint16_t milli)
{
	cli();
	if (task_cb != NULL)
	{
		if (ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj] != NULL)
		{
			ZeroX86_internal_tasks_buffer[task_cb->task_priority_obj]->task_rem_time_obj+=(((uint32_t)60*60*1000*hours)+((uint32_t)60*1000*minutes)+((uint32_t)1000*seconds)+milli);	//V0.0.4>> achieving a task delay functionality by adding the required delay val to the remaining time variable
			sei();
		}
		else
		{
			sei();
			return ZEROX86_ER_TASK_ALREADY_REMOVED;
		}
	}
	else
	{
		sei();
		return ZEROX86_ER_INV_PARAMS;
	}
	return ZEROX86_ER_NO;
}
ZeroX86_err_t ZeroX86_deinit(timer_elect_t timer_select)
{
	//internal buffer initialization
	volatile uint8_t iter=0;
	while (iter< MAX_TASKS_NO)
	{
		ZeroX86_internal_tasks_buffer[iter++]=NULL;
		//zero variables
	}
	systick_deinit(timer_select);	//TODO:check exec result.
	return ZEROX86_ER_NO;
}

void ZeroX86_dispatch(void)
{
	volatile uint8_t iter=ZeroX86_internal_tcbs_buffer_top;	//V0.0.1 >>setting iter to the first available and highest-prio task
	volatile uint8_t tasks_executed_counter=0;
	while( (iter <= MAX_TASKS_NO) && (tasks_executed_counter <= ZeroX86_internal_tcbs_buffer_counter) )	//V0.0.1 >>to be checked if < or <=
	{
		if (ZeroX86_internal_tasks_buffer[iter] != NULL)
		{
			if ( (ZeroX86_internal_tasks_buffer[iter]->task_rem_time_obj <= 0) && 
			     (ZeroX86_internal_tasks_buffer[iter]->task_state_obj == TASK_ST_READY) && 
				 (ZeroX86_internal_tasks_buffer[iter]->task_paused_obj == false) )	//V0.0.3>> the variable added to achieve the PAUSE/RESUME functionalities
			{
				if(ZeroX86_internal_tasks_buffer[iter]->task_type_obj == PERIODIC_TASK)
				{
					ZeroX86_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_RUNNING;
					(*ZeroX86_internal_tasks_buffer[iter]->tpf_cb_obj)();
					ZeroX86_internal_tasks_buffer[iter]->task_rem_time_obj+=ZeroX86_internal_tasks_buffer[iter]->task_period_obj;	//V0.0.4 >>changed to += not to corrupt the delay functionaity
					ZeroX86_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_WAITING;//V0.0.2 this is used to make the current running task waiting to achieve a goal that's
																					//V0.0.2 the highest priority task ready will run next at max since this is non-preemptive
																					//V0.0.2 by going back to check if any higher priority task is ready as mentioned in line230
				}
				else
				{	//one-shoot>>remove after finishing it
					ZeroX86_internal_tasks_buffer[iter]->task_state_obj=TASK_ST_RUNNING;
					(*ZeroX86_internal_tasks_buffer[iter]->tpf_cb_obj)();
					ZeroX86_rem_task(ZeroX86_internal_tasks_buffer[iter]);
					
				}
				tasks_executed_counter++;			//V0.0.1>>a task had just been executed successfully,increment.
				iter=ZeroX86_internal_tcbs_buffer_top;	//V0.0.1>>to make the highest priority task to run next TODO:think about it //V0.0.1 iter = top not 0
													//V0.0.1>>corrected a mistake>> resetting the iter to the first task at the two cases when it's one-shoot and periodic //V0.0.1
			}
			iter=ZeroX86_internal_tasks_buffer[iter]->ptcb_next_obj;	//V0.0.1 >>the iter to be incremented it needs to be pointing to a tcb not a NULL
		}
		else
		{	//V0.0.1>> if it's null, the iterator is incremented undependable on the pointer and not accessing a null
			iter++;
		}
	}
}
