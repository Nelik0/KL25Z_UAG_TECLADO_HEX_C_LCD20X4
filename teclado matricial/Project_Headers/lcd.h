//LCD.h

#ifndef lcd_H_
#define GPIO_PIN_MASK 0x1Fu 
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))
#define PortLCD         GPIOD_PDOR  
#define PortEnable_1    GPIOB_PDOR |= 0x01 
#define PortEnable_0    GPIOB_PDOR &= 0xFE 
#define PortRS_1        GPIOB_PDOR |= 0x02 
#define PortRS_0        GPIOB_PDOR &= 0xFD 
#define ntime_1seg      420000
#define ntime_15msec    3500
#define ntime_40usec    35  
#define nIns    0 
#define nData   1

void cfgPortsLCD(void); //configuracion de puertos de la LCD
void delay(long time);  //retardo necesario para el control de la LCD
void initLCD(void); //sintaxis de inicializacion del LCD
void sendCode(char Code, char PortData); //sintaxis de envio de datos nIns => instruccion, 
                                         //                           nData => dato
int x,i; //contadores

void editChar (char position); //sintaxis para edicion de caracteres  position => lugar de memoria donde quieres guardar el caracter
void BCD(int valor); //conversion de numeros a BCD

int uni, dec, cen, r;
int escritura;
int pos;
#endif /* lcd_H_ */
