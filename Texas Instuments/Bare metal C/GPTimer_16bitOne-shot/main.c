#include "TM4C123.h"                    // Device header

void timerA0DelayMs(int delay) ;

int main() {
	
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	while(1) {
		GPIOF->DATA ^= 2;
		timerA0DelayMs(50);
	}
}

void timerA0DelayMs(int delay) {
	
	SYSCTL->RCGCTIMER |= 0;	//Enable clock for Timer Block 0
	TIMER0->CTL = 0;
	TIMER0->CFG = 0x04;			//16 bit mode
	TIMER0->TAMR = 0x01;		//one-shot mode, down counter
	TIMER0->TAILR = 16000*delay-1;
	TIMER0->ICR = 0x1;
	TIMER0->CTL = 0X01;
	//Wait for TimerA timeout flat to set
	while((TIMER0->RIS & 0x1)==0) {
		
	}
}