
#include<stm32f4xx.h>
#include<stdint.h>

struct schedule
{
	uint32_t *psp;
	void (*task_PC)(void);
};

#define task1_stack_start (0x20020000)
#define task2_stack_start (task1_stack_start-2048)
#define scheduler_stack_start (task2_stack_start-2048)

void task1();
void task2();
void pro_fault_en();
void MemManage_Handler();
void BusFault_Handler();
void UsageFault_Handler();
void HardFault_Handler();
void port_init();
void systick_confg();
void put_psp_value(uint32_t *psp);
uint32_t* get_psp_value();
void MSP_to_scheduler_stack();
void update_next_task();
void tasks_stack_init();
__attribute__((naked)) void SysTick_Handler();
__attribute__((naked)) void set_pc_to_psp();

struct schedule running_task[3];
uint32_t *pPSP;
int a,b,current_task=0,led_control;

int main()
{

	MSP_to_scheduler_stack();
	pro_fault_en();
	port_init();
	tasks_stack_init();
	systick_confg();
	set_pc_to_psp();
	task1();
while(1);


}
