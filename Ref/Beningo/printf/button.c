/*******************************************************************************
* Title                 :   Button Algorithm   
* Filename              :   button.c
* Author                :   Jacob Beningo
* Origin Date           :   04/01/2015
* Version               :   1.0.0
* Compiler              :   ARM GNU C/C++ 1.10.2.201407190854
* Target                :   TODO: PICK A TARGET!
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
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
/** @file button.c
 *  @brief This is the source file for debouncing system buttons
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>				/* For portable types */
#include "button.h"				/* For button definitions */		
#include <stm32l053xx.h>

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define GPIO_13								13
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
 * Defines a list of masks that identify the gpio channel that the buttons 
 * are attached to.  These are used by Gpio_ChannelRead to get the pin state.
 */
const uint16_t ButtonList[] =
{
	GPIO_13
};

/**
 * ButtonCurrentState holds the current state of the physical pin
 * They are initialized to NOT_PRESSED which is an electrical state
 * of 1.
 */
Button_State_t ButtonCurrentState[BUTTON_MAX_NUMBER] =
{
    BUTTON_STATE_NOT_PRESSED
};

/**
 * Defines a list that contains the number of debounce counts necessary
 * to successfully debounce the button(s).  An array was chosen so that
 * different buttons with different debounce parameters could be used
 * in the same application.  It is assumed that each count represents
 * 10 milliseconds.  In this case each switch has a 30 millisecond
 * debounce time.  Different switches can be attached and debounced at
 * different rates.
 */
const uint8_t ButtonDebounceCountList[BUTTON_MAX_NUMBER] =
{
   4,
};

/**
 * Stores the current debounce count of the buttons.  This variable is
 * initialized in Button_Init.
 */
uint8_t ButtonDebounceCount[BUTTON_MAX_NUMBER];

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Button_State_t Gpio_ChannelRead(uint16_t Pin);

/******************************************************************************
* Function Definitions
*******************************************************************************/
Button_State_t Gpio_ChannelRead(uint16_t Pin)
{
		return (Button_State_t)((GPIOC->IDR >> Pin) & 0x1);
}

/******************************************************************************
* Function : Button_Init()
*//** 
* \b Description:
*
*  This function is used to initialize the button variables.  It assumes that
*  the gpio pins have already been configured as inputs with the appropriate
*  settings.
*
* @param  		void
*
* @return 		void
*
* @see Button_Init
* @see Button_Debounce
* @see Button_StateGet
*
* \b Example Example:
* @code
*    Gpio_Init();
*    Button_Init();
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Button_Init(void)
{
	uint8_t i = 0;

	/* Initialize ButtonDebounceCount to an initial value of zero for all
	 * buttons that are attached to the system.
	 */
	for(i = 0; i < BUTTON_MAX_NUMBER; i++)
	{
		ButtonDebounceCount[i] = 0;
	}
	
	RCC->IOPENR |=  (1ul << 2);                   /* Enable GPIOC clock         */
	
  GPIOC->MODER   &= ~(3UL << 2* 13);
  GPIOC->OSPEEDR &= ~(3UL << 2* 13);
  GPIOC->OSPEEDR |=  (1UL << 2* 13);
  GPIOC->PUPDR   &= ~(3UL << 2* 13);
}

/******************************************************************************
* Function : Button_Debounce()
*//** 
* \b Description:
*
* This function is used to debonce buttons that are attached to the system.  
* It loops through ButtonList which contains all available buttons.  Each 
* button pin state is then read.  If a change has occurred, it is noted by an
* increment to ButtonDebounceCount.  When ButtonDebounceCount has reached the 
* ButtonDebounceCountList value for that button, the button will have been 
* debounced and the button state will be updated in ButtonCurrentState.
*
* @param  		void
*
* @return 		void
*
* @see Button_Init
* @see Button_Debounce
* @see Button_StateGet
*
* \b Example Example:
* @code
*    // In System_Init
*    Gpio_Init();
*    Button_Init();
*
*	 // In Task_10ms
*    Button_Debounce();
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Button_Debounce(void)
{
	uint8_t Index = 0;

	/* Loop through all of the buttons, read their state and determine if
	 * any of their states have changed.
	 */
	for(Index = 0; Index < BUTTON_MAX_NUMBER; Index++)
	{
		/* Check to see if the pin reading is different than the current
		 * debounced button state.  If it is different then the debounce
		 * counter for this pin will be incremented.  If it is the same
		 * the counter will be cleared.
		 */
		if(Gpio_ChannelRead(ButtonList[Index]) != ButtonCurrentState[Index])
		{
			ButtonDebounceCount[Index]++;

			/* Check to see if the debounce count has met or exceeded the
			 * required count.  If it has, then the state of the button is
			 * updated.  Otherwise it is left as is.
			 */
			if(ButtonDebounceCount[Index] >= ButtonDebounceCountList[Index])
			{
				if(ButtonCurrentState[Index] == BUTTON_STATE_NOT_PRESSED)
				{
					ButtonCurrentState[Index] = BUTTON_STATE_PRESSED;
				}
				else
				{
					ButtonCurrentState[Index] = BUTTON_STATE_NOT_PRESSED;
				}
			}
		}
		else
		{
			ButtonDebounceCount[Index] = 0;
		}
	} // End for loop
}

/******************************************************************************
* Function : Button_StateGet()
*//** 
* \b Description:
*
* This function is used to return the current state of a button to the application.
* The application can then use this information to run a state machine or 
* perform other related tasks.
*
* @param  		Button Button_t, a system button defined in the Button_t enum
*
* @return 		Button_State_t the debounced state of the button
*
* @see Button_Init
* @see Button_Debounce
* @see Button_StateGet
*
* \b Example Example:
* @code
*    // In System_Init
*    Gpio_Init();
*    Button_Init();
*
*	 // In Task_10ms
*    Button_Debounce();
*
*    Button_MenuState = Button_StateGet(BUTTON_MENU);
*
*    if(Button_MenuState == BUTTON_PRESSED)
*    {
*	    Led_Toggle(LED_RED);
*	 }
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description 
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
Button_State_t Button_StateGet(Button_t Button)
{
	Button_State_t State;

	/* Verify that the requested button exists and
	 * return its state.  If it doesn't exist, then
	 * return the MAX as an error code.
	 */
	if(Button < BUTTON_MAX_NUMBER)
	{
		State = ButtonCurrentState[Button];
	}
	else
	{
		State = BUTTON_STATE_MAX;
	}

	return State;
}

/*************** END OF FUNCTIONS ***************************************************************************/
