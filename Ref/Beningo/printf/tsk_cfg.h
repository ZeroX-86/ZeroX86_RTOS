/****************************************************************************
* Title                 :   Task Configuration
* Filename              :   tsk_cfg.h
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
/** \file tsk_cfg.h
 * \brief This is the header file for the configuration of the application tasks.
 *  Including this file will include all tasks and can also be used to turn off
 *  tasks that will not be used in an application.
 */
#ifndef TSK_CFG_H_
#define TSK_CFG_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include "scheduler.h"               // for TaskType

/******************************************************************************
* Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Configuration
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variable Declarations
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

TaskType *Tsk_GetConfig(void);
uint8_t Tsk_GetNumTasks(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*TSK_CFG_H_*/
/*** End of File **************************************************************/
