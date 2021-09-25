#include "FreeRTOS.h"
#include "task.h"
//�������ȼ�
#define START_TASK_PRIO 1
//�����ջ��С
#define START_STK_SIZE 128
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define TASK1_TASK_PRIO 3
//�����ջ��С
#define TASK1_STK_SIZE 128
//������
TaskHandle_t Task1Task_Handler;
//������
void task1_task(void *pvParameters);
extern "C" void app_hello_main(void);
void app_hello_main(void)
{

    xTaskCreate((TaskFunction_t)start_task,			 //������
				(const char *)"start_task",			 //��������
				(uint16_t)START_STK_SIZE,			 //�����ջ��С
				(void *)NULL,						 //���ݸ��������Ĳ���
				(UBaseType_t)START_TASK_PRIO,		 //�������ȼ�
				(TaskHandle_t *)&StartTask_Handler); //������
}
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); //�����ٽ���
	//����TASK1����
	xTaskCreate((TaskFunction_t)task1_task,
				(const char *)"task1_task",
				(uint16_t)TASK1_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)TASK1_TASK_PRIO,
				(TaskHandle_t *)&Task1Task_Handler);
	taskEXIT_CRITICAL();			//�˳��ٽ���
}
//task1������
void task1_task(void *pvParameters)
{
	while (1)
	{
		printf("hello world\r\n");
		vTaskDelay(1000);										  //��ʱ1s��Ҳ����1000��ʱ�ӽ���
	}
}

