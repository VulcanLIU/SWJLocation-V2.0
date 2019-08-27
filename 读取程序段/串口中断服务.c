void UART5_IRQHandler(void) 
{
	static uint8_t m = 0,rebuf_3[12] = {0};
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
		rebuf_3[m] = USART_ReceiveData(UART5);
		m++;
		if (rebuf_3[0]!= 0x55) 
		{
			m = 0;
			rebuf_3[0] = 0;
		}
		if (rebuf_3[m-1]==0xaa)
		{
		}
		else{
			if(m==11)
			{
				PosX = ConvertTo32(rebuf_3[4], rebuf_3[3], rebuf_3[2], rebuf_3[1]);
				PosY = ConvertTo32(rebuf_3[8], rebuf_3[7], rebuf_3[6], rebuf_3[5]);

				PosAngle = rebuf_3[10];
				PosAngle <<= 8;//高八位
				PosAngle |= rebuf_3[9];
				
			  m = 0; 
			  rebuf_3[0]=0;
			}
		}
	}
}

float ConvertTo32(int la, int lb, int lc, int ld)
{
	la = 0XFFFFFF | (la << 24);
	lb = 0XFF00FFFF | (lb << 16);
	lc = 0XFFFF00FF | (lc << 8);
	ld = 0XFFFFFF00 | ld;
	return la & lb & lc & ld;
}