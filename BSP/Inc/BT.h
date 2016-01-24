/**
  ******************************************************************************
  * @�ļ�	BT.h
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
#pragma once
#include "includes.h"

// ����ʱ��
#define		BT_UART			UART5
#define		BT_UART_NVIC	UART5_IRQn
#define		BT_Periph_RCC	RCC_APB1Periph_UART5
#define		BT_TX_GPIO_RCC	RCC_AHB1Periph_GPIOC
#define		BT_RX_GPIO_RCC	RCC_AHB1Periph_GPIOD
// �������ӵ�GPIO��
#define		BT_TX_GPIO		GPIOC
#define		BT_RX_GPIO		GPIOD
#define		BT_TX_PIN		GPIO_Pin_12
#define		BT_RX_PIN		GPIO_Pin_2
#define		BT_Status_PIN	GPIO_Pin_11
#define		BT_TX_PINSor	GPIO_PinSource12
#define		BT_RX_PINSor	GPIO_PinSource2


/** 
  * @˵�� ����״̬����
  */   
typedef enum
{ 
	BT_Mode_Noconnect		= 0x00, /*!<����δ���� */
	BT_Mode_Connected		= 0x01, /*!<�����ɹ�����*/
}BTStatusTypeDef;

/** 
  * @˵�� �������ͽṹ�嶨��
  */   
typedef struct
{
	u8* BT_Tx_Buf;
	u8 BT_Tx_Pointer;
}BTTxTypeDef;

/** 
  * @˵�� �������սṹ�嶨��
  */   
typedef struct
{
	u8 BT_Rx_Buf[512];
	u8 BT_Rx_Pointer;
}BTRxTypeDef;

/** 
  * @˵�� �����ṹ�嶨��
  */   
typedef struct
{
	BTStatusTypeDef BTStatus;
	BTTxTypeDef 	BTTx;
	BTRxTypeDef 	BTRx;
}BTTypeDef;

extern BTTypeDef BT;

void BT_Init(void);
void RD_BT_Status(void);
void BT_Send_String(uint8_t *pData,char len);
