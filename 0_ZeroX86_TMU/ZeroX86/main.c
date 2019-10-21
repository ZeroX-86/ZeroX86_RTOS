/*
 * main.c
 *
 * Created: 10/16/2019 2:41:07 AM
 *  Author: Mahmo
 */ 
#include "ZeroX86.h"
#include <avr/io.h>
//#include <util/delay.h>

void task_1(void);
void task_2(void);
void task_3(void);
void task_4(void);
task_ctrlblock_t tcb_task1,tcb_task2,tcb_task3,tcb_task4;
int main(void)
{
	DDRA=DDRB=DDRC=DDRD=0xff;
	ZeroX86_init(TIMER_1,MEANINGLESS_VAL);
	ZeroX86_add_task(&tcb_task1,0,0,PERIODIC_TASK,1,task_1);
	//ZeroX86_add_task(&tcb_task2,10,0,PERIODIC_TASK,2,task_2);
	//ZeroX86_add_task(&tcb_task3,15,0,PERIODIC_TASK,3,task_3);
	//zerox86_add_task(&tcb_task4,8,0,PERIODIC_TASK,4,task_4);
	while(1)
	{/*
		PORTD=0xff;
		_delay_ms(100);
		PORTD=0x00;
		_delay_ms(100);*/
		ZeroX86_dispatch();
		//goto sleep mode to be waked up by the INTERRUPT
	}
	return 0;
}


void task_1(void)
{
	PORTA++;
	ZeroX86_delay_task(&tcb_task1,1);
	//_delay_ms(5);
	//PORTA=0x00;
	//_delay_ms(5);
}
void task_2(void)
{
	PORTB++;
	ZeroX86_delay_hmsm_task(&tcb_task2,0,0,1,100);
	/*
	_delay_ms(5);
	PORTB=0x00;
	_delay_ms(5);*/
	
}
void task_3(void)
{
	PORTC++;/*
	_delay_ms(5);
	PORTC=0x00;
	_delay_ms(5);*/
	
}
void task_4(void)
{
	PORTD=0xff;
	//_delay_ms(5);
	PORTD=0x00;
	//_delay_ms(5);
	
}