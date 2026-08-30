#include<stm32f4xx.h>
#include<stdint.h>
extern int a,b,current_task,led_control;

void task1()

{
	while(1) {
	        if (led_control) {
	            GPIOC->ODR &= ~(1u<<13); // LED ON
	        } else {
	            GPIOC->ODR |= (1u<<13);  // LED OFF
	        }
	        for (volatile int i=0; i<500000; i++); // delay
	    }

}

void task2()
{
	 while(1) {
	        if (GPIOA->IDR & (1<<0)) {
	            led_control = 1;  // Button pressed -> turn LED ON
	        } else {
	            led_control = 0;  // Button released -> turn LED OFF
	        }
	        for (volatile int i=0; i<100000; i++); // debounce delay
	    }
}

void update_next_task()
{
	current_task++;
	current_task %= 2;
}
