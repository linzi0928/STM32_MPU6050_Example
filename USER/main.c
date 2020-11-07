/*************************************************************************************************************
舸轮综合电子工作室(GIE工作室)        出品
Gearing Interated Electronics Studio

MPU6050示例程序
来自魔方2反馈单片机程序
除main.c外几乎均来自互联网

关注B站UP主：GIE工作室 获得更多视频资源及动态

2018-2-28第一版
版权所有 禁止未经允许用于任何商业用途！
*************************************************************************************************************/
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "timer.h"
#include "Tim.h"
#include "i2c.h"
extern void Init_MPU6050(void);
extern void Refresh6050(void);
extern float ag_x;
extern float ag_y;
extern float ag_z;
extern float  temp_c;
extern float abs6050(float u);
 int main(void)
 {		 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 	 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);   
	//delay_init();	    	 //延时函数初始化	  
	 delay_ms(100);	
	NVIC_Configuration(); 
	Soft_I2C_Init();//软件IIC初始化，用于6050交换信息
 	Init_MPU6050();//初始化加速度计6050
	uart1_init(9600);
		while(1)
		{	  	
			delay_ms(100);			
			Refresh6050();//获取6050加速度信息，并积分为角度
			printf("Angle_X:%3.2f", ag_x);//串口打印传感器信息
			printf(" Angle_Y:%3.2f", ag_y);
			printf(" Angle_Z:%3.2f", ag_z);
			printf(" Temp:%3.2f\n", temp_c);
		}     


}


