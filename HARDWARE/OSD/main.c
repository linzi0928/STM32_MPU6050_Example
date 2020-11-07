int main(void)
{

	NVIC_Configuration(); 

	MAX7456_SYS_Init();
	MAX7456_Write_ASCII_Chr(0, 0, 'B');
		
	while(1)
	{

	}
}
