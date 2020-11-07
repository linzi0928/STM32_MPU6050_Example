#ifndef __MPU6050_H
#define __MPU6050_H 
#include "stm32f10x.h"
#include "stm32f10x_it.h"
/*******初始化MPU3050，根据需要请参考pdf进行修改************************/
/**********************************************************************
精度说明：±250°/s      131	 LSB/°/s
          ±500°/s      65.5  LSB/°/s
		  ±1000°/s     32.8  LSB/°/s
		  ±2000°/s     16.4  LSB/°/s
		  ±2g          16384 LSB/mg
		  ±4g          8192  LSB/mg
		  ±8g          4096  LSB/mg
		  ±16g         2048  LSB/mg
		  5V供电
*********************************************************************/

// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG6050		   0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1b	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1c   	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B	//加速度相关的寄存器
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43         //角度相关的寄存器
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	MPU6050_Addr   0xD0	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
/************************角速度加速度偏移值*************************/
#define  Gx_offset   0
#define  Gy_offset	 0
#define  Gz_offset	 -1

#define   Ax_offset   303
#define   Ax_Max	  8444
#define   Ax_Min 	  -7662

#define  Ay_offset    60    	  
#define  Ay_Max	       8204
#define  Ay_Min		  -8647

#define   Az_offset   -519
#define   Az_Max	   7921
#define   Az_Min 	  -8960


 void Init_MPU6050(void);
 short getAccX(void);
 short getAccY(void);
 short getAccZ(void);

//获取陀螺仪的值
 short getGyroX(void);
 short getGyroY(void);
 short getGyroZ(void);

//温度
 short getTemperature(void);

void delay5ms(void);
//void READ_MPU6050(void);
u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
u8 Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);

#endif
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
  u8 count=0;
