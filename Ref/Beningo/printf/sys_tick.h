/****************************************************************************
* Title                 :   System Tick
* Filename              :   sys_tick.h
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
/** \file sys_tick.h
 * \brief This file contains the header definitions for the system initalization.
 */
#ifndef SYS_TICK_H_
#define SYS_TICK_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>				// For standard type definitions

/******************************************************************************
* Constants
*******************************************************************************/

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

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void SysTick_Init(uint32_t Interval);
uint32_t SysTick_GetSystemTick();
void SysTick_ISR(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*SYS_INIT_H_*/

/*** End of File **************************************************************/
