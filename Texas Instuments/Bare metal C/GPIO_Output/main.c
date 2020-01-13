//PF4 GPIO SW1
//PF0 GPIO SW2
//PF1 GPIO RGB LED (Red)
//PF2 GPIO RGB LED (Blue)
//PF3 GPIO RGD LED (Green)

#include "TM4C123.h"				//Device header
void delayMs( int ms );

int main() 
{
	SYSCTL->RCGCGPIO |= 0x20;		// 0B 0010 0000	: Enable Clock access to PortF
	GPIOF->DIR |= 0x02;		// 0B 0000 0010		SET RED LED as OUTPUT
	GPIOF->DEN |= 0x02;		// Set Pin1 digital
		while(1)
		{
			GPIOF->DATA |= 0x02;	// Set Pin1 High
			delayMs(100);
			GPIOF->DATA &=~0x02;	// Set Pin1 Low
			delayMs(100);			
		}
}

void delayMs( int ms )
{
	int i, j;
	for (i=0;i<ms;i++) {
		for (j=0;j<3180;j++)
		{}
	}
}