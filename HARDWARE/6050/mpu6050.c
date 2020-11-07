#include"i2c.h"
#include"mpu6050.h"


u8  Single_Write(unsigned char SlaveAddress, unsigned char REG_Address, unsigned char REG_data)		     
{
  	if(!I2C_Start())
	   return 0;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
  //  if(!I2C_WaitAck()){I2C_Stop(); return 0;}
	I2C_WaitAck();	
    I2C_SendByte(REG_Address);   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
	return 1;
}

u8 Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{  
    u8 REG_data;     	
	I2C_Start();
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    I2C_WaitAck();
	I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
	I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();
    REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
	return REG_data;

}
void Init_MPU6050(void)
{
//	Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x80);//复位
//	delay5ms();
	Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x00);
    delay5ms();	//解除休眠状态
	Single_Write(MPU6050_Addr,SMPLRT_DIV, 0x07);
	delay5ms();//采样速率为	125Hz
	Single_Write(MPU6050_Addr,CONFIG6050, 0x06);
	delay5ms();	 //5Hz带宽，FS=1Kｈｚ
	Single_Write(MPU6050_Addr,GYRO_CONFIG, 0x18);
	delay5ms(); //陀螺仪检测范围2000度/秒  ，16.4LSB
	Single_Write(MPU6050_Addr,ACCEL_CONFIG, 0x08);
	delay5ms();  //加速器检测范围4G
}

short getAccX(void)
{
	short AccX = 0;
	char AccXH = 0 , AccXL = 0;

	AccXH = Single_Read( MPU6050_Addr, ACCEL_XOUT_H );
	AccXL = Single_Read( MPU6050_Addr , ACCEL_XOUT_L );

	AccX = (AccXH<<8)|AccXL;

	return AccX;
}

short getAccY(void)
{
	short AccY = 0;
	char AccYH = 0 , AccYL = 0;

	AccYH = Single_Read( MPU6050_Addr, ACCEL_YOUT_H );
	AccYL = Single_Read( MPU6050_Addr, ACCEL_YOUT_L );

	AccY = (AccYH<<8)|AccYL;

	return AccY;
}

short getAccZ(void)
{
	short AccZ = 0;
	char AccZH = 0 , AccZL = 0;

	AccZH = Single_Read( MPU6050_Addr , ACCEL_ZOUT_H );
	AccZL = Single_Read( MPU6050_Addr, ACCEL_ZOUT_L );

	AccZ = (AccZH<<8)|AccZL;

	return AccZ;
}

short getGyroX(void)
{
	short GyroX = 0;
	char GyroXH = 0 , GyroXL = 0; 
	
	GyroXH = Single_Read( MPU6050_Addr, GYRO_XOUT_H );
	GyroXL = Single_Read( MPU6050_Addr , GYRO_XOUT_H );
	
	GyroX = (GyroXH<<8)|GyroXL;
	
	return GyroX;	
}

short getGyroY(void)
{
   	short GyroY = 0;
	char GyroYH = 0 , GyroYL = 0; 
	
	GyroYH = Single_Read( MPU6050_Addr , GYRO_YOUT_H );
	GyroYL = Single_Read( MPU6050_Addr , GYRO_YOUT_H );
	
	GyroY = (GyroYH<<8)|GyroYL;
	
	return GyroY;	
}

short getGyroZ(void)
{
   	short GyroZ = 0;
	char GyroZH = 0 , GyroZL = 0; 
	
	GyroZH = Single_Read( MPU6050_Addr , GYRO_ZOUT_H );
	GyroZL = Single_Read( MPU6050_Addr , GYRO_ZOUT_H );
	
	GyroZ = (GyroZH<<8)|GyroZL;
	
	return GyroZ;	
}

short getTemperature(void)
{
 	short temperature = 0;
	char temperatureH = 0 , temperatureL = 0;

	temperatureH = Single_Read( MPU6050_Addr , TEMP_OUT_H );
	temperatureL = Single_Read( MPU6050_Addr , TEMP_OUT_L );

	temperature = (temperatureH<<8)|temperatureL;

	return temperature;
}

void delay5ms(void)
{
		
   u16 i=1000;  
   while(i) 
   { 
     i--; 
   }  
}



void Refresh6050(void)
{  

//   if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//  {
//      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
     Gyro_x=getGyroX();  	   //X轴数据
	 Gyro_y=getGyroY();  	   //X轴数据
	 Gyro_z=getGyroZ();  	   //X轴数据

     Ayro_x=getAccX();  	   //x轴数据 
  	 Ayro_y=getAccY();  	   //y轴数据 
	 Ayro_z=getAccZ();  	   //z轴数据

	 TempC=getTemperature();
	 
	 
//	 ax=atan(Ayro_x/sqrt(Ayro_z*Ayro_z+Ayro_y*Ayro_y))*180/3.14;
     ax=(Ayro_x - Ax_offset )*180.0/(Ax_Max-Ax_Min);
     gx=(Gyro_x-Gx_offset)*1.0/16.4;
     ag_x = ag_x + (((ax - ag_x)*1.755)+gx )*0.0285; 

//	 ay=atan(Ayro_y/sqrt(Ayro_z*Ayro_z+Ayro_x*Ayro_x))*180/3.14;
     ay=(Ayro_y-Ay_offset )*180*1.0/(Ay_Max-Ay_Min);
     gy=(Gyro_y-Gy_offset)*1.0/16.4;
     ag_y = ag_y + (((ay - ag_y)*1.75)+gy )*0.0286; 

//	 az=atan(sqrt(Ayro_x*Ayro_x+Ayro_y*Ayro_y)/Ayro_z)*180/3.14;
     
     az=(Ayro_z-Az_offset )*180*1.0/(Az_Max-Az_Min);
     gz=(Gyro_z-Gz_offset)*1.0/16.4;
     ag_z = ag_z + (((az - ag_z)*1.75)+gz )*0.0286;
	 
	 temp_c=TempC/340.0+36.25;
 //}


}

float abs6050(float u)
{
	if(u>0)return u;
	else return -u;
}
