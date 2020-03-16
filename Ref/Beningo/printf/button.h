/****************************************************************************
* Title                 :   Button Algorithm   
* Filename              :   button.h
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
*  04/01/15   1.0.0   Jacob Beningo   Interface Created.
*
*****************************************************************************/
/** @file button.h
 *  @brief This module exposes the state of system buttons and switches!
 * 
 *  This is the header file for the definition of the possible states that
 *  a button may have in addition to the buttons that exist in the system.  
 *  Three functions are used to initialize, debounce and get the state of
 *  a button.  
 */
#ifndef BUTTON_H_
#define BUTTON_H_

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
 * Button_State_t defines the possible states that a button may be in.  
 * Additional button states can be added to this enumeration.  Button_State_t
 * also defines a maximum value that can be used for boundary checking.
 */
typedef enum
{
   BUTTON_STATE_PRESSED,		/**< The pressed electrical state */
   BUTTON_STATE_NOT_PRESSED,	/**< The not pressed electrical state */
   BUTTON_STATE_MAX				/**< Maximum number of button states */
}Button_State_t;

/**
 * Button_t defines the buttons that exist within the embedded system. 
 * Additional buttons can be added by adding to this enumeration. 
 * It also defines a maximum value that can be used for boundary checking.
 */
typedef enum
{
   BUTTON_USER,				/**< The menu button */
   BUTTON_MAX_NUMBER			/**< Number of buttons in the system */
}Button_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void Button_Init(void);
void Button_Debounce(void);
Button_State_t Button_StateGet(Button_t Button);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*BUTTON_H_*/

/*** End of File **************************************************************/
