/**
  ******************************************************************************
  * @文件	PS_Dirver.c
  * @日期	2015-1-26
  * @说明	手柄驱动
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  * 使用的接口：
  *             DATA -> GPIOB3
  *             CMD -> GPIOB4
  *             ATT -> GPIOB5
  *             CLK -> GPIOB6
  *             ACK -> GPIOB7
  * 注：此PS手柄读取速度较慢，只能使用模拟SPI时序
  ******************************************************************************
  */

#include "includes.h"
#define		Pluse	200//经测试，PS手柄最大承受时钟频率为20kHz，当前约为13kHz(f1)

// 手柄结构体定义
PSTypeDef PS;

/*******************************************************************************
函 数 名：PS_Struct_Init(void)
描    述：初始化手柄结构体
*******************************************************************************/
void PS_Struct_Init(void)
{	
	for(int i = 0;i < 9;i++)
		PS.PS_Data[i] = 0;
}

/*******************************************************************************
函 数 名：Delay_PS(u16 time)
描    述：内部延时函数,仅内部调用
*******************************************************************************/
void Delay_PS(u16 time)
{
	volatile u16 tmp = time;
	while(tmp--);
}

/*******************************************************************************
函 数 名：PS_Init(void)
描    述：PS手柄连接IO口初始化(GPIO、UART5、结构体)
*******************************************************************************/
void PS_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(PS_GPIO_RCC, ENABLE);

	/* GPIO Ports Clock Enable */
	RCC_AHB1PeriphClockCmd(PS_GPIO_RCC, ENABLE);

	/*PS_CMD_PIN、PS_ATT_PIN、PS_CLK_PIN输出模式 */
	GPIO_InitStructure.GPIO_Pin = PS_CMD_PIN|PS_ATT_PIN|PS_CLK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(PS_GPIO, &GPIO_InitStructure);

	/*PS_DATA_PIN、PS_ACK_PIN输入模式 */
	GPIO_InitStructure.GPIO_Pin = PS_DATA_PIN|PS_ACK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  //浮空上拉输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(PS_GPIO, &GPIO_InitStructure);
	
	PS_Struct_Init();
	
	PS_CMD_HIGH();
	PS_ATT_HIGH();
	PS_CLK_HIGH();
	Delay_PS(10000);
}

/*******************************************************************************
函 数 名：u8 SPI_WR(u8 WR_CMD)
描    述：SPI读写模拟函数
输入参数：
          WR_CMD：SPI写数据
返 回 值：SPI读取的数据
*******************************************************************************/
u8 SPI_WR(u8 WR_CMD)
{
	u8 bit_ctr;

   	for(bit_ctr = 0 ; bit_ctr < 8 ; bit_ctr ++)
   	{
   		// 从最低位的值
		if(WR_CMD & 0x01)
			PS_CMD_HIGH();
		else
			PS_CMD_LOW();
		// 右移一位
		WR_CMD = (WR_CMD >> 1);

		// 时钟信号拉低
		PS_CLK_LOW();
		Delay_PS(Pluse/2);
		// 读取MISO的数据
		WR_CMD = WR_CMD | (PS_DATA_RD() << 7);
		Delay_PS(Pluse/2);

		// 时钟信号拉高
		PS_CLK_HIGH();
		Delay_PS(Pluse);
   	}
	Delay_PS(Pluse);
    return(WR_CMD);
}

/*******************************************************************************
函 数 名：PS_Digital_Mode(void)
描    述：PS的数字模式
*******************************************************************************/
void PS_Digital_Mode(void)
{
	char D1 = 0;
	if((PS.PS_Data[2] & SLCT) == 0)
      D1 = 1;
//		printf("SLCT DOWN!\n");
	if((PS.PS_Data[2] & STRT) == 0)
      D1 = 1;
//		printf("STRT DOWN!\n");
	if((PS.PS_Data[2] & UP) == 0)
      D1 = 1;
//		printf("UP DOWN!\n");
	if((PS.PS_Data[2] & RGHT) == 0)
      D1 = 1;
//		printf("RGHT DOWN!\n");
	if((PS.PS_Data[2] & DOWN) == 0)
      D1 = 1;
//		printf("DOWN DOWN!\n");
	if((PS.PS_Data[2] & LEFT) == 0)
      D1 = 1;
//		printf("LEFT DOWN!\n");

	if((PS.PS_Data[3] & L2) == 0)
      D1 = 1;
//		printf("L2 DOWN!\n");
	if((PS.PS_Data[3] & R2) == 0)
      D1 = 1;
//		printf("R2 DOWN!\n");
	if((PS.PS_Data[3] & R1) == 0)
	  D1 = 1;
//		printf("R1 DOWN!\n");
	if((PS.PS_Data[3] & L1) == 0)
		D1 = 1;
//		printf("L1 DOWN!\n");
	if((PS.PS_Data[3] & Triangle) == 0)
		D1 = 1;
//		printf("Triangle DOWN!\n");
	if((PS.PS_Data[3] & Circular) == 0)
		D1 = 1;
//		printf("Circular DOWN!\n");
	if((PS.PS_Data[3] & Cross) == 0)
		D1 = 1;
//		printf("Cross DOWN!\n");
	if((PS.PS_Data[3] & Square) == 0)
		D1 = 1;
//		printf("Square DOWN!\n");
	if(D1)
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

/*******************************************************************************
函 数 名：PS_Analog_Red(void)
描    述：PS的模拟红灯模式
*******************************************************************************/
void PS_Analog_Red(void)
{
	char D1 = 0;
	if((PS.PS_Data[2] & SLCT) == 0)
      D1 = 1;
//		printf("SLCT DOWN!\n");
	if((PS.PS_Data[2] & STRT) == 0)
      D1 = 1;
//		printf("STRT DOWN!\n");
	if((PS.PS_Data[2] & UP) == 0)
      D1 = 1;
//		printf("UP DOWN!\n");
	if((PS.PS_Data[2] & RGHT) == 0)
      D1 = 1;
//		printf("RGHT DOWN!\n");
	if((PS.PS_Data[2] & DOWN) == 0)
      D1 = 1;
//		printf("DOWN DOWN!\n");
	if((PS.PS_Data[2] & LEFT) == 0)
      D1 = 1;
//		printf("LEFT DOWN!\n");

	if((PS.PS_Data[3] & L2) == 0)
      D1 = 1;
//		printf("L2 DOWN!\n");
	if((PS.PS_Data[3] & R2) == 0)
      D1 = 1;
//		printf("R2 DOWN!\n");
	if((PS.PS_Data[3] & R1) == 0)
	  D1 = 1;
//		printf("R1 DOWN!\n");
	if((PS.PS_Data[3] & L1) == 0)
		D1 = 1;
//		printf("L1 DOWN!\n");
	if((PS.PS_Data[3] & Triangle) == 0)
		D1 = 1;
//		printf("Triangle DOWN!\n");
	if((PS.PS_Data[3] & Circular) == 0)
		D1 = 1;
//		printf("Circular DOWN!\n");
	if((PS.PS_Data[3] & Cross) == 0)
		D1 = 1;
//		printf("Cross DOWN!\n");
	if((PS.PS_Data[3] & Square) == 0)
		D1 = 1;
//		printf("Square DOWN!\n");
	
	if(D1)
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

/*******************************************************************************
函 数 名：Get_PS_Data(void)
描    述：获取PS手柄数据，存入PS.PS_Data
*******************************************************************************/
void Get_PS_Data(void)
{	
	PS_ATT_LOW();
	Delay_PS(1000);
	SPI_WR(0x01);
	PS.PS_Data[0] = SPI_WR(0x42);
	PS.PS_Data[1] = SPI_WR(0x55);
	PS.PS_Data[2] = SPI_WR(0x55);
	PS.PS_Data[3] = SPI_WR(0x55);
	PS.PS_Data[4] = SPI_WR(0x55);
	PS.PS_Data[5] = SPI_WR(0x55);
	PS.PS_Data[6] = SPI_WR(0x55);
	PS.PS_Data[7] = SPI_WR(0x55);
	PS.PS_Data[8] = SPI_WR(0x55);
	PS_ATT_HIGH();
}