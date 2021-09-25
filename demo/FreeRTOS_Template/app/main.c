#include "stm32f4xx.h" //STM32系统头文件
#include "core_cm4.h"
#include "stdio.h"
#include "ReTarget.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_uart1.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //配置系统优先级分组
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART1_Init();
	void app_hello_main(void);
	app_hello_main();
	vTaskStartScheduler();							 //开启任务调度
}
