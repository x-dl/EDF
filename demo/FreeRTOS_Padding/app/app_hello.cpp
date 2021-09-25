#include "FreeRTOS.h"
#include "task.h"



//任务优先级
#define TASK1_TASK_PRIO 3
//任务堆栈大小
#define TASK1_STK_SIZE 128
//任务句柄
static TaskHandle_t Task1Task_Handler;
//任务函数
void task1_task(void *pvParameters);

extern "C" void app_hello_main(void)
{
		taskENTER_CRITICAL(); //进入临界区
		xTaskCreate((TaskFunction_t)task1_task,			 //任务函数
				(const char *)"task1_task",			 //任务名称
				(uint16_t)TASK1_STK_SIZE,			 //任务堆栈大小
				(void *)NULL,						 //传递给任务函数的参数
				(UBaseType_t)TASK1_TASK_PRIO,		 //任务优先级
				(TaskHandle_t *)&Task1Task_Handler); //任务句柄
		 taskEXIT_CRITICAL();			//退出临界区
}

//task1任务函数
static void task1_task(void *pvParameters)
{
	while (1)
	{
		printf("hello world!!!\r\n");
		vTaskDelay(1000);										  //延时1s，也就是1000个时钟节拍
	}
}

