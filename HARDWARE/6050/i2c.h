#ifndef __I2C_H
#define __I2C_H 	
#include "stm32f10x.h"
#include "sys.h"

/*******************修改管脚时除了修改宏定义还要修改程序中用到管教的地方*******************************************/
#define  I2C_RCC      RCC_APB2Periph_GPIOA  
#define SCL_H         GPIOA->BSRR = GPIO_Pin_12
#define SCL_L         GPIOA->BRR  = GPIO_Pin_12 
   
#define SDA_H         GPIOA->BSRR = GPIO_Pin_11
#define SDA_L         GPIOA->BRR  = GPIO_Pin_11

#define SCL_read      GPIOA->IDR  & GPIO_Pin_12
#define SDA_read      GPIOA->IDR  & GPIO_Pin_11
	
/*******************此时也可以用以下方法定义，然后可以直接对端口赋值，如：SCL=1;
#define SCL  PAout(5)
*********************************************************************************/

void I2C_delay(void);
u8 I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
u8 I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte) ;
unsigned char I2C_RadeByte(void);
void Soft_I2C_Init(void);
void SDA_IOIN(void);
void SDA_IOOUT(void);

#endif


