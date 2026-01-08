
#include "LPC17xx.h"
#include "../Main.h"
extern uint32_t tick;

void TIMER0_IRQHandler (void)
{
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}

//int led =0;

void TIMER1_IRQHandler (void)
{
//	if(led ==0){
//		LED_On(4);
//		led =1;
//	}
//	else{
//		LED_Out(0);
//		led = 0;
//	}
		
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	tick++;
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

