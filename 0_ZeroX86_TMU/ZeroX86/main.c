/*
 * main.c
 *
 * Created: 10/16/2019 2:41:07 AM
 *  Author: Mahmo
 */ 
#include "ZeroX86.h"
#include <avr/io.h>
#include <util/delay.h>

void task_1(void);
void task_2(void);
void task_3(void);
void task_4(void);

int main(void)
{
	DDRA=DDRB=DDRC=DDRD=0xff;
	zerox86_tmu_init(TIMER_1,2);
	task_ctrlblock_t tcb_task1,tcb_task2,tcb_task3,tcb_task4;
	zerox86_tmu_add_task(&tcb_task1,5,0,PERIODIC_TASK,1,task_1);
	zerox86_tmu_add_task(&tcb_task2,10,0,PERIODIC_TASK,2,task_2);
	zerox86_tmu_add_task(&tcb_task3,15,0,PERIODIC_TASK,3,task_3);
	//zerox86_tmu_add_task(&tcb_task4,8,0,PERIODIC_TASK,4,task_4);
	while(1)
	{/*
		PORTD=0xff;
		_delay_ms(100);
		PORTD=0x00;
		_delay_ms(100);*/
		zerox86_tmu_dispatch();
		//goto sleep mode to be waked up by the INTERRUPT
	}
	return 0;
}


void task_1(void)
{
	PORTA=0xff;
	_delay_ms(5);
	PORTA=0x00;
	_delay_ms(5);
}
void task_2(void)
{
	PORTB=0xff;
	_delay_ms(5);
	PORTB=0x00;
	_delay_ms(5);
	
}
void task_3(void)
{
	PORTC=0xff;
	_delay_ms(5);
	PORTC=0x00;
	_delay_ms(5);
	
}
void task_4(void)
{
	PORTD=0xff;
	_delay_ms(5);
	PORTD=0x00;
	_delay_ms(5);
	
}