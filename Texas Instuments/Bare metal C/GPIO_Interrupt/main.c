#include "TM4C123.h"                    // Device header

void delayMs();

int main() {
	SYSCTL->RCGCGPIO |= 0x20;
	
	//Unlock PF0
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR = 0x01;
	GPIOF->LOCK = 0;
	
	GPIOF->DIR &= ~0x11; // make PF4 AND PF0 input pins
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x1F;
	GPIOF->PUR |= 0x11;	// enable pullup for PF4 and PF0
	
	__disable_irq();
	GPIOF->IS &=~0X11;	// make PF4 and PF0 edge sensitive
	GPIOF->IBE &=~0x11;
	GPIOF->IEV &=-0x11;	// falling edge detection
	GPIOF->ICR |= 0x11; // Clear any prior interrupt
	GPIOF->IM		|= 0x11;//	Unmask interrupt
	
	NVIC->IP[30] = 3<<5;//	set interrupt to priority 3
	NVIC->ISER[0] = 0x40000000;	// Enable IRQ30
	__enable_irq();
	while(1) {
		//toggle RED LED
		GPIOF->DATA |= 0x02;
		delayMs(100);
		GPIOF->DATA &=~0x02;
		delayMs(100);
	}
}

void GPIOF_Handler(void) {
	volatile int readback;
	//togle green LED 3 times
	for(int i=0;i<3;i++){
		GPIOF->DATA	|= 0x08;
		delayMs(100);
		GPIOF->DATA	&=~0x08;
		delayMs(100);		
	}
	GPIOF->ICR |=0x11; //Clear interrupt flag before return
	readback = GPIOF->ICR;
}

void delayMs(int delay) {
	for(int i=0;i<delay;i++){
		for(int j=0;j<3180;j++) {}
	}
}