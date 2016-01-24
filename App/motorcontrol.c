#include "motorcontrol.h"

ST_PID Speed_PID_0={1,   1,   0.24, 0,0};
ST_PID Speed_PID_1={1.1, 1,   0.235, 0,0};
ST_PID Speed_PID_2={1,   1,   0.24, 0,0};
ST_PID Speed_PID_3={1,   1,   0.24, 0,0};

//ST_PID Speed_PID_4={1,   0.2, 0, 0,0};//{1,0.2,0,0,0}

//s32 EXP_Angle=0;

typedef struct Control
{
	float Speed;
	float Speed_error;
	int Encoder_number;  
	float Motor_out;
	float Error_Integral;
}Control;


int look_encoder;
int Pwm_Out_0;
int Pwm_Out_1;
int Pwm_Out_2;
int Pwm_Out_3;


Control Now_0;  //��ǰ����
Control Now_1;  //��ǰ����
Control Now_2;  //��ǰ����
Control Now_3;  //��ǰ����

Control Past_0;  //��һ�β���
Control Past_1;  //��һ�β���
Control Past_2;  //��һ�β���
Control Past_3;  //��һ�β���

s32 Speed_exp_0;
s32 Speed_exp_1;
s32 Speed_exp_2;
s32 Speed_exp_3;

float PIDjisuan(ST_PID *Speed_PID, float ThisError )
{
    float pError,dError,iError, temp;	
    pError = ThisError-Speed_PID->LastError; 
    iError = ThisError;
    dError = ThisError-2*(Speed_PID->LastError)+Speed_PID->PreError;
    
    //�������� 
    temp=Speed_PID->KP*pError + Speed_PID->KI*iError+Speed_PID->KD*dError;  //����
    //�洢��������´�����
    Speed_PID->PreError  =Speed_PID->LastError;
    Speed_PID->LastError = ThisError;
    return temp;
}

void Motor_Control_0(s16 i)
{  
	Speed_exp_0=i;
//    if(Speed_exp_0==0)
//    { Move_Motor_0(0); }
//    else
//	{
	Now_0.Speed=tmp_0;
	Now_0.Speed_error=Speed_exp_0-Now_0.Speed;//�������ٶȱȽ�
	if((Now_0.Speed_error>1)||(Now_0.Speed_error<-1))    //514/300=1.713
	{  
		static float Pwm_Out_last_0=0;
		
		Now_0.Motor_out=PIDjisuan(&Speed_PID_0,Now_0.Speed_error);
		
		Past_0.Speed_error=Now_0.Speed_error;
		
		Past_0.Motor_out=Now_0.Motor_out;
		
		Past_0.Error_Integral=Now_0.Error_Integral;
		
		Past_0.Speed=Now_0.Speed;
		
		Pwm_Out_0=(s32)(Now_0.Motor_out+Pwm_Out_last_0);
		
		if(Pwm_Out_0>Motor_out_max)//���������Сֵ ��PID����֮�� ��ֹPID������������ֵ������Χ
		{
			Pwm_Out_0=Motor_out_max;
		}	
		if(Pwm_Out_0<Motor_out_min)
		{
			Pwm_Out_0=Motor_out_min;
		}
		Pwm_Out_last_0=Pwm_Out_0;
		Move_Motor_0(Pwm_Out_0);
		
	}
}
void Motor_Control_1(s16 i)
{ 
  Speed_exp_1=i;
//  if(Speed_exp_1==0)
//  { Move_Motor_1(0);}
//  else
//  {
	 Now_1.Speed=tmp_1;
	 Now_1.Speed_error=Speed_exp_1-Now_1.Speed;//�������ٶȱȽ�
	 if((Now_1.Speed_error>1)||(Now_1.Speed_error<-1))     //507/300=1.69
	 {   static float Pwm_Out_last_1=0;
	     Now_1.Motor_out=PIDjisuan(&Speed_PID_1,Now_1.Speed_error);
	     Past_1.Speed_error=Now_1.Speed_error;
	     Past_1.Motor_out=Now_1.Motor_out;
	     Past_1.Error_Integral=Now_1.Error_Integral;
	     Past_1.Speed=Now_1.Speed;
	     Pwm_Out_1=(s32)(Now_1.Motor_out+Pwm_Out_last_1);
	     if(Pwm_Out_1>Motor_out_max)//���������Сֵ ��PID����֮�� ��ֹPID������������ֵ������Χ
	     {
		   Pwm_Out_1=Motor_out_max;
	     }	
	     if(Pwm_Out_1<Motor_out_min)
	     {
		   Pwm_Out_1=Motor_out_min;
	     }
	     Pwm_Out_last_1=Pwm_Out_1;
	     Move_Motor_1(Pwm_Out_1);
	
  }
}
void Motor_Control_2(s16 i)
{ 
  Speed_exp_2=i;
//  if(Speed_exp_2==0)
//  { Move_Motor_2(0);}
//  else
//  {
	 Now_2.Speed=-tmp_2;
	 Now_2.Speed_error=Speed_exp_2-Now_2.Speed;//�������ٶȱȽ�
	 if((Now_2.Speed_error>1)||(Now_2.Speed_error<-1))     //507/300=1.69
	 {   static float Pwm_Out_last_2=0;
	     Now_2.Motor_out=PIDjisuan(&Speed_PID_2,Now_2.Speed_error);
	     Past_2.Speed_error=Now_2.Speed_error;
	     Past_2.Motor_out=Now_2.Motor_out;
	     Past_2.Error_Integral=Now_2.Error_Integral;
	     Past_2.Speed=Now_2.Speed;
	     Pwm_Out_2=(s32)(Now_2.Motor_out+Pwm_Out_last_2);
	     if(Pwm_Out_2>Motor_out_max)//���������Сֵ ��PID����֮�� ��ֹPID������������ֵ������Χ
	     {
		   Pwm_Out_2=Motor_out_max;
	     }	
	     if(Pwm_Out_2<Motor_out_min)
	     {
		   Pwm_Out_2=Motor_out_min;
	     }
	     Pwm_Out_last_2=Pwm_Out_2;
	     Move_Motor_2(Pwm_Out_2);
//	}
	
  }
}
void Motor_Control_3(s16 i)
{ 
  Speed_exp_3=i;
//  if(Speed_exp_3==0)
//  {Move_Motor_3(0);}
//  else
//  {
	 Now_3.Speed=-tmp_3;
	 Now_3.Speed_error=Speed_exp_3-Now_3.Speed;//�������ٶȱȽ�
	 if((Now_3.Speed_error>1)||(Now_3.Speed_error<-1))     
	 {   static float Pwm_Out_last_3=0;
	     Now_3.Motor_out=PIDjisuan(&Speed_PID_3,Now_3.Speed_error);
	     Past_3.Speed_error=Now_3.Speed_error;
	     Past_3.Motor_out=Now_3.Motor_out;
	     Past_3.Error_Integral=Now_3.Error_Integral;
	     Past_3.Speed=Now_3.Speed;
	     Pwm_Out_3=(s32)(Now_3.Motor_out+Pwm_Out_last_3);
	     if(Pwm_Out_3>Motor_out_max)//���������Сֵ ��PID����֮�� ��ֹPID������������ֵ������Χ
	     {
		   Pwm_Out_3=Motor_out_max;
	     }	
	     if(Pwm_Out_3<Motor_out_min)
	     {
		   Pwm_Out_3=Motor_out_min;
	     }
	     Pwm_Out_last_3=Pwm_Out_3;
	     Move_Motor_3(Pwm_Out_3);
	//}
	
  }
}