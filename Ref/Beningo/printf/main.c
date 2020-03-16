#include "stm32l053xx.h"
#include <stdint.h>
#include "SysTick.h"
#include "tsk_cfg.h"			// For task config
#include "button.h"
#include "board_led.h"
#include "uart_config.h"
#include "uart.h"
#include "uart_app.h"
#include "wdt.h"
#include <stdio.h>

int main(void)
{
	
  static uint32_t tick = 0;						// System tick
	static TaskType *Task_ptr;                 		// Task pointer
	static uint8_t TaskIndex = 0;					// Task index
	const uint8_t NumTasks = Tsk_GetNumTasks();		// Number of tasks
  const UartConfig_t * const UartConfig = Uart_ConfigGet();
	const WdtConfig_t * const WdtConfig = Wdt_ConfigGet();
	
	/****************************************************************************
	* System Initialization
	*****************************************************************************/
	Task_ptr = Tsk_GetConfig();    // Get a pointer to the task configuration

	SysTick_Init();
	(void) LED_Initialize();
	Button_Init();
  Uart_Init(UartConfig);
	Uart_AppInit();
	
	/* Initialize GPIO for testing purposes */
	GPIOA->MODER   &= ~((3UL << 2*6));
  GPIOA->MODER   |=  ((1UL << 2*6));
  GPIOA->OTYPER  &= ~((1UL <<   6));
  GPIOA->OSPEEDR &= ~((3UL << 2*6));
  GPIOA->OSPEEDR |=  ((1UL << 2*6));
  GPIOA->PUPDR   &= ~((3UL << 2*6));
	
	GPIOA->BSRR |= (1UL << 6) << 16;	
	
	Wdt_Init(WdtConfig);
	Wdt_Enable();
	
	char a[] = "Hello";
char b[] = "     ";
 
// Find length of string a
char* ptr = a;

while(*ptr)
  ptr++;

printf("Length=%d\n", ptr - a);
  
// Copy a to b
char* from = a;
char* to   = b;
  
while (*to++ = *from++)
  ;

printf("%s %s\n", a, b);

	
	// The main while loop.  This while loop will run the program forever
	while(1)
	{
		tick = SysTick_Get();		// Get current system tick

		// Loop through all tasks.  First, run all continuous tasks.  Then,
		// if the number of ticks since the last time the task was run is
		// greater than or equal to the task interval, execute the task.
		for(TaskIndex = 0; TaskIndex < NumTasks; TaskIndex++)
		{
			if(Task_ptr[TaskIndex].Interval == 0)
			{
				// Run continuous tasks.
				(*Task_ptr[TaskIndex].Func)();
			}
			else if((tick - Task_ptr[TaskIndex].LastTick) >= Task_ptr[TaskIndex].Interval)
			{
				(*Task_ptr[TaskIndex].Func)();         // Execute Task

				Task_ptr[TaskIndex].LastTick = tick;  // Save last tick the task was ran.
			}
		}// end for
	}// end while(1)
}
