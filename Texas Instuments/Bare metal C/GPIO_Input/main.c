//PF4 GPIO SW1
//PF0 GPIO SW2
//PF1 GPIO RGB LED (Red)
//PF2 GPIO RGB LED (Blue)
//PF3 GPIO RGD LED (Green)

#include "TM4C123.h"                    // Device header

int main() {
	SYSCTL->RCGCGPIO |=0x20;	//	ENABLE PORT F CLOCK
	GPIOF->DIR |= 0x08;				//	0B 0000 1000	: SET PF3 AS OUTPUT
	GPIOF->DEN |= 0x18;				//	0B	0001 1000
	GPIOF->PUR |= 0x10;
	
	while(1) {
		if (!(GPIOF->DATA & 0x10)) {	//	Switch is active low
			GPIOF->DATA |= 0x8;
		}
		else {
			GPIOF->DATA &=~0X8;
		}
	}
}