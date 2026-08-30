#include<stm32f4xx.h>

#define task1_stack_start (0x20020000)
#define task2_stack_start (task1_stack_start-2048)
#define scheduler_stack_start (task2_stack_start-2048)

extern void task1();
extern void task2();
struct schedule
{
	uint32_t *psp;
	void (*task_PC)(void);
};

extern struct schedule running_task[3];
extern int current_task;
extern uint32_t *pPSP;


void tasks_stack_init()
{
	running_task[0].psp= (uint32_t*) task1_stack_start;
	running_task[1].psp=(uint32_t*) task2_stack_start;

	running_task[0].task_PC = task1;
	running_task[1].task_PC = task2;
	for(int i = 0 ; i < 2 ;i++)
		{
		pPSP = running_task[i].psp;
		pPSP--;
		*pPSP = 0x01000000; // dummy xpsr
		pPSP--;
		*pPSP=(uint32_t)running_task[i].task_PC;  // set PC
		pPSP--;
		*pPSP = 0xFFFFFFFD;  // LR

		for(int j = 0 ; j < 13 ; j++)
			{
				pPSP--;
			    *pPSP = 0;

			}
		running_task[i].psp = pPSP;
		}

}




uint32_t* get_psp_value()
{
	return running_task[current_task].psp;
}


void put_psp_value(uint32_t *psp)
{
    running_task[current_task].psp = psp;
}

__attribute__((naked)) void MSP_to_scheduler_stack()
{
	  __asm volatile("MSR MSP,%0": :  "r" (scheduler_stack_start)  :   );
	     __asm volatile("BX LR");

}
__attribute__((naked)) void set_pc_to_psp()

{
	 //1. initialize the PSP with TASK1 stack start address
			//get the value of psp of current_task
			//Preserve LR which connects back to main() using PUSH
			__asm volatile ("PUSH {LR}");
			//Get the PSP Value of the Current Task
			__asm volatile ("BL get_psp_value");
			//Initialize PSP
			__asm volatile ("MSR PSP,R0");
			//Retrieve LR Value using POP
			__asm volatile ("POP {LR}");
			//Change SP to PSP using CONTROL register
			__asm volatile ("MOV R0,#0X02");
			__asm volatile ("MSR CONTROL,R0");
			//Return to Main Function
			__asm volatile ("BX LR");

}
