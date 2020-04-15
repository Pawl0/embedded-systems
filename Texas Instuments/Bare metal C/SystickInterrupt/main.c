#include "TM4C123.h"                    // Device header

int main() {
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	//Configure systick
	__disable_irq();
	SysTick->LOAD = 16000000-1;
	SysTick->CTRL = 7;	//ENABLE, USE INTERRUPT, USE SYSTEM CLOCK
	
	__enable_irq();
	
	while(1) {}
}

void SysTick_Handler(){
	//blink LED
	
	GPIOF->DATA ^= 0x02;
}