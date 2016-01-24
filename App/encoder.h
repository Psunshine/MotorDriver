/*******************************************************************************
�ļ�����encoder.c
��  �ܣ�����
˵  ����TIM1, PA8, PA9
        TIM3��PA6��PA7
        IIM5��PA0��PA1
*******************************************************************************/
//#include "main.h"
#include "includes.h"

#ifndef ENCODER_H
#define ENCODER_H

#define ENC_TS                      20                          // ��������������� ms
#define ENC_PPR                     (u8)16 //((u16)1000)                 // ����������

/*******************************������X��غ궨��******************************/
// ����
#define ENC_X_TIM                   TIM9
#define ENC_X_PORT                  GPIOE
#define ENC_X_A                     GPIO_Pin_5
#define ENC_X_B                     GPIO_Pin_6
// ����
#define ENC_X_AF					GPIO_AF_TIM9
#define ENC_X_A_PinSource      		GPIO_PinSource5
#define ENC_X_B_PinSource      		GPIO_PinSource6
// ʱ��
//#define ENC_X_Enable()					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM9 ,ENABLE)
//#define ENC_X_Port_Enable()				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE)
/*******************************������X��غ궨��******************************/

/*******************************������Y��غ궨��******************************/
// ����
#define ENC_Y_TIM                   TIM12
#define ENC_Y_PORT                  GPIOB
#define ENC_Y_A                     GPIO_Pin_14
#define ENC_Y_B                     GPIO_Pin_15
// ����
#define ENC_Y_AF					GPIO_AF_TIM12
#define ENC_Y_A_PinSource      		GPIO_PinSource14
#define ENC_Y_B_PinSource      		GPIO_PinSource15
// ʱ��
//#define ENC_Y_Enable()					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12 ,ENABLE)
//#define ENC_Y_Port_Enable()				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE)
/*******************************������Y��غ궨��******************************/

#define ENC_PORT_0                  GPIOA 
#define ENC_0_A                     GPIO_Pin_5                  //A5
#define ENC_0_B                     GPIO_Pin_3                  //B3
#define ENC_TIM_0                   TIM2                        // TIM3����0�ŵ����������Ԫ
#define ENC_PORT_00                  GPIOB

#define ENC_PORT_1                  GPIOD
#define ENC_1_A                     GPIO_Pin_12  
#define ENC_1_B                     GPIO_Pin_13  
#define ENC_TIM_1                   TIM4                        // TIM5����1�ŵ����������Ԫ

#define ENC_PORT_2                  GPIOA
#define ENC_2_A                     GPIO_Pin_7  
#define ENC_2_B                     GPIO_Pin_6  
#define ENC_TIM_2                   TIM3                       // TIM1����2�ŵ����������Ԫ   


#define ENC_PORT_3                  GPIOA
#define ENC_3_A                     GPIO_Pin_0
#define ENC_3_B                     GPIO_Pin_1  
#define ENC_TIM_3                   TIM5                       // TIM4����3�ŵ����������Ԫ   

#define ENC_COEF_0                  ((float)(pi*52/512/62/4))    // ���߾���������Ȧ���Ļ���ϵ��//62
#define ENC_COEF_1                  ((float)(pi*52/512/62/4))    // ���߾���������Ȧ���Ļ���ϵ��
#define ENC_COEF_2                  ((float)(pi*52/512/62/4))    // ���߾���������Ȧ���Ļ���ϵ��
#define ENC_COEF_3                  ((float)(pi*52/512/62/4))    // ���߾���������Ȧ���Ļ���ϵ��
#define ENC_COEF                    ((float)(159.5929f/4000))    // A1��ʵ�ʲ���ϵ�� ���߾���������Ȧ���Ļ���ϵ��


#define   RY  70.83
#define   RX  37.98
#define angle_x  0.0069
#define angle_y  0.0061
  
void ENC_Init(void);
void Encoder_X_Init(void);
void Encoder_Y_Init(void);
void ENC_Read(void);
void Encoder_0_Init(void);
void Encoder_1_Init(void);
void Encoder_2_Init(void);
void Encoder_3_Init(void);
void Encoder_Start(void);
extern int Encoder_Get_CNT(void);
extern  float x_0,x_1,x_2;       // ���̼������Ǽ���õ��ĳ�����λ��
extern s16 tmp_0,tmp_1,tmp_2,tmp_3;
extern s16 gb_Y,gb_X;
typedef struct
{
   float x,y;
}position;

#endif  
