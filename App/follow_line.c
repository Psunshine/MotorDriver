#include "follow_line.h"


typedef struct 
{
	int Front_Data_Min;
        int Front_Data_Max;
        int Behind_Data_Min;
        int Behind_Data_Max;
}light_data;

light_data Now;
light_data Last;
u8 data_input[48];
  int T ;//��ֵ 
int flag;
int min_number_last;
int max_number_last;
int min_number_now;
int max_number_now;
int min_number;
int max_number;
int count_last;
int count_now;

/*************************************************************************
         otsuThreshold(u8* data_in,u8 *dataout1,u8 *dataout2)
���������ݵĶ�̬��ֵ����
���������u8* data_in
���������u8 *dataout1,u8 *dataout2
*************************************************************************/

void otsuThreshold(u8* data_in,u8 *dataout1,u8 *dataout2)
{
  
         T=0;

	int height = 48;
	int width = 1;
	double gSum0;//��һ��Ҷ���ֵ  
	double gSum1;//�ڶ���Ҷ���ֵ  
	double N0 = 0;//ǰ��������  
	double N1 = 0;//����������  
	double u0 = 0;//ǰ������ƽ���Ҷ�  
	double u1 = 0;//��������ƽ���Ҷ�  
	double w0 = 0;//ǰ�����ص���ռ����ͼ��ı���Ϊ��0  
	double w1 = 0;//�������ص���ռ����ͼ��ı���Ϊ��1  
	double u = 0;//��ƽ���Ҷ�  
	double tempg = -1;//��ʱ��䷽��   ���Ը�
	double g = 100;//��䷽��  
	double Histogram[256] = { 0 };// = new double[256];//�Ҷ�ֱ��ͼ  
	double N = width*height;//��������  
	//int max_number,min_number;
        
       
	for (int row = 0; row<height; row++)
	{//����ֱ��ͼ  
		//uchar* grayimgptr = grayimg.ptr<uchar>(row);

	
          double temp = data_in[row];
			temp = temp<0 ? 0 : temp;
			temp = temp>255 ? 255 : temp;
			Histogram[(int)temp]++;
		
	}
	//������ֵ  
	for (int i = 0; i<256; i++)
	{
		gSum0 = 0;
		gSum1 = 0;
		N0 += Histogram[i];//ǰ��������
		N1 = N - N0;//����������  
		if (0 == N1)break;//������ǰ�������ص�ʱ������ѭ��  
		w0 = N0 / N;//ǰ�����ص���ռ����ͼ��ı���Ϊ��0 
		w1 = 1 - w0;//ǰ�����ص���ռ����ͼ��ı���Ϊ��1
		for (int j = 0; j <= i; j++)
		{
			gSum0 += j*Histogram[j];
		}//ǰ���Ҷ��ܺ�
		u0 = gSum0 / N0;//ǰ���ҶȾ�ֵ
		for (int k = i + 1; k<256; k++)
		{
			gSum1 += k*Histogram[k];
		}//�����Ҷ��ܺ�
		u1 = gSum1 / N1;//�����ҶȾ�ֵ
		//u = w0*u0 + w1*u1;  //��ƽ���Ҷ�
		g = w0*w1*(u0 - u1)*(u0 - u1);
		if (tempg<g)
		{
			tempg = g;
			T = i;
		}
	}
	
        for(int i=0;i<47;i++)
        {
          if(data_in[i]<T)
          {
            data_input[i]=0;
  
          }
          else 
          {
            data_input[i]=1; 
          }
        }
        
         flag=0;
         count_last=0;
         count_now=0;
        for(int j=0;j<48;j++)
          {
           
            if((flag==0)&&((data_input[j+1]-data_input[j])==-1))
            {
              min_number_now=j+1;
              flag=1;
            }
             else;
             if((flag==1)&&((data_input[j+1]-data_input[j])==0))
              {
                count_now++;
              }
           else;
           if((flag==1)&&((data_input[j+1]-data_input[j])==1))
            {
              max_number_now = j;
              flag = 2;
            }
            else ;
            if((j < 48)&&(flag == 2))
            {
              flag = 0;
              if(count_now > count_last)
              {
              min_number_last = min_number_now;
              max_number_last = max_number_now;
              count_last = count_now;
              count_now=0;
              }
              else ;
            }
            min_number = min_number_last;
            max_number = max_number_last;
          }
          
        
          *dataout1 = min_number;
          *dataout2 = max_number;
          
        


}


/*************************************************************************
        dis_angle(float* distance,float* angle )
�������Ƕ���ƫ�����Ķ�ȡ����
���������
���������float* distance,float* angle
*************************************************************************/
void dis_angle(float* distance,float* angle ) //ͨ��ǰ��Ѳ�߰��ǵ����Сֵ����ű�ǵ�Ƚϣ��ó��ǶȺ�ƫ����
{
    u8 a,b,c,d;
  otsuThreshold(buffer_blue_front,&a,&b);      // ǰ��Ѳ�߰����ֵ����Сֵ
  Now.Front_Data_Min=a;
  Now.Front_Data_Max=b;
//  otsuThreshold(buffer_blue_behind,&c,&d);     // ����Ѳ�߰����ֵ����Сֵ
//  Now.Behind_Data_Min=c;
//  Now.Behind_Data_Max=d;
//  if(abs(Now.Front_Data_Min-Last.Front_Data_Min)<5)   //�Ƚ���һ��������ֵ
//  {                                                                       //����Ƕ�
//    *angle=atan((Now.Front_Data_Min+Now.Front_Data_Max-Now.Behind_Data_Min-Now.Behind_Data_Max)*L/2*L_distance);
//                                                                          //����ƫ����
//    *distance=(Now.Front_Data_Min+Now.Front_Data_Max-Now.Behind_Data_Min-Now.Behind_Data_Max)/2-middle_number;
//  }
//  else 
//  Last.Front_Data_Min=Now.Front_Data_Min;
//  Last.Front_Data_Max=Now.Front_Data_Max;
//  Last.Behind_Data_Min=Now.Behind_Data_Min;
//  Last.Behind_Data_Max=Now.Behind_Data_Max;
}