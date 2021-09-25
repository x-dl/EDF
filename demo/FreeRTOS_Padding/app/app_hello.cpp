#include "FreeRTOS.h"
#include "task.h"
//任务优先级
#define START_TASK_PRIO 1
//任务堆栈大小
#define START_STK_SIZE 128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define TASK1_TASK_PRIO 3
//任务堆栈大小
#define TASK1_STK_SIZE 128
//任务句柄
TaskHandle_t Task1Task_Handler;
//任务函数
void task1_task(void *pvParameters);
extern "C" void app_hello_main(void);
void app_hello_main(void)
{

    xTaskCreate((TaskFunction_t)start_task,			 //任务函数
				(const char *)"start_task",			 //任务名称
				(uint16_t)START_STK_SIZE,			 //任务堆栈大小
				(void *)NULL,						 //传递给任务函数的参数
				(UBaseType_t)START_TASK_PRIO,		 //任务优先级
				(TaskHandle_t *)&StartTask_Handler); //任务句柄
}
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); //进入临界区
	//创建TASK1任务
	xTaskCreate((TaskFunction_t)task1_task,
				(const char *)"task1_task",
				(uint16_t)TASK1_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)TASK1_TASK_PRIO,
				(TaskHandle_t *)&Task1Task_Handler);
	taskEXIT_CRITICAL();			//退出临界区
}
//task1任务函数
void task1_task(void *pvParameters)
{
	while (1)
	{
		printf("hello world\r\n");
		vTaskDelay(1000);										  //延时1s，也就是1000个时钟节拍
	}
}

