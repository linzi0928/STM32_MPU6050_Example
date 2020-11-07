/*************************************************************************************************************
舸轮综合电子工作室(GIE工作室)
Gearing Interated Electronics Studio

底层AD扫描相关函数(来自正点原子库)

关注B站UP主：GIE工作室 获得更多视频资源及动态

*************************************************************************************************************/
 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_adc.h"													   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC2	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC2);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目 
	ADC_Init(ADC2, &ADC_InitStructure);
  
	ADC_Cmd(ADC2, ENABLE);
	

	ADC_ResetCalibration(ADC2);
		
	while(ADC_GetResetCalibrationStatus(ADC2));
	
	ADC_StartCalibration(ADC2);
	
	while(ADC_GetCalibrationStatus(ADC2));	
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				 
u16 Get_Adc(u8 ch)   
{
int long radc;
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束

	radc= ADC_GetConversionValue(ADC2);	//返回最近一次ADC1规则组的转换结果
	
	return radc;
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
	}
	return temp_val/times;
// 	return Get_Adc(ch);
} 	 
u8 adcscan()
{
		u32 adcx;
		adcx=Get_Adc_Average(ADC_Channel_0,2);
		adcx=12.5*(adcx*(3.3/1024));
		return adcx;
}


























