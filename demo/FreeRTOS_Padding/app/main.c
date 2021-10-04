#include "stm32f4xx.h" //STM32ϵͳͷ�ļ�
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����ϵͳ���ȼ�����
	SysTick_Config((SystemCoreClock / 1000));
	BSP_UART1_Init();
	SEGGER_SYSVIEW_Conf();
	xTaskCreate((TaskFunction_t)start_task,			 //������
				(const char *)"start_task",			 //��������
				(uint16_t)START_STK_SIZE,			 //�����ջ��С
				(void *)NULL,						 //���ݸ��������Ĳ���
				(UBaseType_t)START_TASK_PRIO,		 //�������ȼ�
				(TaskHandle_t *)&StartTask_Handler); //������
	vTaskStartScheduler();							 //�����������
}
static void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); 			//�����ٽ���
void app_main(void);
	app_main();
	taskEXIT_CRITICAL();			//�˳��ٽ���
	vTaskDelete(NULL);
}
