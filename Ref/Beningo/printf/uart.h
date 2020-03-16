/****************************************************************************
* Title                 :   Uart 
* Filename              :   uart.h
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
*****************************************************************************/
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
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author         Description 
*  08/19/15   1.0.0   Jacob Beningo   Interface Created.
*
*****************************************************************************/
/** @file uart.h
 *  @brief This module interfaces to the usart low level hardware
 * 
 *  This is the header file for the definition of the uart driver.
 */
#ifndef UART_H_
#define UART_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>			/* For portable types */

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


	
/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * This enumeration is a list of available UART channels on the part.
 */
typedef enum
{
   UART1,
   UART2,
   UART_MAX_CHANNEL
}UartChannel_t;

/** 
 * This enumeration is a list of possible UART states.
 */
typedef enum
{
   UART_DISABLE,
   UART_ENABLE,
   UART_MAX_STATE
}UartState_t;

/**
 * This enumeration is a list of possible stop bits.
 */
typedef enum
{
   UART_STOP1,
   UART_STOP2,
   UART_MAX_STOP
}UartStop_t;

/**
 * This structure defines the data members necessary to properly configure
 * the UART driver.
 */
typedef struct
{
   UartChannel_t 		 UartChannel;
   UartState_t       UartState;
   UartStop_t        StopBits;   
}UartConfig_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void Uart_Init(const UartConfig_t *Config);
uint8_t Uart_PutChar(UartChannel_t Channel, uint8_t Ch );
uint8_t Uart_GetChar(UartChannel_t Channel);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*UART_H_*/

/*** End of File **************************************************************/
