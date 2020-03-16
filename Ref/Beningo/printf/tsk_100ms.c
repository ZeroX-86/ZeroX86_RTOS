
#include "tsk_100ms.h"			// For this modules definitions
#include <stdint.h>
#include "board_led.h"
#include "button.h"
#include "uart.h"
#include "uart_app.h"
#include "assert.h"
#include "wdt.h"

#define LED_GREEN			1

void Tsk_100ms(void)
{
	static uint32_t State = 0;
	Button_State_t ButtonState = Button_StateGet(BUTTON_USER);

	Wdt_Clear();
	assert(State < 2);
	
	if((State==0) && (ButtonState == BUTTON_STATE_NOT_PRESSED))
	{
			LED_Off(LED_GREEN);
			State = 1;
	}
	else
	{
			LED_On(LED_GREEN);
			State = 0;
	}
	
	//Uart_AppTx(Buffer, 14);
	Uart_printf(UART1, "The system state is %d\n\r", State);
}

/*** End of File **************************************************************/

