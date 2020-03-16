/****************************************************************************
* Title                 :   Wachdog Timer Configuration
* Filename              :   wdt_config.c
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
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author         Description 
*  08/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
/** @file wdt_config.c
 *  @brief This is the source file for watchdog timer configuration
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>						/* For portable types */
#include <stm32l053xx.h>  		/* For hardware definitions */
#include "wdt_config.h"				/* For definitions and types */		

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
 * Defines the watchdog timer configuration settings
 */ 
const WdtConfig_t WdtConfig =
{
   WDT_DEBUG_DISABLED,
	 WDT_WINDOW_MAX,
	 WDT_COUNT_MAX
};

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Function : Wdt_ConfigGet()
*//** 
* \b Description:
*
*  This function is used to initialize the watchdog timer.
*
* @return  Pointer to the configuration table
*
* @see Wdt_Init
* @see Wdt_Enable
* @see Wdt_Disable
* @see Wdt_Reset
* @see Wdt_Clear
*
* \b Example Example:
* @code
*    WdtConfig_t WdtConfig = Wdt_ConfigGet();
*    Wdt_Init(WdtConfig);
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  08/19/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
const WdtConfig_t * Wdt_ConfigGet(void)
{
   return &WdtConfig;
}

/*************** END OF FUNCTIONS ***************************************************************************/
