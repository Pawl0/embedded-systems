#include "TM4C123.h"                    // Device header

void timer0BDelay(int delay);

int main() {
	
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	while(1) {
		GPIOF->DATA ^= 0x02;
		timer0BDelay(1000);
	}
}

void timer0BDelay(int delay) {
	
	SYSCTL->RCGCTIMER |= 1;
	TIMER0->CTL = 0;
	TIMER0->CFG = 0x04;				//16-bit mode
	TIMER0->TBMR = 0x02;			//periodic-mode
	TIMER0->TBILR = 16000-1;	//timer B Interval Load Register
	TIMER0->ICR = 0x100;			//clear timerb timeout flag
	TIMER0->CTL |=0x0100;			//Enable TimerB
	
	for (int i = 0 ; i < delay; i++) {
			while((TIMER0->RIS & 0x100) == 0) {}	// Wait for TimerB timeout flag
			TIMER0->ICR = 0x100;									// Clear the TimerB Timout flag
				
	}
}