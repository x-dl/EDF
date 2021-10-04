#include "stm32f4xx.h" //STM32系统头文件
#include "core_cm4.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_uart1.h"
#include "SEGGER_SYSVIEW.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 128
static TaskHandle_t StartTask_Handler;
static void start_task(void *pvParameters);
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //配置系统优先级分组
	SysTick_Config((SystemCoreClock / 1000));
	BSP_UART1_Init();
	SEGGER_SYSVIEW_Conf();
	xTaskCreate((TaskFunction_t)start_task,			 //任务函数
				(const char *)"start_task",			 //任务名称
				(uint16_t)START_STK_SIZE,			 //任务堆栈大小
				(void *)NULL,						 //传递给任务函数的参数
				(UBaseType_t)START_TASK_PRIO,		 //任务优先级
				(TaskHandle_t *)&StartTask_Handler); //任务句柄
	vTaskStartScheduler();							 //开启任务调度
}
static void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); 			//进入临界区
void app_main(void);
	app_main();
	taskEXIT_CRITICAL();			//退出临界区
	vTaskDelete(NULL);
}
