#include "timer.h"

extern u32 PIDloopcount;

void Timer_Configuration(void)
{
  	//////////////��ʼ�� �ж�
	NVIC_InitTypeDef  NVIC_InitStructure; 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);  
  	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);	
	////////////////////��ʼ����ʱ��
	//////////////��ʱ�ж�ʱ��
	uint16_t Prescalervalue=(uint16_t)(SystemCoreClock/8/100000)-1;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  	TIM_TimeBaseStructure.TIM_Period = 399;              //1ms ��ʱ (399+1)*(209+1)/84000=1 ms
  	TIM_TimeBaseStructure.TIM_Prescaler = Prescalervalue;//209
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
  	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
  	TIM_Cmd(TIM7, ENABLE);
}

void TIM7_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET )
	{	
		TIM_ClearITPendingBit(TIM7,TIM_FLAG_Update);
		TIM_ClearFlag(TIM7,TIM_FLAG_Update);
		ENC_Read();
		SetSpeed();
		PIDloopcount++;
	}
}
