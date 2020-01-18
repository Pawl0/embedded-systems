#include "TM4C123.h"                    // Device header

//Toggle LED at 1hz using systick
int main() {
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR = 0x0E;
	GPIOF->DEN = 0x0E;
	
	//Systick Config
	SysTick->LOAD = 16000000-1;
	SysTick->CTRL = 5;	// enble systick, no interrupt, use system clock
	
	while(1) {
		
		// check if count flag is set
		if(SysTick->CTRL & 0x10000) {
			GPIOF->DATA ^= 2;
		}
	}
}