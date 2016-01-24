#include "includes.h"


RobotWspeed robotw;
float vx,vy,wz;    //�ٶȣ�����ÿ��   ���ٶȣ�����ÿ��

void WSpeed(float vx, float vy,float wz)    //�����ķ���˶�����
{
  
  robotw.speed0=(s32)(((vx-vy)+(LL1+LL2)*wz/550)/PI/R/2*1000);//0
  robotw.speed1=(s32)(((vx+vy)-(LL1+LL2)*wz/550)/PI/R/2*1000);//1
  robotw.speed2=(s32)(((vx-vy)-(LL1+LL2)*wz/550)/PI/R/2*1000);//2
  robotw.speed3=(s32)(((vx+vy)+(LL1+LL2)*wz/550)/PI/R/2*1000);//3
  
}


void SetSpeed(void)  
{	
	Motor_Control_0((s16)robotw.speed0);
	Motor_Control_1((s16)robotw.speed1);
	Motor_Control_2((s16)robotw.speed2);
	Motor_Control_3((s16)robotw.speed3);
}

void SetSpeed_0(void)  
{	
	Move_Motor_0((s32)robotw.speed0);
	Move_Motor_1((s32)robotw.speed1);
	Move_Motor_2((s32)robotw.speed2);
	Move_Motor_3((s32)robotw.speed3);
}

void stop(void)    //�ٶȸ�0�ͺ���
{
  
  WSpeed(0,0,0);
  SetSpeed();
}
