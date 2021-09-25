#include "bsp_systick.h"
void BSP_SYSTICK_Init(uint32_t ticks)
{
	SysTick->LOAD = ticks ; /* set reload register */		 //
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1); /* set Priority for Systick Interrupt */
	SysTick->VAL = 0;											 /* Load the SysTick Counter Value */
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
					SysTick_CTRL_TICKINT_Msk |
					SysTick_CTRL_ENABLE_Msk; /* Enable SysTick IRQ and SysTick Timer */
}
