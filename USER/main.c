/**
  ******************************************************************************
  * @�ļ�	main.c
  * @����	2015-1-26
  * @˵��	�ֱ�����
  ******************************************************************************
  * ������ͨ��ѧ-ͨ��1208-��С��
  *
  * ˵��:	IAR�汾:7.20.2.7314
  *      	���ļ��汾:��׼�� V1.3.0
  * �ļ�����:	Tab Size:4
  * �Զ�����:	Body:4
  * ��ϸ˵����Documents��Readme.txt
  ******************************************************************************
  * ����������
  *           
  ******************************************************************************
  */
#include "includes.h"

int time = 2;
float32_t da1;
float32_t da2;
int m=0;
u16 adcx;  
float t1,t2,t3;
float infrared_data;
u8 senddata;
float a,b,distance,angle;

u32 PIDloopcount;

void delay_ms(unsigned int t)
{
	int volatile tmp1;
	int i;
	for(i = 0;i < 8400;i++)
	{
		tmp1 = t;
		while(tmp1--);
	}
}

void main(void)
{
	// �жϷ��������
	NVIC_Config();
	ENC_Init();
	Motor_Init();
	CAN_init();
	BEEP_Config();
    LED_Config();
    Timer_Configuration(); 
	
	while(1)
	{
	  if (CAN_rx_success_flag_2 == 1)
	  {
		CAN2_DATA();
		CAN_rx_success_flag_2 =0;
	  }

	  if(PIDloopcount % 1000 < 500)
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	  else
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	}
}

