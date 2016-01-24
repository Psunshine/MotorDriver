/**
  ******************************************************************************
  * @�ļ�	SendPS.c
  * @����	2015-1-26
  ******************************************************************************
  * ������ͨ��ѧ-ͨ��1208-��С��
  *
  * ˵��:	IAR�汾:7.20.2.7314
  *      	���ļ��汾:��׼�� V1.3.0
  * �ļ�����:	Tab Size:4
  * �Զ�����:	Body:4
  ******************************************************************************
  * ����������
  *           ��ȡ�ֱ����ݣ�ͨ���������͸�����
  ******************************************************************************
  */
#include "includes.h"

u8 head_end[]={0x55};
u8 A2D[]={0x41};
u8 FF_Flag = 1;
u8 count = 0;//����ֹͣ�źŵļ���ֵ

void Get_Data_Send(void)
{
	// ��ȡ�ֱ�����
	Get_PS_Data();
	
	// �ж��ֱ���������ģʽ
	switch(CONL.PS->PS_Data[0])
	{
		// ����ģʽ
		case Digital_Mode:
			PS_Digital_Mode();
			// �ж������Ƿ���Ч(�а�������)����FF_Flag=1ʱҲ�����
			// Ŀ����Ϊ���ڰ����ɿ���෢�ͼ���ֹͣ���ݣ���ֹ����©����֡
			if(FF_Flag||(CONL.PS->PS_Data[2] != 0xff)||(CONL.PS->PS_Data[3] != 0xff))
			{
				// ������Ч����
				BT_Send_String(CONL.PS->PS_Data,1);// ��ͷ
				BT_Send_String(CONL.PS->PS_Data+2,2);// ��Ч����
				// ���Ͱ�β
				BT_Send_String(head_end,1);
				
				// count���ڷ���ֹͣ���ݼ�����FF_FlagΪ��־λ
				if((count < 10)&&(CONL.PS->PS_Data[2] == 0xff)\
					&&(CONL.PS->PS_Data[3] == 0xff))//û����Ч���ݣ����־λ
				{
					count++;
					if(count >= 10)
						FF_Flag = 0;
				}
				else
				{
					FF_Flag = 1;
					count = 0;
				}
			}
			break;
		// ģ��ģʽ��������ģʽ���ƣ�����׸��
		case Analog_Red:
			PS_Analog_Red();
			
			if(((CONL.PS->PS_Data[3] & R1) != 0))
			{
				if(FF_Flag||(CONL.PS->PS_Data[2] != 0xff)||\
				   (CONL.PS->PS_Data[3] != 0xff))// ����Ч����
				{
					BT_Send_String(A2D,1);
					BT_Send_String(CONL.PS->PS_Data+2,2);
					BT_Send_String(head_end,1);
					if((count < 10)&&(CONL.PS->PS_Data[2] == 0xff)\
						&&(CONL.PS->PS_Data[3] == 0xff))
					{
						count++;
						if(count >= 10)
							FF_Flag = 0;
					}
					else
					{
						FF_Flag = 1;
						count = 0;
					}
				}
			}
			else
			{
				BT_Send_String(CONL.PS->PS_Data,1);
				BT_Send_String(CONL.PS->PS_Data+2,6);
				BT_Send_String(head_end,1);
			}
			break;
		default:
		break;
	}
}
