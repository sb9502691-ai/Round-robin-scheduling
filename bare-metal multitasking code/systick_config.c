#include<stm32f4xx.h>

void systick_confg()
{
  SysTick->CTRL |=(1u<<2);
  SysTick->CTRL |=(1u<<1);
  SysTick->CTRL |=(1u<<0);
  SysTick->LOAD = 160000 - 1;

}
