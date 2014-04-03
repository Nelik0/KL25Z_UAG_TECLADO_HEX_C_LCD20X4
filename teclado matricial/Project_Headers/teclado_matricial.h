//teclado_matricial.h

#ifndef teclado_matricial_H_
#define GPIO_PIN_MASK 0x1Fu 
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))

#define PORT_KEY_IN		GPIOC_PDIR
#define PORT_KEY_OUT	GPIOC_PDOR

#define RB4		GPIOC_PDIR = 0x10
#define RB5		GPIOC_PDIR = 0x20
#define RB6		GPIOC_PDIR = 0x40
#define RB7		GPIOC_PDIR = 0x80

#define PB_COLUMN_MASK		0x0F 
#define PB_FILE_MASK		0xF0

void cfgPortBot(void); //configuracion de puerto de botones
void debounce(long stage); //sintaxis para evitar rebote por medio de retardo
void botread(void); //sintaxis para leer el teclado
void escaneo_matriz(char file, char rb3, char rb2, char rb1, char rb0); //sintaxis para escaneo deL teclado

unsigned char read; //variable donde se guarda la lectura del teclado
unsigned char ready_read;	//bandera de lectura lista: se coloca en 1 cuando el micro ya tomo la lectura como tal, se necesita regresar a 0
							//por sw (asignar un cero)

#endif /* teclado_matricial_H_ */
