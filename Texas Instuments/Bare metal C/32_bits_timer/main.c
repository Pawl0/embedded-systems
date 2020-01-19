#include "TM4C123.h"                    // Device header
#define BLUE (1U<<2);

void delaySecond(uint32_t sec);

int main() {
	SYSCTL->RCGCGPIO |= (1U<<5);
	GPIOF->DIR |= BLUE;
	GPIOF->DEN |= BLUE;
	
	while(1) {
		GPIOF->DATA ^= BLUE;
		delaySecond(10);
	}
}

void delaySecond(uint32_t sec) {
	int j;
	
	SYSCTL->RCGCTIMER |= 0x01;
	TIMER0->CTL =0x00;						//disable timer0 during setup
	TIMER0->CFG = 0;							//configure for 32-bit timer mode
	TIMER0->TAMR = 0x02;					//Periodic, down counter
	TIMER0->TAILR = 16000000-1;		//start value for 25hz interrupt
	TIMER0->ICR = 0x01;						//clear timer0 timeout flag
	TIMER0->CTL |= 0X01;
	
	for (j=0;j<sec;j++) {
		while((TIMER0->RIS & 0x01) == 0);
		TIMER0->ICR = 0x01;
	}
}