/*******************************************************************************
* Title                 :   Uart Application
* Filename              :   uart_config.c
* Author                :   Jacob Beningo
* Origin Date           :   08/19/2015
* Version               :   1.0.0
* Compiler              :   Keil uVision v5.14.0
* Target                :   STM32L0R53
* Notes                 :   None
*
* THIS SOFTWARE IS PROVIDED BY BENINGO ENGINEERING "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL BENINGO ENGINEERING OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/
/****************************************************************************
* Doxygen C Template
* Copyright (c) 2013 - Jacob Beningo - All Rights Reserved
*
* Feel free to use this Doxygen Code Template at your own risk for your own
* purposes.  The latest license and updates for this Doxygen C template can be  
* found at www.beningo.com or by contacting Jacob at jacob@beningo.com.
*
* For updates, free software, training and to stay up to date on the latest 
* embedded software techniques sign-up for Jacobs newsletter at 
* http://www.beningo.com/814-2/
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Template. 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author         Description 
*  08/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
/** @file uart_app.c
 *  @brief This is the source file for the uart application
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>				/* For portable types */
#include "uart_app.h"			/* For gse definitions */		
#include "cbuf.h"         /* For a public domain circular buffer */
#include "uart.h"					/* For uart driver definitions */
#include <stm32l053xx.h>  /* For hardware definitions */
#include <stdarg.h>				/* For variable parameters */
#include <stdio.h>				/* For sprintf */
#include <string.h>				/* For strlen */
#include <assert.h>				/* For assertions */

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
/**
 * Stores a single character read from the receive uart peripheral
 */
static uint8_t volatile RxChar = 0;

/**
 * Stores a single character that will transmitted over the uart.
 */
static uint8_t volatile TxChar = 0;

/**
 * Defines a variable that is used as a circular buffer for incoming uart data
 */
static myQ volatile RxBuffer;

/**
 * Defines a variable that is used as a circular buffer for outgoing uart data
 */
static myQ volatile TxBuffer;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Function : Uart_AppInit()
*//** 
* \b Description:
*
*  This function is used to initialize the uart application buffers
*
* @return 		void
*
* @see Uart_AppInit
*
* \b Example Example:
* @code
*    Uart_AppInit();
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  08/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Uart_AppInit(void)
{
    CBUF_Init(RxBuffer);
    CBUF_Init(TxBuffer);
}

/******************************************************************************
* Function : Uart_AppTx()
*//** 
* \b Description:
*
*  This function is used to transmit more than one character at a time.
*
* @param			Buffer contains a series of characters to transmit.
* @param      Size is the number of character in Buffer.
*
* @return 		void
*
* @see Uart_AppInit
*
* \b Example Example:
* @code
*    Uart_AppTx(Buffer, 14);
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  08/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Uart_AppTx(uint8_t * Buffer, uint8_t Size)
{
	 uint8_t TxChar = 0;
	 uint8_t Index = 0;
	
   for(Index = 0; Index < Size; Index++)
	 {
		 CBUF_Push(TxBuffer, Buffer[Index]);
	 }
	 
   TxChar = CBUF_Pop(TxBuffer);

	 Uart_PutChar(UART1, TxChar);  
}


/******************************************************************************
* Function : Uart_IsrTx()
*//**
* \b  Description:
*
*  This function fires when byte data is transmitted on the UART.  The interrupt
*  verifies that the data is for the GSE uart, retrieves the data byte and
*  transmits it from the circular buffer.
*
* @see Uart_AppTx
* @see Uart_AppInit
*
* \b Example:
* @code
*    None
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description 		<br>
*  07/07/15       1.1.0            JWB      Function Implemented.	<br>
*
*******************************************************************************/
void USART1_IRQHandler (void) 
{
    uint8_t TxChar;

		/* Clear the PA3 signal */
	  GPIOA->BSRR |= (1UL << 6);	
	
    USART1->ICR |= USART_ICR_TCCF;

    /* If the buffer isn't empty then transmit the next byte */
    if(CBUF_IsEmpty(TxBuffer) == 0)
    {
    	TxChar = CBUF_Pop(TxBuffer);

	    Uart_PutChar(UART1, TxChar);   	
    }
		
		/* Set the PA3 signal */
	  GPIOA->BSRR |= (1UL << 6) << 16;	
}

/******************************************************************************
* Function : Gse_printf()
*//**
* \b  Description:
*
*  This function is used to format a printf string into a buffer that can be
*  added to the circular buffer and transmitted out the Gse port.
*
* @see Gse_Init
* @see Gse_Process
* @see Gse_printf
* @see Gse_IsrRx
* @see Gse_IsrTx
*
* \b Example:
* @code
*    Gse_printf("There are %d commands in the queue\n\r", CommandsQueued);
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description 		<br>
*  07/07/15       1.1.0            JWB      Function Implemented.	<br>
*
*******************************************************************************/
void Uart_printf(UartChannel_t Channel, const char *format, ...)
{
	char Buffer[50];
  va_list args;
  uint8_t length;
  uint8_t i = 0;
  uint8_t TxChar;
	
	va_start(args, format);
	vsprintf(Buffer, format, args);
	va_end(args);

  length = strlen(Buffer);

	
/* Below is example code for using a circular buffer with interrupts */	
/* Don't forget to turn interrupts on in uart.c */	
#if 1
  for(i = 0; i < length; i++)
  {
     CBUF_Push(TxBuffer, Buffer[i]);
  }

  TxChar = CBUF_Pop(TxBuffer);

  Uart_PutChar(Channel, TxChar);
#endif	
	
/* Below code is an example of a blocking printf statement */	
#if 0	
	for(i = 0; i < length; i++)
	{
	   Uart_PutChar(UART1, Buffer[i]);	
		
		 while((USART1->ISR & USART_ISR_TC) != USART_ISR_TC);
	}
#endif	
	
}


void __aeabi_assert(const char *expr, const char *file, int line)
{
	Uart_printf(UART1, "Assertion failed in %s at line %d\n", file, line);

	for(;;);
}

/*************** END OF FUNCTIONS ***************************************************************************/
