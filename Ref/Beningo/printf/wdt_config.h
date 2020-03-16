/****************************************************************************
* Title                 :   Wachdog Timer Configuration
* Filename              :   wdt_config.h
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
/** @file wdt_config.h
 *  @brief This module is used to configure the watchdog timer.
 * 
 *  This is the header file for the definition of the watchdog configuration.
 */
#ifndef WDT_CONFIG_H_
#define WDT_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/


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
 * Defines the possible debug states.
 */
typedef enum
{
	WDT_DEBUG_DISABLED,
	WDT_DEBUG_ENABLED,
	WDT_DEBUG_MAX
}WdtDebug_t;

/**
 * Defines the possible windows counter settings
 */
typedef enum
{
	WDT_WINDOW_MIN = 0x00,
	WDT_WINDOW_MAX = 0x7F
}WdtWindow_t;

/**
 * Defines the possible windows counter settings
 */
typedef enum
{
	WDT_COUNT_MIN = 0x00,
	WDT_COUNT_MAX = 0x7F
}WdtCounter_t;

/**
 * Defines the data necessary to fully configure 
 * the watchdog.
 */
typedef struct
{
   WdtDebug_t   DebugState;   /**< Enable or Disabled */
	 WdtWindow_t  WindowCount;  /**< Window width in counts */
	 WdtCounter_t CounterValue; /**< Dog Pet coutn */
}WdtConfig_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

const WdtConfig_t * Wdt_ConfigGet(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*WDT_H_*/

/*** End of File **************************************************************/
