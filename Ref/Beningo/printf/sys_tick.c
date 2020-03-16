/****************************************************************************
* Title                 :   System Tick
* Filename              :   sys_tick.c
* Author                :   JWB
* Origin Date           :   11/07/2012
* Version               :   1.0.0
* Compiler              :   IAR C/C++ Compiler for ARM v6.40.4
* Target                :   MKL25Z128VLK4
* Copyright             :   Beningo Engineering
* All Rights Reserved
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
* Notes                 :   None
*
* Revision Log:
*
* REV           Author        Date                  Changes
* 1.0.0          JWB       11/07/2012           Initial Release
*******************************************************************************/
/** \file sys_tick.c
 * \brief This module contains the system tick.
*******************************************************************************/
#include "sys_tick.h"			// For timer initialization
#include "MKL25Z4.h"			// For Hardware definitions
#include "mcu_cfg.h"			// For system clock frequency definition
#include "constants.h"			// For REGBIT definitions

/******************************************************************************
* Constants
*******************************************************************************/
/**
 *  Defines a pointer to the SysTick Reload Value Register on the microcontroller.
 */
uint32_t volatile * const systload = (uint32_t*)&SYST_RVR;

/**
 *  Defines a pointer to the SysTick Current Value Register on the microcontroller.
 */
uint32_t volatile * const systval = (uint32_t*)&SYST_CVR;

/**
 *  Defines a pointer to the system tick control register on the microcontroller.
 */
uint32_t volatile * const systcon = (uint32_t*)&SYST_CSR;

/******************************************************************************
* Configuration
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/
/**
 * System tick variable
 */
static volatile uint32_t tick = 0;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : SysTick__Init()
*//**
* \section Description Description:
*
*  This function initializes the system tick module.
*
* \param     Interval - uint32_t, system tick interval in us.
*
* \return     None.
*
* \section Example Example:
* \code
*  	void Tmr_SysTickInit(uint32_t Interval)
*	{
*		SysTick_Init(Interval);
*	}
* \endcode
*
* \see
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  01/02/14       0.1.1            JWB      Function Created.
*
*******************************************************************************/
void SysTick_Init(uint32_t Interval)
{
	// Set the system tick reload value with the desired interval
	*systload = (GetSystemClock() / (1000000UL / Interval)) - 1;

	*systval = 0;		// Clear the current counter value

	*systcon = 0;									// Clear the system tick control and status register
	*systcon |= (REGBIT2 + REGBIT1 + REGBIT0);		// Enable the system tick with interrupt
}

/******************************************************************************
* Function : SysTick_GetSystemTick()
*//**
* \section Description Description:
*
*  This function returns the current system tick value
*
* \param     None.
*
* \return     uint32_t - system tick
*
* \section Example Example:
* \code
*	uint32_t tick = SysTick_GetSystemTick();
* \endcode
*
* \see
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  01/02/14       0.1.1            JWB      Function Created.
*
*******************************************************************************/
uint32_t SysTick_GetSystemTick()
{
	return tick;
}

/******************************************************************************
* Function : SysTick_ISR()
*//**
* \section Description Description:
*
*  This function is the System Tick Interrupt Serive Routine.  Increment the
*  system tick.
*
* \param     None.
*
* \return     None.
*
* \see
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  01/02/14       0.1.1            JWB      Function Created.
*
*******************************************************************************/
void SysTick_ISR(void)
{
	tick++;
}

/*** End of File **************************************************************/
