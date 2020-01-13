//PF4 GPIO SW1
//PF0 GPIO SW2
//PF1 GPIO RGB LED (Red)
//PF2 GPIO RGB LED (Blue)
//PF3 GPIO RGD LED (Green)
//Unlock Value: 0x4C4F434B

#include "TM4C123.h"                    // Device header

int main() {
	
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->LOCK = 0x4C4F434B;			// unlock commit register
	GPIOF->CR = 0x01;							// make PF0 configurable
	
	GPIOF->DIR |= 0X08;						// 0B 0000 1000
	GPIOF->DEN = 0x09;						// 0B 0000 1001	: Set PF0 and PF3 as digital pins
	GPIOF->PUR = 0x01;
	
	while(1) {
		if(!(GPIOF->DATA & 0x01)) {
			GPIOF->DATA |= 0x8; 
		} else {
			GPIOF->DATA &= ~0x8; 			
		}
	}
}