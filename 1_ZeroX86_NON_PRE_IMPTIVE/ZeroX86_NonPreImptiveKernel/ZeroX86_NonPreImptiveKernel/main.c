/*
 * ZeroX86_NonPreImptiveKernel.c
 *
 * Created: 11/24/2019 11:44:34 PM
 * Author : Mahmoud
 */ 

#include <avr/io.h>
#include "ZeroX86.h"
void OnIdle(void );
OS_VoidT task1(OS_VoidT*arg)
{
	PORTA++;
}
OS_VoidT task2(OS_VoidT*arg)
{
	PORTB++;
}
OS_VoidT task3(OS_VoidT*arg) 
{
	PORTC++;
}
int main(void)
{
	DDRA=DDRB=DDRC=DDRD=0xff;
	OS_TaskHandlerT TstHandler1;
	OS_TaskHandlerT TstHandler2;
	OS_TaskHandlerT TstHandler3;
	OS_SysInit(TIMER_0);
	OS_CreateTask(TstHandler1,task1,50,1,20,"TSK1",5);
	OS_CreateTask(TstHandler2,task2,100,2,30,"TSK2",9);
	OS_CreateTask(TstHandler3,task3,25,3,25,"TSK3",4);

	OS_SysRun();
	
    while (1) 
    {
    }
}

void OnIdle(void )
{
	
}
/*
A new MSc program at our dept: Professional MSc at Electronics and Telecom at EECE dept, Cairo University
Read and Share
=============================================
PROFESSIONAL MASTERS IN ELECTRONICS & TELECOMMUNICATIONS
The Department of Electronics and Electrical Communications Engineering announces the launch of its new Professional Masters program, starting from the academic year 2014-2015 in three proposed tracks:
- Telecommunications Networks
- Embedded Systems.
- Electronic and Micro Electronic Mechanical Systems Design.
This new, non thesis, degree is conducted in close partnership with the main local and multinational industrial corporations in the field of Electronics & Telecommunications. It aims to establish a standard-setting program in terms of curriculum design and pedagogical approach, producing professionals tuned to the challenging needs of industry and capable of coping with the rapid pace of change of the information and communication technology.
The program addresses freshly graduated engineers wishing to boost their chances of employability in industry as well as experienced engineers wishing to update their technical and managerial capabilities for a better career path.
This unique program incorporates advanced engineering subjects delivered with a professional view as well as non-engineering subjects addressing the managerial, economic, financial, regulatory and legal aspects of the engineering profession. This is in addition to a project dealing with an industrial problem supervised by academic and industry experts. For a better student  instructor interactivity the number of seats / track is limited. A number of total and partial fellowships will be available for qualified students.
For more information, send questions to ecpm@eng.cu.edu.eg. Registration and application for fellowships will start on the 1st of September, on the same site. Admission tests will take place on the 15th of September.
A website about the program will be available very soon
- Valeo Experts but no technical
- registration fees of one course is about 1200 LE
- Time starting from 5:15 pm to 8:15 pm
and this is the website:
http://www.eecumasters.com/
*/

