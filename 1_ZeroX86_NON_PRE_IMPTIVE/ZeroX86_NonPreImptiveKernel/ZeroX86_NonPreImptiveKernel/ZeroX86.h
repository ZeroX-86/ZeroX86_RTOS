/*
 * ZeroX86.h
 *
 *  Date	: Nov 29, 2019
 *  Author  : MahmoudSaad.ZeroX-86
 *  Email   : Mahmoud.S.AbdElhares@gmail.com
 *  Github  : github.com/zerox96
 *  LinkedIn: www.linkedin.com/in/mahmoudsaad96
 *  FaceBook: www.facebook.com/ZeroX86.MSA
 */


#ifndef ZEROX86_H_
#define ZEROX86_H_
#include "ZeroXPort.h"
#include <stdlib.h>
#include <string.h>
typedef          void	OS_VoidT;
typedef signed   char	OS_Int8T ;
typedef unsigned char	OS_Uint8T ;
typedef signed   short	OS_Int16T ;
typedef unsigned short	OS_Uint16T ;
typedef	signed	 long	OS_Int32T ;
typedef unsigned long	OS_Uint32T;

#define OS_NULL ((void*)0)

#define TASK_WAITING	0U
#define TASK_READY		1U
#define TASK_SUSPENDED	2U

#define MAX_TASK_NAME_LENGTH 5U

#define USE_IDLE_HOOK 1U

//used to handle the task implementation
typedef OS_VoidT(*OS_CodeHandlerT)(OS_VoidT *PVArg);
//used to handle the task tcb
typedef OS_VoidT* OS_TaskHandlerT;

typedef struct ctrlBlock
{
	struct ctrlBlock*	PtrNext;	//pointer to the next task
	struct ctrlBlock*	PtrPrev;	//pointer to the prev task
	OS_Uint8T			TaskPriority;	//task priority
	OS_Uint8T			TaskId;	//task id
	OS_Uint8T			TaskState;	//task state
	OS_VoidT*			TaskArg;
	OS_Uint32T			TaskPeriod;	//??
	OS_Uint32T			TaskTimeOut;	//timeout delay down-counter
	OS_CodeHandlerT     CodeHandler;	//pointer to a task handler
	OS_Uint8T			TaskName[MAX_TASK_NAME_LENGTH];	//task name
	OS_Uint32T			TaskExecTime;	//variable to store the task exec time if enabled
}OS_Tcb;

typedef struct
{
	OS_Tcb*		PtrListHead;	//the highest-priority task
	OS_Tcb*		PtrCurrTask;	//the currently active task
	OS_Uint8T	U8ListSize;		//the no of tasks in the sys
}OS_TcbListT;

typedef enum {
	OS_ERR_NO,
	OS_ERR_INV_PARAMS,
	OS_ERR_LIST_EMPTY,
	OS_ERR_LIST_NOT_FOUND,
	OS_ERR_CNT_MALLOC,
	OS_ERR_LIST_X,	//when having any error with the list operations
		
}OS_ReturnT;


//priorities are evaluated according to the prio val+the ID val?? or the priority + fifo

//prios or tcb structures>> a linked list/array of queues with each element have a ptr
// to the tasks and a ptr to the next ready prio level
//taskprioritySet
//#define CREATE_TASK(HANDLE, PRIORITY, ID, TASKCB, NAME) TaskEnteryT HANDLE={.TaskPriority=PRIORITY,.TaskId=ID,.TaskCB=TASKCB,.TaskName=NAME};
OS_ReturnT OS_SysInit(timer_select_t systick_timer);
OS_ReturnT OS_SysRun(OS_VoidT);
OS_ReturnT OS_CreateTask(OS_TaskHandlerT TaskHandler,
					     OS_CodeHandlerT CodeHandler,
					   	 OS_Uint32T Period,OS_Uint8T Id,
					     OS_Uint32T StartTime,OS_Uint8T Name[],
					     OS_Uint8T Priority);
OS_ReturnT OS_RemoveTask(OS_TaskHandlerT* TaskHandler);
OS_ReturnT OS_SuspendTask(OS_TaskHandlerT* Handler);
OS_ReturnT OS_ResumeTask(OS_TaskHandlerT* Handler);
OS_ReturnT OS_DelayTask(OS_TaskHandlerT* Handler,OS_Uint32T Ticks);

#endif /* ZEROX86_H_ */
/*
MA112: Discrete Mathematics I: logic, basics, and foundationshttps://www.youtube.com/playlist?list=PLoK2Lr1miEm_WKBBBHUQJRXaumduqkM4S
Mathematics for Computer Sciencehttps://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-042j-mathematics-for-computer-science-fall-2010/index.htm
MIT 18.01 Single Variable Calculus, Fall 2006https://www.youtube.com/playlist?list=PL590CCC2BC5AF3BC1*/