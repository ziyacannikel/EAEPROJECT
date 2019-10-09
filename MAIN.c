#include "stm32f10x.h"                  // Device header
#include "softTimer.h"
_Bool ledStatus=0;

void led_init(void){
 GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void TIM3_IRQHandler(void){
	
if(TIM3->SR & TIM_SR_UIF)       // if UIF flag is set
  {
		TIM3->SR &= ~TIM_SR_UIF;    // clear UIF flag
		SoftTimer_ISR();		        // SoftTimerISR function
  }
}

uint32_t		sure =0;	
uint32_t		sure1 =0;	
_Bool bcont=0;

void blinktime(void)
{
  //Short time 
	while(1)
	{			

		if(SoftTimer_GetTimerStatus(0))
		{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)) //Buton durumu
			{
					sure++;
				  bcont=1;
				
			}
			if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) & bcont)
			{ 
					if(sure>10)
					{
						sure=0;	
						bcont=0;
						break;
					}
						sure=0;	
			}
			sure1++;
			SoftTimer_ResetTimer(0);
			SoftTimer_SetTimer(0, 100); 
		}
		/*Kisa zaman modu süreleri*/
		if(sure1<=10)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>10 & sure1<=20)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>20 & sure1<=30)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>30 & sure1<=40)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>40 & sure1<=60)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>60 & sure1<=80)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>80 & sure1<=100)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>100 & sure1<=120)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else
		sure1=0;

	}
 //Long time
	while(1)
	{			

		if(SoftTimer_GetTimerStatus(0))
		{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)) //Buton durumu
			{
					sure++;
				  bcont=1;
				
			}
			if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) & bcont)
			{ 
					if(sure<10)
					{
						sure=0;	
						bcont=0;
						break;
					}
						sure=0;	
			}
			sure1++;
			SoftTimer_ResetTimer(0);
			SoftTimer_SetTimer(0, 100); 
		}
		
		/*Uzun zaman modu süreleri*/
		if(sure1<=10)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>10 & sure1<=20)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>20 & sure1<=30)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>30 & sure1<=40)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>40 & sure1<=50)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>50 & sure1<=60)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>60 & sure1<=70)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>70 & sure1<=80)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>80 & sure1<=100)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>100 & sure1<=120)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>120 & sure1<=140)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>140 & sure1<=160)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>160 & sure1<=180)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>180 & sure1<=200)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>200 & sure1<=220)
		{GPIO_SetBits(GPIOC,GPIO_Pin_9);}
		else if(sure1>220 & sure1<=240)
		{GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
		else
		sure1=0;
	

	}
	
}	
	

int main()
{
	led_init();
	SoftTimer_Init();
	SoftTimer_SetTimer(0, 100); //100 ms ayarli asagi yukari	

	while(1)
	{
	
		blinktime();
	
		
	}
}


