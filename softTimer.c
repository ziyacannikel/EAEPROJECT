#include "stm32f10x.h"
#include "softTimer.h"

//
// soft timers array
//
typedef struct{
	_Bool			IsRunning;		         // timer calisma durumu
	volatile _Bool		Timeout;		   // timer tamamlanma durumu
	uint32_t 		SetTime;		         // timer suresi
	uint32_t		Time;			           // aktif sure
}STimerType;

static STimerType SoftTimers[TIMER_COUNT];

//
// Server functions
// 

void SoftTimer_Init(void)
{
	uint8_t i;
	
	for(i = 0; i < TIMER_COUNT; i++)
	{
		SoftTimers[i].IsRunning = 0;         //false yerine 0 yaptim
		SoftTimers[i].Time      = 0; 
		SoftTimers[i].Timeout   = 0;         //false yerine 0 yaptim
	}
	
	//
	// !! !! !!
	//
	// burada islemcinin herhangi bir timer arabirimi 1ms'de bir kesme üretecek sekilde init edilecek
	// bu kesme fonksiyonu (ISR) icerisinde SoftTimer_ISR fonskiyonu cagirilacak
	//
	// !! !! !!
	//
	
	/*TIMER3 CONFIGURATION*/
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC =1 ;                // Set prescaler 
	TIM3->ARR = 11999;             // Auto reload value 
	TIM3->DIER = TIM_DIER_UIE;    // Enable update interrupt (timer level)
	TIM3->CR1 = TIM_CR1_CEN;      // Enable timer

	NVIC_EnableIRQ(TIM3_IRQn);    // Enable interrupt from TIM3 (NVIC level)
	
}

void SoftTimer_SetTimer(uint8_t TimerNo, uint32_t SetTimeMs)
{
	if(TimerNo < TIMER_COUNT)
	{
		SoftTimers[TimerNo].Time		  = 0;
		SoftTimers[TimerNo].SetTime		= SetTimeMs;
		SoftTimers[TimerNo].IsRunning	= 1;
		SoftTimers[TimerNo].Timeout		= 0;
	}
}

_Bool SoftTimer_GetTimerStatus(uint8_t TimerNo)
{
	return(SoftTimers[TimerNo].Timeout);
}

void SoftTimer_ResetTimer(uint8_t TimerNo)
{											 
	SoftTimers[TimerNo].IsRunning = 0;
	SoftTimers[TimerNo].Time = 0;
	SoftTimers[TimerNo].Timeout = 0;
}

void SoftTimer_ISR(void)
{
	
	for(int i=0; i < TIMER_COUNT ; i++)
	{
		if(SoftTimers[i].IsRunning)
		{				
			if(SoftTimers[i].SetTime <= SoftTimers[i].Time)
			{
				SoftTimers[i].Timeout = 1;	
			  
			}
			else
			{
				SoftTimers[i].Time++;
				
			}		 
		} 
		else 
		{
			SoftTimers[i].Timeout = 0;
			SoftTimers[i].Time = 0;
			
		}
	}
}

