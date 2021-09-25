#include "stm32f4xx.h" //STM32系统头文件
#include "core_cm4.h"
#include "stdio.h"
#include "ReTarget.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_uart1.h"
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

//任务优先级
#define TASK2_TASK_PRIO 2
//任务堆栈大小
#define TASK2_STK_SIZE 128
//任务句柄
TaskHandle_t Task2Task_Handler;
//任务函数
void task2_task(void *pvParameters);
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //配置系统优先级分组
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART1_Init();
    xTaskCreate((TaskFunction_t)start_task,			 //任务函数
				(const char *)"start_task",			 //任务名称
				(uint16_t)START_STK_SIZE,			 //任务堆栈大小
				(void *)NULL,						 //传递给任务函数的参数
				(UBaseType_t)START_TASK_PRIO,		 //任务优先级
				(TaskHandle_t *)&StartTask_Handler); //任务句柄
	vTaskStartScheduler();							 //开启任务调度
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
	//创建TASK2任务
	xTaskCreate((TaskFunction_t)task2_task,
				(const char *)"task2_task",
				(uint16_t)TASK2_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)TASK2_TASK_PRIO,
				(TaskHandle_t *)&Task2Task_Handler);
	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL();			//退出临界区
}

//task1任务函数
void task1_task(void *pvParameters)
{
	while (1)
	{
		printf("i am task1\r\n");
		vTaskDelay(1000);										  //延时1s，也就是1000个时钟节拍
	}
}
//task2任务函数
void task2_task(void *pvParameters)
{
	while (1)
	{
		printf("i am task2\r\n");
		vTaskDelay(1000);										  //延时1s，也就是1000个时钟节拍
	}
}
