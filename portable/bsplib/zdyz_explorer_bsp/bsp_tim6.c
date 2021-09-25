#include "bsp_tim6.h"
void BSP_TIM6_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    uint32_t PrescalerValue = 84 - 1;
    uint32_t Period = 1000 - 1;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);         //ʹ��ʱ��
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //����ģʽ
    TIM_TimeBaseInitStruct.TIM_Period = Period;                  //�Զ���װ��ֵ����Χ0~65535,
    TIM_TimeBaseInitStruct.TIM_Prescaler = PrescalerValue;       //��Ƶϵ������Ϊ1ʱ����ʱ��Ƶ�ʹ������ߵ���������ʱ�����ó���������42000000/42000
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);             //��ʼ��
    TIM_Cmd(TIM6, ENABLE);                                       //ʹ�ܶ�ʱ��6

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); //����ʱ��6�����ж�
    NVIC_EnableIRQ(TIM6_DAC_IRQn);             //ʹ��TIM6�ж�
}
