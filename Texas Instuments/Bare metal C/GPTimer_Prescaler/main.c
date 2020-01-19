#include "TM4C123.h"                    // Device header

void timer1ADelaySec(int delay);
	
int main() {
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR = 0x0E;
	GPIOF->DEN = 0x0E;
	while(1) {
		GPIOF->DATA ^= 0x02;
		timer1ADelaySec(2);
	}
	
}

void timer1ADelaySec(int delay){
	SYSCTL->RCGCTIMER |= 0x02;						//Enable clock access to Timer1 Block
	TIMER1->CTL = 0;
	TIMER1->CFG = 0x04;										//16bit mode
	TIMER1->TAMR = 0x02;									//Periodic mode
	TIMER1->TAILR = 64000-1;
	TIMER1->TAPR = 250-1;									//TIMERA PRESCALER 16MHz/250 = 640000Hz
	TIMER1->ICR = 0x1;
	TIMER1->CTL |= 0x01;
	
	for (int i=0;i<delay;i++) {
		while((TIMER1->RIS &0x1) == 0) {}
			TIMER1->ICR = 0x1;
	}
}