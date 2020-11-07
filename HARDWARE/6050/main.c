/*********************************************************************************
说明：只用到了VCC(5V),GND,SCL,SDA四个管脚。XDA和XCL是用来连接其他外部设备的
AD0是16位AD，可以输出状态值，但是本程序就是直接读取寄存器的值，所以这个没有必要；
INT是中断，这个貌似可以用在程序中，但是不太熟悉怎么操作。所用示波器为最熟悉的那一张。
就是4通道的。
*********************************************************************************/


#include"stm32f10x.h"
#include"delay.h"
#include"usart.h" /* printf函数定向输出到串口，所以必须包含这个文件 */
#include<stdio.h>  /* 因为用到了printf函数，所以必须包含这个文件 */
#include"mpu6050.h"
#include"i2c.h"
#include"Kalman_Filter.h"
#include"Tim.h"
#include"ocsctl.h"
 s16 Gyro_x;
 s16 Gyro_y;
 s16 Gyro_z;
 s16 Ayro_x;
 s16 Ayro_y;
 s16 Ayro_z;
 s16 TempC;
 float ag_x=0;
 float  ax;
 float  gx;
 float ag_y=0;
 float  ay;
 float  gy;
 float ag_z=0;
 float  az;
 float  gz;
 float  temp_c;
//extern float angle2, angle_dot; 
/**************使用飞思卡尔官方教程中的方法进行角度融合*************************/


int main(void)
{  
   
   SystemInit();
   delay_init(72);
   TIM3_Init();
   Initial_UART1(115200);
   Soft_I2C_Init();
   Init_MPU6050();
//  printf("\r\n初始化成功\r\n");
   while(1)
   {
//      UART1_ReportMotion(Ayro_x,Ayro_y,Ayro_z,Gyro_x,Gyro_y,Gyro_z,0,0,0);
//	  UART1_ReportIMU((int16_t)(az*10),(int16_t)(ag_z*10),0,0,0,0,100);
	  //UART1_ReportIMU(int16_t yaw,int16_t pitch,int16_t roll
//,int16_t alt,int16_t tempr,int16_t press,int16_t IMUpersec);

      OCS_displayData(ag_x,ag_y,ag_z,0);
	   delay_ms(20);
 
    }
  
}
