
#include<stm32f4xx.h>
extern void save_psp_value();
extern void update_next_task();
void pro_fault_en()
{
	SCB->SHCSR |= (1U<<18);
	SCB->SHCSR |= (1U<<17);
	SCB->SHCSR |= (1U<<16);
}

void MemManage_Handler()
{

}

void BusFault_Handler()
{

}

void UsageFault_Handler()
{


}


void HardFault_Handler()
{


}

__attribute__((naked)) void SysTick_Handler()

{
	//1. Get current running task's PSP value
			__asm volatile("MRS R0,PSP");
			//2. Using that PSP value store SF2( R4 to R11)
			__asm volatile("STMDB R0!,{R4-R11}");
		    //3.Save the LINK Register Using PUSH Operations
			__asm volatile("PUSH {LR}");
			//4. Save the current value of PSP
		    __asm volatile("BL put_psp_value");
		    //5. Decide next task to run
		    __asm volatile("BL update_next_task");
			//6. get its past PSP value
			__asm volatile ("BL get_psp_value");
			//7. Using that PSP value retrieve SF2(R4 to R11)
			__asm volatile ("LDMIA R0!,{R4-R11}");
			//8. update PSP
			__asm volatile("MSR PSP,R0");
		     //9.Retrieve the LINK Register Using POP Operations
			__asm volatile("POP {LR}");
		     //Update PSP and exit
			__asm volatile("BX LR");


}
