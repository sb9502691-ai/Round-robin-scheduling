#include<stm32f4xx.h>
void port_init()
{
	RCC->AHB1ENR |= (1<<2) | (1<<0);  // Enable GPIOC clock
	 GPIOA->MODER &= ~(0x3 << (0*2));
	GPIOC->MODER &= ~(0x3 << (13 * 2));   // Clear MODER13 bits (26 & 27)
	GPIOC->MODER |=  (0x1 << (13 * 2));   // Set MODER13 = 01 (output)

}
