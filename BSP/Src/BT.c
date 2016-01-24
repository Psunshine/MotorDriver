/**
  ******************************************************************************
  * @�ļ�	BT.c
  * @����	2015-1-26
  * @˵��	��������
  ******************************************************************************
  * ������ͨ��ѧ-ͨ��1208-��С��
  *
  * ˵��:	IAR�汾:7.20.2.7314
  *      	���ļ��汾:��׼�� V1.3.0
  * �ļ�����:	Tab Size:4
  * �Զ�����:	Body:4
  * ��ϸ˵����Documents��Readme.txt
  ******************************************************************************
  * ʹ�õĽӿڣ�
  *             PC12 -> TX , PD2 -> RX , PC11 -> BT_Status
  * ʹ�õ����裺
  *             UART5
  ******************************************************************************
  */

#include "includes.h"

// �����ṹ�嶨��
BTTypeDef BT;

/*******************************************************************************
�� �� ����BT_Struct_Init(void)
��    ������ʼ������ģ��ṹ��
*******************************************************************************/
void BT_Struct_Init(void)
{	
	BT.BTStatus = BT_Mode_Noconnect;
	BT.BTTx.BT_Tx_Pointer = 0;
	BT.BTRx.BT_Rx_Pointer = 0;
}

/*******************************************************************************
�� �� ����BT_Init(void)
��    ������ʼ������ģ��(GPIO��UART5���ṹ��)
*******************************************************************************/
void BT_Init(void)
{	
	USART_InitTypeDef UART5_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// C��D��ʱ��
	RCC_AHB1PeriphClockCmd(BT_TX_GPIO_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(BT_RX_GPIO_RCC, ENABLE);
	// PC12 -> TX
	GPIO_InitStructure.GPIO_Pin = BT_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BT_TX_GPIO,&GPIO_InitStructure);
	// PD2 -> RX
	GPIO_InitStructure.GPIO_Pin = BT_RX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BT_RX_GPIO,&GPIO_InitStructure);
	// PC11 -> BT_Status
	GPIO_InitStructure.GPIO_Pin = BT_Status_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//��Ϊ���ӳɹ��Ǹߵ�ƽ
	GPIO_Init(BT_TX_GPIO,&GPIO_InitStructure);
	// ���ù�������
	GPIO_PinAFConfig(BT_TX_GPIO,BT_TX_PINSor,GPIO_AF_UART5);
	GPIO_PinAFConfig(BT_RX_GPIO,BT_RX_PINSor,GPIO_AF_UART5);
	// UART5ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	// UART5�ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// UART5��ʼ��
	USART_DeInit(UART5);
	UART5_InitStructure.USART_BaudRate = 115200;
	UART5_InitStructure.USART_WordLength = USART_WordLength_8b;
	UART5_InitStructure.USART_StopBits = USART_StopBits_1;
	UART5_InitStructure.USART_Parity = USART_Parity_No;
	UART5_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	UART5_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART5,&UART5_InitStructure);
	USART_Cmd(UART5,ENABLE);
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	// �ṹ���ʼ��
	BT_Struct_Init();
	// ����״̬
	RD_BT_Status();
}

/*******************************************************************************
�� �� ����RD_BT_Status(void)
��    ������ȡ����״̬�����µ�ȫ�ֽṹ��
*******************************************************************************/
void RD_BT_Status(void)
{
	if(GPIO_ReadInputDataBit(BT_TX_GPIO,BT_Status_PIN) == SET)
		BT.BTStatus = BT_Mode_Connected;
	else
		BT.BTStatus = BT_Mode_Noconnect;
}
/*******************************************************************************
�� �� ����BT_Send_Char(u8 Char)
��    ����ͨ����������һ���ַ�
���������
          pData���ַ����׵�ַ
          len���ַ�������
*******************************************************************************/
void BT_Send_Char(u8 Char)
{
	USART_SendData(BT_UART,Char);
	// �ȴ��������һ���ֽ�
	while(USART_GetFlagStatus(BT_UART,USART_FLAG_TXE) != SET);
}
/*******************************************************************************
�� �� ����BT_Send_String(uint8_t *pData,char len)
��    ����ͨ����������һ������Ϊlen���ַ���(��ʱδʹ�ýṹ������)
���������
          pData���ַ����׵�ַ
          len���ַ�������
*******************************************************************************/
void BT_Send_String(uint8_t *pData,char len)
{
	while(len--)
	{
		BT_Send_Char(*pData);
		// ָ���һ
		pData++;
	}
}
/*******************************************************************************
�� �� ����UART5_IRQHandler(void)
��    �����������ڽ����ж�
*******************************************************************************/
void UART5_IRQHandler(void)
{ 
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
		BT.BTRx.BT_Rx_Buf[BT.BTRx.BT_Rx_Pointer] = USART_ReceiveData(UART5);
	}
}