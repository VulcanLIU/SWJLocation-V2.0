
#include"stm32f10x_lib.h"
#include"RCC_Configuration.h"  //系统时钟配置
#include"USART_Configuration.h"
#include"delay.h"
#include <stdio.h>
TIM_OCInitTypeDef TIM_OCInitStructure;
u16	 aa, flay=0	;

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//两个输出端
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //开启定时器时钟
	TIM_DeInit(TIM3);									   //初始值
	TIM_TimeBaseStructure.TIM_Prescaler=0;             //TIM3时钟调节频率  
	TIM_TimeBaseStructure.TIM_Period=600;                 // 装入初值 调节频率 50ms
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分割 可以不要
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;		//PWM模式2
	TIM_OCInitStructure.TIM_Pulse=aa; 					//调节占控制
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	 //使能输出比较
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;		//输出极性
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);			//装入TIM3_CH1
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);			//装入TIM3_CH2
//	TIM_ARRPreloadConfig(TIM3,ENABLE);					//使能TIM3在ARR上的预装在寄存器，可以不要
	TIM_Cmd(TIM3,ENABLE);								//使能TIM3外设
}
int main(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();
	TIM3_Configuration();
	delay_init(72);
	while(1)
	{	
		if(flay==0)
		{
			aa++;						   // 自己改变占空比
			if(aa==600)
			{
				flay=1;
			}	
		}
		if(flay==1)
			{
				aa--;
				if(aa==0)
				{
					flay=0;
				}	
			}				 
	   delay_ms(1);				   //延时
	   	printf("\r\n aa=  %d\r\n",aa);
	   TIM_OCInitStructure.TIM_Pulse=aa;
	   TIM_OC3Init(TIM3, &TIM_OCInitStructure);	  //重新装入占空比值
	   TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	}
		
}




