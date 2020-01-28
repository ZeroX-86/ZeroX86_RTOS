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

#define CREATE_TASK(HANDLE, PRIORITY, ID, TASKCB, NAME) TaskEnteryT HANDLE={.TaskPriority=PRIORITY,.TaskId=ID,.TaskCB=TASKCB,.TaskName=NAME};




#endif /* ZEROX86_H_ */