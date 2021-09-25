#include "bsp_tim6.h"
void BSP_TIM6_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    uint32_t PrescalerValue = 84 - 1;
    uint32_t Period = 1000 - 1;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);         //使能时钟
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //计数模式
    TIM_TimeBaseInitStruct.TIM_Period = Period;                  //自动重装载值，范围0~65535,
    TIM_TimeBaseInitStruct.TIM_Prescaler = PrescalerValue;       //分频系数，不为1时，定时器频率挂载总线的两倍（看时钟树得出），所以42000000/42000
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);             //初始化
    TIM_Cmd(TIM6, ENABLE);                                       //使能定时器6

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); //允许定时器6更新中断
    NVIC_EnableIRQ(TIM6_DAC_IRQn);             //使能TIM6中断
}
