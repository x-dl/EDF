#include "stm32f4xx.h" //STM32ϵͳͷ�ļ�
#include "core_cm4.h"
#include "stdio.h"
#include "ReTarget.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_uart1.h"
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

//�������ȼ�
#define TASK2_TASK_PRIO 2
//�����ջ��С
#define TASK2_STK_SIZE 128
//������
TaskHandle_t Task2Task_Handler;
//������
void task2_task(void *pvParameters);
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����ϵͳ���ȼ�����
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART1_Init();
    xTaskCreate((TaskFunction_t)start_task,			 //������
				(const char *)"start_task",			 //��������
				(uint16_t)START_STK_SIZE,			 //�����ջ��С
				(void *)NULL,						 //���ݸ��������Ĳ���
				(UBaseType_t)START_TASK_PRIO,		 //�������ȼ�
				(TaskHandle_t *)&StartTask_Handler); //������
	vTaskStartScheduler();							 //�����������
}
void TIM6_DAC_IRQHandler(void) 
{
    static int count = 0;
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET) //����ж�
    {
        count++;
        if (count == 1000) //������
        {
            count = 0;
			printf("hello world!!!\r\n");

        }
    }
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //����жϱ�־λ
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
	//����TASK2����
	xTaskCreate((TaskFunction_t)task2_task,
				(const char *)"task2_task",
				(uint16_t)TASK2_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)TASK2_TASK_PRIO,
				(TaskHandle_t *)&Task2Task_Handler);
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	taskEXIT_CRITICAL();			//�˳��ٽ���
}

//task1������
void task1_task(void *pvParameters)
{
	while (1)
	{
		printf("i am task1\r\n");
		vTaskDelay(1000);										  //��ʱ1s��Ҳ����1000��ʱ�ӽ���
	}
}
//task2������
void task2_task(void *pvParameters)
{
	while (1)
	{
		printf("i am task2\r\n");
		vTaskDelay(1000);										  //��ʱ1s��Ҳ����1000��ʱ�ӽ���
	}
}
