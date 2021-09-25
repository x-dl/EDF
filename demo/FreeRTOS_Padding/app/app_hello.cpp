#include "FreeRTOS.h"
#include "task.h"



//�������ȼ�
#define TASK1_TASK_PRIO 3
//�����ջ��С
#define TASK1_STK_SIZE 128
//������
static TaskHandle_t Task1Task_Handler;
//������
void task1_task(void *pvParameters);

extern "C" void app_hello_main(void)
{
		taskENTER_CRITICAL(); //�����ٽ���
		xTaskCreate((TaskFunction_t)task1_task,			 //������
				(const char *)"task1_task",			 //��������
				(uint16_t)TASK1_STK_SIZE,			 //�����ջ��С
				(void *)NULL,						 //���ݸ��������Ĳ���
				(UBaseType_t)TASK1_TASK_PRIO,		 //�������ȼ�
				(TaskHandle_t *)&Task1Task_Handler); //������
		 taskEXIT_CRITICAL();			//�˳��ٽ���
}

//task1������
static void task1_task(void *pvParameters)
{
	while (1)
	{
		printf("hello world!!!\r\n");
		vTaskDelay(1000);										  //��ʱ1s��Ҳ����1000��ʱ�ӽ���
	}
}

