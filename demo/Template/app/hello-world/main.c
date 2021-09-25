#include "stm32f4xx.h" //STM32系统头文件
#include "stdio.h"
#include "ReTarget.h"
#include "bsp_tim6.h"
#include "bsp_uart1.h"
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //配置系统优先级组
	BSP_UART1_Init();
	BSP_TIM6_Init();
	while(1)
	{
	
	}
}
void TIM6_DAC_IRQHandler(void) 
{
    static int count = 0;
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET) //溢出中断
    {
        count++;
        if (count == 1000) //大周期
        {
            count = 0;
			printf("hello world!!!\r\n");

        }
    }
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除中断标志位
}
