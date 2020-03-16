/*******************************************************************************
* Title                 :   Uart Driver
* Filename              :   uart.c
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
*  09/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
/** @file uart.c
 *  @brief This is the source file for the uart driver.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>				/* For portable types */
#include <stm32l053xx.h>  /* For hardware definitions */
#include "uart.h"				  /* For uart driver types */		

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

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void Uart_GpioConfigure(void);
static void Uart_Uart1Configure(void);

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Function : Uart_Init()
*//** 
* \b Description:
*
*  This function is used to initialize the uart peripheral.
*
* @param  		Config is a pointer to a configuration structure of type UartConfig_t
*
* @return 		void
*
* @see Uart_PutChar
* @see Uart_GetChar
*
* \b Example Example:
* @code
*    Uart_Init(UartConfig);
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  09/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Uart_Init(const UartConfig_t *Config)
{
	UartChannel_t Channel = UART1;
	
	/* Loop through the configuration table and setup the UART */
	for(Channel = UART1; Channel < UART_MAX_CHANNEL; Channel++)
	{
		/* 
		 * Check to see if UART 1 should be enabled.
		 * TODO: Update to use pointer array memory register map.
		 */
		if((Channel == UART1) && 
			 (Config->UartState == UART_ENABLE))
		{
				Uart_GpioConfigure();
			  Uart_Uart1Configure();
		}
	} /* End of for loop through available uart devices */
}

/******************************************************************************
* Function : Uart_PutChar()
*//** 
* \b Description:
*
*  This function is used to transmit a character on the uart
*
* @param  		Channel is the uart number that data should be sent on
* @param 			Ch is the 8 bit character to be transmitted
*
* @return 		True if able to write the character, false otherwise.
*
* @see Uart_Init
* @see Uart_GetChar
*
* \b Example Example:
* @code
*    Uart_PutChar(UART1, 'H');
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  09/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
uint8_t Uart_PutChar(UartChannel_t Channel, uint8_t Ch )
{
	uint8_t ReturnVal = 0;
	
	if(Channel == UART1)
	{
		/* Check to make sure that previous transmissions are complete */
		if((USART1->ISR & USART_ISR_TC) != USART_ISR_TC)
		  USART1->ICR |= USART_ICR_TCCF;
		{	
		   USART1->TDR = Ch;
			 ReturnVal = 1;
		}
	}
	else if(Channel == UART2)
	{
		/* Check to make sure that previous transmissions are complete */
		if((USART1->ISR & USART_ISR_TC) != USART_ISR_TC)
		{	
   		USART2->TDR = Ch;
			ReturnVal = 1;
		}
	}
	
	return ReturnVal;
}

/******************************************************************************
* Function : Uart_GetChar()
*//** 
* \b Description:
*
*  This function is used to get a character out of the uart buffer
*
* @param  		Channel is the uart number that data should be sent on
*
* @return 		uint8_t character data from the uart receive buffer
*
* @see Uart_Init
* @see Uart_PutChar
*
* \b Example Example:
* @code
*    Value = Uart_GetChar(UART1);
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  09/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
uint8_t Uart_GetChar(UartChannel_t Channel)
{
	uint8_t ValueRead = 0;
	
	if(Channel == UART1)
	{
		ValueRead = USART1->RDR;
	}
	else if(Channel == UART2)
	{
		ValueRead = USART2->RDR;
	}	
	
	return ValueRead;
}




static void Uart_GpioConfigure(void)
{
		/* Enable the peripheral clock of GPIOA */
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	
	/* GPIO configuration for USART1 signals */
	/* (1) Select AF mode (10) on PA9 and PA10 */
	/* (2) AF4 for USART1 signals */
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE9|GPIO_MODER_MODE10))\
								 | (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1); /* (1) */
	GPIOA->AFR[1] = (GPIOA->AFR[1] &~ (0x00000FF0))\
									| (4 << (1 * 4)) | (4 << (2 * 4)); /* (2) */			
}

static void Uart_Uart1Configure(void)
{
		/* Enable the peripheral clock USART1 */
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

		/* Configure USART1 */
		/* (1) oversampling by 16, 9600 baud */
		/* (2) 8 data bit, 1 start bit, 1 stop bit, no parity */
		USART1->BRR = 20000/96;  /* (1) */
		USART1->CR1 = USART_CR1_TE | USART_CR1_UE; /* (2) */
		
		/* polling idle frame Transmission */
		while((USART1->ISR & USART_ISR_TC) != USART_ISR_TC)
		{ 
			/* add time out here for a robust application */
		}
		USART1->ICR |= USART_ICR_TCCF;/* clear TC flag */
		USART1->CR1 |= USART_CR1_TCIE;/* enable TC interrupt */
		
		/* Configure IT */
		/* (3) Set priority for USART1_IRQn */
		/* (4) Enable USART1_IRQn */
		NVIC_SetPriority(USART1_IRQn, 0); /* (3) */
		NVIC_EnableIRQ(USART1_IRQn); /* (4) */
}

/*************** END OF FUNCTIONS ***************************************************************************/
