/*
 * ZeroX86.h
 *
 *  Date	: Nov 29, 2019
 *  Author  : MahmoudSaad.ZeroX-86
 *  Email   : Mahmoud.S.AbdElhares@gmail.com
 *  Github  : github.com/zerox-86
 *  LinkedIn: www.linkedin.com/in/mahmoudsaad96
 *  FaceBook: www.facebook.com/ZeroX86.MSA
 */


#ifndef ZEROX86_H_
#define ZEROX86_H_

typedef void			Void;
typedef signed char		INT8 ;
typedef unsigned char	UINT8 ;
typedef signed short	INT16 ;
typedef unsigned short	UINT16 ;
typedef	signed long		INT32 ;
typedef unsigned long	UINT32;
#define MAX_TASK_NAME_LENGTH 20

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef struct  
{
	UINT8 Priority;
	UINT8 Id;
	Void(*TaskCB)(Void *PVArg);
	UINT8 Name[MAX_TASK_NAME_LENGTH];
}TaskEnteryT;

typedef struct ControlBlock
{
	struct ControlBlock* PtrNext;
	struct ControlBlock* PtrPrev;
	UINT8 TaskPriority;
	UINT8 TaskId;
	Void(*TaskCB)(Void *PVArg);
	UINT8 TaskName[MAX_TASK_NAME_LENGTH];
}TaskControlBlock;
//priorities are evaluated according to the prio val+the ID val?? or the priority + fifo

//prios or tcb structures>> a linked list/array of queues with each element have a ptr
// to the tasks and a ptr to the next ready prio level
//taskprioritySet
#define CREATE_TASK(HANDLE, PRIORITY, ID, TASKCB, NAME) TaskEnteryT HANDLE={.TaskPriority=PRIORITY,.TaskId=ID,.TaskCB=TASKCB,.TaskName=NAME};




#endif /* ZEROX86_H_ */
/*
MA112: Discrete Mathematics I: logic, basics, and foundationshttps://www.youtube.com/playlist?list=PLoK2Lr1miEm_WKBBBHUQJRXaumduqkM4S
Mathematics for Computer Sciencehttps://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-042j-mathematics-for-computer-science-fall-2010/index.htm
MIT 18.01 Single Variable Calculus, Fall 2006https://www.youtube.com/playlist?list=PL590CCC2BC5AF3BC1*/