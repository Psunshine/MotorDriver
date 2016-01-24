/**
  ******************************************************************************
  * @�ļ�	Sysinit.c
  * @����	2015-1-26
  * @˵��	ϵͳ��ʼ��
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
  *           ����ϵͳ��ʼ��
  ******************************************************************************
  */
#include "includes.h"



/*******************************************************************************
�� �� ����NVIC_Config(void)
��    �����жϷ��������
*******************************************************************************/
void NVIC_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

/*******************************************************************************
�� �� ����Struct_Init(void)
��    ����ϵͳ�ṹ���ʼ��ָ��
*******************************************************************************/


void BEEP_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOD,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
}
void delay(int tmp)
{
	int volatile tmp1;
	int i;
	for(i = 0;i < 1000;i++)
	{
		tmp1 = tmp;
		while(tmp1--);
	}
}
