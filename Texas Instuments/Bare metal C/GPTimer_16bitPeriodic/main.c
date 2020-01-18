#include "TM4C123.h"                    // Device header

void timer0ADelay(int delay);

int main() {
	
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	while(1) {
		GPIOF->DATA ^= 0x02;
		timer0ADelay(100);
	}
}

void timer0ADelay(int delay) {
	
	SYSCTL->RCGCTIMER |= 1;
	TIMER0->CTL = 0;
	TIMER0->CFG = 0x04;				//16-bit mode
	TIMER0->TAMR = 0x02;			//periodic-mode
	TIMER0->TAILR = 16000-1;
	TIMER0->ICR = 0x1;
	TIMER0->CTL |=0x01;
	
	for (int i = 0 ; i < delay; i++) {
			while((TIMER0->RIS & 0x1) == 0) {}	// Wait for TimerA timeout flag
			TIMER0->ICR = 0x1;									// Clear the TimerA Timout flag
				
	}
}