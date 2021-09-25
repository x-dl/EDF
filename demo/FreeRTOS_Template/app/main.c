#include "stm32f4xx.h" //STM32ϵͳͷ�ļ�
#include "core_cm4.h"
#include "stdio.h"
#include "ReTarget.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_uart1.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����ϵͳ���ȼ�����
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART1_Init();
	void app_hello_main(void);
	app_hello_main();
	vTaskStartScheduler();							 //�����������
}
