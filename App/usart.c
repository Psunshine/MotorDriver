#include "usart.h"


void Usart_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;	
	//GPIOA��USART1ʱ��ʹ�ܢ�	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3,ENABLE);//ʹ��USART1ʱ��
	//USART_DeInit(USART1);  //��λ����2 ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //PA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //PA3����ΪUSART2	
		//USART_DeInit(USART1);  //��λ����3 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //PB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //PB11����ΪUSART3
	//USART2_TX /RX  PA.2 PA.3 ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����	
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3	
		//USART3_TX /RX  PB.10 PB.11 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����	
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11	
	//USART ��ʼ������ ��
	USART_InitStructure.USART_BaudRate = 115200;//һ������Ϊ9600;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ	
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ	
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      //�շ�ģʽ	
	USART_Init(USART2, &USART_InitStructure); //��ʼ������
	//USART_Init(USART3, &USART_InitStructure); //��ʼ������
	
	//USART_Cmd(USART2,ENABLE);
	//USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	

////	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
#if EN_USART2_RX   
//	 
//NVIC���ã�ʹ���ж� ��	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�	
	//Usart2 NVIC ����	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;          //��Ӧ���ȼ�2	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ��ʹ��	
	NVIC_Init(&NVIC_InitStructure);     //����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
#endif	
//#if EN_USART3_RX      //NVIC���ã�ʹ���ж� 	
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�	
//	//Usart3 NVIC ����	
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�2	
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;          //��Ӧ���ȼ�2	
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ��ʹ��	
//	NVIC_Init(&NVIC_InitStructure);     //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
//#endif
       USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���  ��
//     USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���  ��
	
}

void Send_Char(u8 Data)
{
	USART_SendData(USART2,Data);
	// �ȴ��������һ���ֽ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
}

void Send_Data(void)
{
	Send_Char(0x01);
	
	Send_Char(tmp_0&0x00FF);
	Send_Char(tmp_0>>8);
	
	Send_Char(tmp_1&0x00FF);
	Send_Char(tmp_1>>8);

	Send_Char(tmp_2&0x00FF);
	Send_Char(tmp_2>>8);
	Send_Char(0xC6);
}

//void USART2_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//	{
//		USART_ClearFlag(USART2, USART_FLAG_RXNE);
//		Usart1buf[pointer++%USART2_BUF_SIZE] = USART_ReceiveData(USART1);
//		
//		// �ڴ�д������ճ���
//		if(1)
//		{
//		}	
//	}
//}
