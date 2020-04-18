/*
 * ZeroX86.c
 *
 *  Date	: Nov 29, 2019
 *  Author  : MahmoudSaad.ZeroX-86
 *  Email   : Mahmoud.S.AbdElhares@gmail.com
 *  Github  : github.com/zerox-86
 *  LinkedIn: www.linkedin.com/in/mahmoudsaad96
 *  FaceBook: www.facebook.com/ZeroX86.MSA
 */
#include "ZeroX86.h"
#include "ZeroX86CFG.h"
#include "ZeroXPort.h"


static OS_ReturnT OS_ListInit(OS_TcbListT* TcbList);
static OS_ReturnT OS_ListInsertTask(OS_TcbListT* TcbList,OS_Tcb* Tcb);
static OS_ReturnT OS_ListRemoveTask(OS_TcbListT* TcbList,OS_Tcb* Tcb);
static OS_VoidT   OS_SysTick(OS_VoidT);
static OS_VoidT   OS_TaskTickCount(OS_VoidT* PVArg);
static OS_VoidT   OS_TaskExecute(OS_VoidT* PVArg);
static OS_ReturnT OS_ListTraverse(OS_TcbListT* TcbList,OS_VoidT(*PtrFunc)(OS_VoidT* ));
static OS_ReturnT OS_ListTraverseTop(OS_TcbListT* TcbList,OS_VoidT(*PtrFunc)(OS_VoidT* ));
static OS_ReturnT OS_ListRemoveTask(OS_TcbListT* TcbList,OS_Tcb* Tcb);

static OS_Uint32T  OS_SysClock;	//system tick counter since starting the os
static OS_TcbListT OS_RdyList;	//an internal list used to handle ready tasks
static OS_TcbListT OS_DlyList;	//an internal list used to handle delayed+ tasks
static OS_TaskHandlerT IdleHandler;
//req = if set the flag >> u must assign a function
OS_VoidT IdleTask(OS_VoidT *PVArg)
{
	#ifdef USE_IDLE_HOOK
	OnIdle();
	#endif	//USE_IDLE_HOOK
}

OS_ReturnT OS_SysInit(timer_select_t systick_timer)
{
	OS_SysClock = 0U;
	OS_ListInit(&OS_RdyList);
	OS_ListInit(&OS_DlyList);
	//OS_CreateTask(&IdleHandler,IdleTask,2,0,0,"tst",0);
	//assign the call back to the tick func
	systick_init(systick_timer,1000,OS_SysTick);
}
OS_ReturnT OS_CreateTask(OS_TaskHandlerT* TaskHandler,
			         	 OS_CodeHandlerT CodeHandler,
						 OS_Uint32T Period,OS_Uint8T Id,
			        	 OS_Uint32T StartTime,OS_Uint8T Name[],
						 OS_Uint8T Priority)
{
	//if dynamic
	OS_Tcb* PtrTemp = (OS_Tcb*)malloc(sizeof(OS_Tcb));
	//else create array of struct with the numb
	if (PtrTemp != OS_NULL)
	{
		PtrTemp->TaskId = Id;
		PtrTemp->TaskPeriod = Period;
		*TaskHandler = (OS_VoidT*)PtrTemp;
		PtrTemp->TaskPriority = Priority;
		PtrTemp->CodeHandler = CodeHandler;
		PtrTemp->TaskTimeOut = StartTime + Period;
		strcpy((char*)PtrTemp->TaskName,(const char*)Name);	
		if (0U == StartTime)
		{
			return (OS_ListInsertTask(&OS_RdyList,PtrTemp));
		} 
		else
		{
			return (OS_ListInsertTask(&OS_DlyList,PtrTemp));
		}
	}
	return OS_ERR_CNT_MALLOC;
}

OS_ReturnT OS_RemoveTask(OS_TaskHandlerT* TaskHandler)
{
	if (TaskHandler != OS_NULL)
	{
		
		if (((OS_Tcb*)TaskHandler)->TaskState )
		{
			return (OS_ListRemoveTask(&OS_RdyList,(OS_Tcb*)TaskHandler));
		}
		else
		{
			return (OS_ListRemoveTask(&OS_DlyList,(OS_Tcb*)TaskHandler));
		}
		free(TaskHandler);
		TaskHandler = OS_NULL;
	}
	return OS_ERR_CNT_MALLOC;
}
OS_ReturnT OS_SysRun(OS_VoidT)
{
	while (1)
	{
		OS_ListTraverseTop(&OS_RdyList,OS_TaskExecute);
	}
}
OS_ReturnT OS_DelayTask(OS_TaskHandlerT* Handler,OS_Uint32T Ticks)
{
	if (OS_NULL != Handler)
	{
		OS_Uint8T ExecRes1 = OS_ERR_NO;
		OS_Uint8T ExecRes2 = OS_ERR_NO;
		((OS_Tcb*)Handler)->TaskTimeOut = Ticks;
		((OS_Tcb*)Handler)->TaskState = TASK_WAITING;
		ExecRes1 = OS_ListRemoveTask(&OS_RdyList,(OS_Tcb*)Handler);
		ExecRes2 = OS_ListInsertTask(&OS_DlyList,(OS_Tcb*)Handler);
		/*if (ExecRes1 || ExecRes2)//TODO:error check differently or remove checking //OS_ERR_LIST_NOT_FOUND
		{
			return OS_ERR_LIST_X;
		}*/
		return OS_ERR_NO;
	}
	return OS_ERR_INV_PARAMS;
}
OS_ReturnT OS_SuspendTask(OS_TaskHandlerT* Handler)
{
	if (OS_NULL != Handler)
	{
		OS_Uint8T ExecRes1 = OS_ERR_NO;
		OS_Uint8T ExecRes2 = OS_ERR_NO;
		((OS_Tcb*)Handler)->TaskState = TASK_SUSPENDED;
		ExecRes1 = OS_ListRemoveTask(&OS_RdyList,(OS_Tcb*)Handler);
		ExecRes2 = OS_ListInsertTask(&OS_DlyList,(OS_Tcb*)Handler);
		/*if (ExecRes1 || ExecRes2)
		{
			return OS_ERR_LIST_X;
		}*/
		return OS_ERR_NO;
	}
	return OS_ERR_INV_PARAMS;
}
//resume works for delayed and suspended tasks is this good?
OS_ReturnT OS_ResumeTask(OS_TaskHandlerT* Handler)
{
	if (OS_NULL != Handler)
	{
		OS_Uint8T ExecRes1 = OS_ERR_NO;
		OS_Uint8T ExecRes2 = OS_ERR_NO;
		((OS_Tcb*)Handler)->TaskState = TASK_READY;
		ExecRes1 = OS_ListRemoveTask(&OS_DlyList,(OS_Tcb*)Handler);
		ExecRes2 = OS_ListInsertTask(&OS_RdyList,(OS_Tcb*)Handler);
		/*if (ExecRes1 || ExecRes2)
		{
			return OS_ERR_LIST_X;
		}*/
		return OS_ERR_NO;
	}
	return OS_ERR_INV_PARAMS;
}
/*SystickFunc*/
static OS_VoidT OS_SysTick(OS_VoidT)
{
	OS_ListTraverse(&OS_DlyList,OS_TaskTickCount);	
}
static OS_VoidT OS_TaskTickCount(OS_VoidT* PVArg)
{
	OS_Uint8T ExecRes1 = OS_ERR_NO;
	OS_Uint8T ExecRes2 = OS_ERR_NO;
	OS_Tcb* TempPtr = (OS_Tcb*)PVArg;
	TempPtr->TaskTimeOut--;
	OS_SysClock++;
	if (0U == TempPtr->TaskTimeOut)
	{
		TempPtr->TaskState = TASK_READY;
		
		ExecRes1 = OS_ListRemoveTask(&OS_DlyList,(OS_Tcb*)TempPtr);
		ExecRes2 = OS_ListInsertTask(&OS_RdyList,(OS_Tcb*)TempPtr);
/*
		if (ExecRes1 || ExecRes2)
		{
			return OS_ERR_LIST_X;//	TODO:error;
		}*/
		return OS_ERR_NO;
	}
}
static OS_VoidT OS_TaskExecute(OS_VoidT* PVArg)
{
	OS_Tcb* TempPtr = (OS_Tcb*)PVArg;
	//if (TASK_READY == TempPtr->TaskState)
	//{
		(*TempPtr->CodeHandler)(TempPtr->TaskArg);
		TempPtr->TaskState = TASK_WAITING;
		TempPtr->TaskTimeOut = TempPtr->TaskPeriod;
	//}
}
static OS_ReturnT OS_ListInit(OS_TcbListT* TcbList)
{
	if (OS_NULL != TcbList)
	{
		TcbList->PtrCurrTask = OS_NULL;
		TcbList->PtrListHead = OS_NULL;
		TcbList->I8ListSize  = 0U;
	} 
	else
	{
		return OS_ERR_INV_PARAMS;
	}
	return OS_ERR_NO;
}
static OS_ReturnT OS_ListInsertTask(OS_TcbListT* TcbList,OS_Tcb* Tcb)
{
	if ((OS_NULL != TcbList) && (OS_NULL != Tcb)){
		if(TcbList->I8ListSize < MAX_TASKS_NO){
				TcbList->I8ListSize++; 
			if (OS_NULL == TcbList->PtrListHead){
				TcbList->PtrListHead = Tcb;
				Tcb->PtrNext = OS_NULL;
				Tcb->PtrPrev = OS_NULL;
			} 
			else{
				OS_Tcb* TempPtr1 = OS_NULL;
				OS_Tcb* TempPtr2 = OS_NULL;
				OS_Uint8T TempIt = Tcb->TaskPriority;
				for (TempPtr1 = TcbList->PtrListHead;((TempPtr1->TaskPriority >= TempIt) && TempPtr1 != OS_NULL);TempPtr1=TempPtr1->PtrNext){
					TempPtr2 = TempPtr1;
				}
				if (OS_NULL == TempPtr1){
					TempPtr2->PtrNext = Tcb;
					Tcb->PtrNext = OS_NULL;
					Tcb->PtrPrev = TempPtr2;
				}
				else{
					Tcb->PtrNext = TempPtr1;
					Tcb->PtrPrev = TempPtr2;
					TempPtr2->PtrNext = Tcb;
					TempPtr1->PtrPrev = Tcb;
				}						
			}
		}
		else{
			return OS_ERR_LIST_FULL;
		}
	} 
	else{
		return OS_ERR_INV_PARAMS;
	}
	return OS_ERR_NO;
}
static OS_ReturnT OS_ListTraverse(OS_TcbListT* TcbList,OS_VoidT(*PtrFunc)(OS_VoidT* ))
{
	if ((OS_NULL != TcbList) && (OS_NULL != PtrFunc)){
		OS_Tcb* TemPtr = TcbList->PtrListHead;
		while(OS_NULL != TemPtr){
			(*PtrFunc)((OS_VoidT*)TemPtr);
			TemPtr = TemPtr->PtrNext;
		}
		return OS_ERR_NO;
	}
	return OS_ERR_INV_PARAMS;
}
static OS_ReturnT OS_ListTraverseTop(OS_TcbListT* TcbList,OS_VoidT(*PtrFunc)(OS_VoidT* ))
{
	if ((OS_NULL != TcbList) && (OS_NULL != PtrFunc)){
		OS_Tcb* TemPtr = TcbList->PtrListHead;
		while(OS_NULL != TemPtr){
			(*PtrFunc)((OS_VoidT*)TemPtr);
			OS_ListRemoveTask(&OS_RdyList,TemPtr);
			OS_ListInsertTask(&OS_DlyList,TemPtr);
			TemPtr = TcbList->PtrListHead;
		}
		return OS_ERR_NO;
	}
	return OS_ERR_INV_PARAMS;
}
static OS_ReturnT OS_ListRemoveTask(OS_TcbListT* TcbList,OS_Tcb* Tcb)
{
	if ((OS_NULL != TcbList) && (OS_NULL != Tcb)){
		if (OS_NULL == TcbList->PtrListHead){
			return OS_ERR_LIST_EMPTY;
		}
		else{
			if(0U > TcbList->I8ListSize){
				TcbList->I8ListSize--;
				OS_Tcb* TempPtr1 = OS_NULL;
				OS_Uint8T TempIt = Tcb->TaskPriority;
				for (TempPtr1 = TcbList->PtrListHead; \
				((TempPtr1->TaskPriority != TempIt) && TempPtr1 != OS_NULL);){
					TempPtr1=TempPtr1->PtrNext;
				}
				if (OS_NULL == TempPtr1){
					return OS_ERR_LIST_NOT_FOUND;
				}
				else{
					if (TempPtr1->PtrNext != OS_NULL){
						TempPtr1->PtrNext->PtrPrev = TempPtr1->PtrPrev;
					}
					TempPtr1->PtrPrev->PtrNext = TempPtr1->PtrNext;
				}
			}
			else{
				return OS_ERR_LIST_EMPTY;
			}
		}
	}
	else
	{
		return OS_ERR_INV_PARAMS;
	}
	return OS_ERR_NO;
}