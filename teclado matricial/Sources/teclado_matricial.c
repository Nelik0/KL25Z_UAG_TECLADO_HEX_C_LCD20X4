/*
 *  Created on: Feb 19, 2014
 *      Author: Nelson Antonio Pérez Cervantes
 */
#include "derivative.h"
#include "teclado_matricial.h"


void cfgPortBot(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		
	PORTC_PCR0 |= (PORT_PCR_MUX(1));	//RB0
	PORTC_PCR1 |= (PORT_PCR_MUX(1));	//RB1
	PORTC_PCR2 |= (PORT_PCR_MUX(1));	//RB2
	PORTC_PCR3 |= (PORT_PCR_MUX(1));	//RB3
	
	PORTC_PCR4 = (PORT_PCR_MUX(1));	//RB4
	PORTC_PCR5 = (PORT_PCR_MUX(1));	//RB5
	PORTC_PCR6 = (PORT_PCR_MUX(1));	//RB6
	PORTC_PCR7 = (PORT_PCR_MUX(1));	//RB7
	
	GPIOC_PDDR = PB_FILE_MASK;
	GPIOC_PDOR = PB_FILE_MASK;
	
	ready_read = 0;
	read = 0;
}
void debounce(long stage)
{
	while(stage>0) 
    { 
		stage--; 
    } 
}
void botread(void)
{	
	if (PORT_KEY_IN & PB_COLUMN_MASK)
	{
		escaneo_matriz(RB7,'1','2','3','A');
		escaneo_matriz(RB6,'4','5','6','B');
		escaneo_matriz(RB5,'7','8','9','C');
		escaneo_matriz(RB4,'*','0','#','D');
		debounce(700000);
		ready_read = 1;
		PORT_KEY_OUT |= PB_FILE_MASK;
	}
}
void escaneo_matriz(char file,char rb3,char rb2, char rb1, char rb0)
{
	PORT_KEY_OUT = file;
	if (PORT_KEY_IN)
	{
		switch (PORT_KEY_IN & PB_COLUMN_MASK)
		{
			case 0x01:
				read = rb0;
				break;
			case 0x02:
				read = rb1;
				break;
			case 0x04:
				read = rb2;
				break;
			case 0x08:
				read = rb3;
				break;
		}
	}
}
