#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "string.h"

//如果想串口中断接收，请不要注释以下宏定义
#define USART_REC_LEN  			700  	//定义最大接收字节数 700
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern char USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 i;							 //缓存数组索引变量

void uart1_init(u32 bound);
void uart2_init(u32 bound);
char Find(char *a);

#endif


