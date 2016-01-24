/*���ܣ�pwm���ƹ���������
��ʱ��4 TIM4 4·pwm  PB6,PB7,PB8,PB9
�������� PC0,PC1,PC2,PC3
Motor_0 : pwm-PB6,����-PC0,PC1
Motor_1 : pwm-PB7,����-PC2,PC3
������ʵ�ʷ���Ϊ׼��
*/
#include "motor.h"




void Motor_Init(void)
{    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 |RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB |RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE,ENABLE);
	
	/* ���pwm�������� */
	GPIO_InitTypeDef GPIO_InitStructure;
	/* ���� GPIOC�ϵ� TIM1 �� 1��2��3��4ͨ����Ӧ���� PE.9,PE 11,PE 13,PE 14 Ϊ�ڶ������������ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 |GPIO_Pin_13| GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);
	
	/*��ӵ��ĸ�������������������*/
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14;   //���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   //���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
	/* ��ʱ��8���� */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* ���� TIM_OCInit ��ʼ���ṹ�� TIM_OCInitStructure */
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	//TIM_TimeBaseStructure.TIM_Period=1000;
	TIM_TimeBaseStructure.TIM_Period=5000;
	
	//TIM_TimeBaseStructure.TIM_Prescaler=720-1;
	TIM_TimeBaseStructure.TIM_Prescaler=0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM8 , &TIM_TimeBaseStructure);
	//����=TIM_Period/72000000/720
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//���� ������Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;   //MOE=0 ���� TIM1����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;//MOE=0 ���� TIM1����ȽϿ���״̬
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	
	/* ʹ��Ԥװ�ؼĴ��� */
	TIM_OC1PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;  //����������ģʽ�� �ǹ���״̬ѡ�� OSSR
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;  //����������ģʽ�� �ǹ���״̬ѡ�� OSSI
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;  //ʹ������ƽ1
	TIM_BDTRInitStructure.TIM_DeadTime = 0x2B;                //ָ��������ʹ� �ر�״̬֮�����ʱ Լ 1US  
	TIM_BDTRInitStructure.TIM_Break =  TIM_Break_Disable;  //ʹ��ɲ�� 
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;         //ɲ������ܽ� ���Ը�
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//�Զ��������ʹ��
	
	TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);        //��ʼ���趨�õĲ���
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	
	/* ���� TIM ���� */
	TIM_Cmd(TIM8 , ENABLE);   
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
	/* ��ʱ��1���� */
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* ���� TIM_OCInit ��ʼ���ṹ�� TIM_OCInitStructure */
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	//TIM_TimeBaseStructure.TIM_Period=1000;
	TIM_TimeBaseStructure.TIM_Period=5000;
	
	//TIM_TimeBaseStructure.TIM_Prescaler=720-1;
	TIM_TimeBaseStructure.TIM_Prescaler=0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM1 , &TIM_TimeBaseStructure);
	
	//����=TIM_Period/72000000/720
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//���� ������Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;   //MOE=0 ���� TIM1����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;//MOE=0 ���� TIM1����ȽϿ���״̬
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	/* ʹ��Ԥװ�ؼĴ��� */
	TIM_OC1PreloadConfig(TIM1 , TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1 , TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1 , TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1 , TIM_OCPreload_Enable);
	
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;  //����������ģʽ�� �ǹ���״̬ѡ�� OSSR
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;  //����������ģʽ�� �ǹ���״̬ѡ�� OSSI
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;  //ʹ������ƽ1
	TIM_BDTRInitStructure.TIM_DeadTime = 0x2B;                //ָ��������ʹ� �ر�״̬֮�����ʱ Լ 1US  
	TIM_BDTRInitStructure.TIM_Break =  TIM_Break_Disable;  //ʹ��ɲ�� 
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;         //ɲ������ܽ� ���Ը�
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//�Զ��������ʹ��
	
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);        //��ʼ���趨�õĲ���
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	/* ���� TIM ���� */
	TIM_Cmd(TIM1 , ENABLE);   
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
    
}

/*****����˶�������v-�ٶȣ�����ֵ����2������****/

void Move_Motor_0(int v)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_11);
    if(v<0)
    {		
		M0_PWM_1=0;
		M0_PWM_2=abs(v);
    }
    else
    {
        M0_PWM_1=abs(v);
		M0_PWM_2=0;
    }   
}

void Move_Motor_1(int v)
{
  //  MOTOR_1_PWM=abs(v);
    if(v<0)
    {
      	M1_PWM_1=0;
		M1_PWM_2=abs(v);
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        //GPIO_ResetBits(GPIOE,GPIO_Pin_11);       
    }
    else
    {       
      	M1_PWM_1=abs(v);
		M1_PWM_2=0;

		GPIO_SetBits(GPIOC,GPIO_Pin_12);
       // GPIO_SetBits(GPIOE,GPIO_Pin_11);
       // GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    }   
}
void Move_Motor_2(int v)
{
    
 //   MOTOR_2_PWM=abs(v);
    if(v<0)
    {
              
        M2_PWM_1=abs(v);
		M2_PWM_2=0;
        GPIO_SetBits(GPIOE,GPIO_Pin_12);
        //GPIO_ResetBits(GPIOE,GPIO_Pin_13);
    }
    else
    {

 		M2_PWM_1=0;
		M2_PWM_2=abs(v); 
        GPIO_SetBits(GPIOE,GPIO_Pin_12);
       // GPIO_ResetBits(GPIOE,GPIO_Pin_12);
    }   
}
void Move_Motor_3(int v)
{
    
 //   MOTOR_3_PWM=abs(v);
    if(v<0)
    {
		M3_PWM_1=abs(v);
		M3_PWM_2=0;
        GPIO_SetBits(GPIOC,GPIO_Pin_14);
       // GPIO_ResetBits(GPIOE,GPIO_Pin_14);
    }
    else
    {
		M3_PWM_1=0;
		M3_PWM_2=abs(v);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
        //GPIO_SetBits(GPIOE,GPIO_Pin_14);
       // GPIO_ResetBits(GPIOC,GPIO_Pin_14);
    }   
}

