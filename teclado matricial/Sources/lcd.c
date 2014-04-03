/*
 *  Created on: Feb 19, 2014
 *      Author: Nelson Antonio Pérez Cervantes
 */
#include "derivative.h"
#include "lcd.h"

void cfgPortsLCD(void) 
{ 
    //Turn on clock for portD and portB 
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
    //Also, we can use predefined masks created by freescale, such as: 
    //SIM_SCGC5_PORTB_MASK; 
      
    /* Set pins of PORTD as GPIO */
	
	
    PORTD_PCR0=(PORT_PCR_MUX(1)); 	//D0
    PORTD_PCR1=(PORT_PCR_MUX(1));	//D1
    PORTD_PCR2=(PORT_PCR_MUX(1)); 	//D2
    PORTD_PCR3=(PORT_PCR_MUX(1)); 	//D3
    PORTD_PCR4=(PORT_PCR_MUX(1)); 	//D4
    PORTD_PCR5=(PORT_PCR_MUX(1)); 	//D5
    PORTD_PCR6=(PORT_PCR_MUX(1)); 	//D6
    PORTD_PCR7=(PORT_PCR_MUX(1));	//D7
	/* Set pins of PORTB as GPIO */
    PORTB_PCR0=(PORT_PCR_MUX(1)); 	//E
    PORTB_PCR1=(PORT_PCR_MUX(1)); 	//RS
      
    //Reasure first PortB and PortD value 
	GPIOB_PDOR = 0x00;
    GPIOD_PDOR = 0x00;
    
    //Configure PortC as outputs 
    GPIOD_PDDR |= 0xFF; 
    GPIOB_PDDR |= 0x03; 
	initLCD();
	pos = 0;
} 
void delay (long time) 
{  
    x = time; 
    while(x>0) 
    { 
    x--; 
    } 
}
void initLCD(void) 
{ 
    delay(ntime_15msec); 
    //Commands = {0x38, 0x38, 0x38, 0x0C, 0x01}; 
    sendCode(nIns, 0b00001110); // prender lcd, activar cursor, desactivar parpadeo
    delay(ntime_40usec);
	sendCode(nIns, 0b00000110); // activar mover cursor a la derecha
	delay(ntime_40usec);
	sendCode(nIns, 0b00111000); //bus de 8 bits, 4 lineas , fuente 5x8
	delay(ntime_40usec);
}  
void sendCode(char Code, char PortData) 
{   
    PortRS_0; 
    PortEnable_0; 
      
    PortLCD = PortData;
      
    if (Code == nIns) 
    { 
        PortRS_0; 
		PortEnable_1;
		delay(ntime_40usec);
		PortEnable_0;
		PortRS_0;
		delay(ntime_15msec);
    } 
    else if (Code == nData) 
    { 
        PortRS_1; 
		PortEnable_1; 
        delay(ntime_40usec); 
        PortEnable_0; 
        PortRS_0; 
		delay(ntime_15msec);
	}
} 
void editChar (char position)
{
	switch (position)
	{
		case 0x00:
		sendCode(nIns,0x40);
		break;
		case 0x01:
		sendCode(nIns,0x48);
		break;
		case 0x02:
		sendCode(nIns,0x50);
		break;
		case 0x03:
		sendCode(nIns,0x58);
		break;
		case 0x04:
		sendCode(nIns,0x60);
		break;
		case 0x05:
		sendCode(nIns,0x68);
		break;
		case 0x06:
		sendCode(nIns,0x70);
		break;
		case 0x07:
		sendCode(nIns,0x48);
		break;
		default:
		sendCode(nIns,0x40);
		break;
	}
}
void BCD(int valor)	
{
	cen = valor / 100;
	r = valor % 100;
	dec = r / 10;
	r = r % 10;
	uni = r;
}
