#include "teclado_matricial.h"
#include "lcd.h"
#include "derivative.h"

char menu_principal[80] = 	   "*Selec. una opcion**a)Cfg. Bluetooth    b)Cfg. Filtro       c)Enviar cfg. actual"; //menu 1
char menu_cfg_bt[80] =		   "***Cfg. Bluetooth*** a)Nombre dispo.     b)Contrasena       *Selec. una opcion**"; //menu 2
char menu_cfg_nombre_dis[80] = "***Nombre dispo.****Nombre dispositivo: -----     #=enter   **Max.5 caracteres**"; //menu 3
char menu_cfg_contra[80] =     "*****Contrasena*****  Contrasena        ----                ****Max.4 digitos***"; //menu 4
char menu_cfg_filtro[80] =	   "****Cfg. Filtro***** a)Filtro P. banda   b)Filtro R. banda  *Selec. una opcion**"; //menu 5
char menu_cfg_pbandas[80] =	   "**Filtro P. bandas**Frecuencia de corte central: --- Hz     Rango de 10 - 365 Hz"; //menu 6
char menu_cfg_rbandas[80] =    "**Filtro R. bandas**Frecuencia de corte central: --- Hz     Rango de 08 - 258 Hz"; //menu 7
char menu_confirmacion[80] =   "Enviar esta config.?BT ID:----- a)Si    PASS:----   b)Aun noFCR:---Hz  FCP:---Hz"; //menu 8
char error_display[80] =       "  Favor de revisar    los parametros    FCR y FCP pulse a) ob) para continuar   "; //menu 9

char stop = 0; //bandera de enter
char error = 0;	//bandera de error: se activa cuando los valores de frecuencia de corte central de filtro rechaza bandas (FCCR) y
				//frecuencia de corte central de filtro rechaza bandas (FCCP) no se encuentran en los rangos								

int counter_name; //contador de las configuraciones

char name_device[5] =  "ECGBT"; //nombre por default del BT(ID)
char password[4] =     "1234";	//contraseña por default
char fcc_p_bandas[3] = "120";	//FCCP por default
char fcc_r_bandas[3] = "120";	//FCCR por default

int fcc_p; 	//valor numerico de FCCP 
int fcc_r;	//valor numerico de FCCR

void writeLCD_menu(char menu); //escribe las pantallas de diferentes menus
void op_select(void); //sintaxis para seleccion de opcion a y b
void op_multi_select(void);	//sintaxis para seleccion de a, b, c
void reset_flag(void);	//reseteo de banderas
void write_w_key(void); //escritura con el teclado matricial
void enter_device_name(void);	//sintaxis para ingresar el id del bt
void enter_pass(void);	//sintaxis para ingresar contraseña del bt
void enter_fcc_p_bandas(void); //sintaxis para ingresar la frecuencia de corte central del filtro pasa bandas
void enter_fcc_r_bandas(void);	//sintaxis para ingresar la frecuencia de corte central del filtro rechaza bandas
void cfg_ECG_options(void);	//sintaxis donde se configura todos los parametros del ECG
void confirmacion(void);	//sintaxis para confirmar el envio de parametros al ECG
void show_cfg(void);	//escribe las configuracion que se encuentran por el momento en la configuracion
void verificacion(void); //sintaxis donde se verifica si los valores de FCCR y FCCP estan en los rango permisibles 

int main(void)
{
	cfgPortsLCD(); //configuracion de puertos del LCD 20x4
	cfgPortBot();  //configuracion de puertos del teclado matricial
	sendCode(nIns,0x01);
	for(;;) 
	{
		cfg_ECG_options();
		confirmacion();
	}
	
	return 0;
}
void writeLCD_menu(char menu)
{
	switch(menu)
	{
	case 1:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_principal[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_principal[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_principal[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_principal[pos]);
		}
		sendCode(nIns,0xA7);
		break;
	case 2:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_cfg_bt[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_cfg_bt[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_cfg_bt[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_cfg_bt[pos]);
		}
		sendCode(nIns,0xA7);
		break;
	case 3:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_cfg_nombre_dis[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_cfg_nombre_dis[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_cfg_nombre_dis[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_cfg_nombre_dis[pos]);
		}
		break;
	case 4:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_cfg_contra[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_cfg_contra[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_cfg_contra[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_cfg_contra[pos]);
		}
		break;
	case 5:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_cfg_filtro[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_cfg_filtro[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_cfg_filtro[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_cfg_filtro[pos]);
		}
		sendCode(nIns,0xA7);
		break;
	case 6:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_cfg_pbandas[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_cfg_pbandas[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_cfg_pbandas[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_cfg_pbandas[pos]);
		}
		break;
	case 7:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_cfg_rbandas[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_cfg_rbandas[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_cfg_rbandas[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_cfg_rbandas[pos]);
		}
		break;
	case 8:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,menu_confirmacion[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,menu_confirmacion[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,menu_confirmacion[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,menu_confirmacion[pos]);
		}
		break;
	case 9:
		for(pos=0;pos<20;pos++)
		{
			sendCode(nIns,0x80+pos);
			sendCode(nData,error_display[pos]);
		}
		for(pos=20;pos<40;pos++)
		{
			sendCode(nIns,0xAC+pos);
			sendCode(nData,error_display[pos]);
		}
		for(pos=40;pos<60;pos++)
		{
			sendCode(nIns,0x80+pos-20);
			sendCode(nData,error_display[pos]);
		}
		for(pos=60;pos<80;pos++)
		{
			sendCode(nIns,0xAC+pos-20);
			sendCode(nData,error_display[pos]);
		}
		break;
	}
}
void op_select(void)
{
	while((read!='A')&&(read!='B'))
		{
			botread();
		}
}
void op_multi_select(void)
{
	while((read!='A')&&(read!='B')&&(read!='C'))
		{
			botread();
		}
}
void reset_flag(void)
{
	read = 0;
	ready_read = 0;
}
void write_w_key(void)
{
		while(read == 0)
		{
			botread();
		}
		if (read == '#')
		{
			stop = 1;
		}
		else
		{
			sendCode(nData,read);
		}
}
void enter_device_name(void)
{
	
	for (counter_name=0;counter_name<5;counter_name++)
	{
		name_device[counter_name] = ' ';
	}
	counter_name = 0;
	while((stop == 0)&&(counter_name < 5))
	{
		write_w_key();
		if(read!='#')
		{
			name_device[counter_name] = read;
		}
		reset_flag();
		counter_name++;
	}	
	stop = 0;
}
void enter_pass(void)
{
	for (counter_name=0;counter_name<4;counter_name++)
	{
		password[counter_name] = ' ';
	}
	counter_name = 0;
	while((counter_name < 4))
	{
		while(read == 0)
		{
			botread();
		}
		if((read>=0x30)&&(read<0x3A))
		{	
			sendCode(nData,read);
			password[counter_name] = read;
			counter_name++;
		}
		reset_flag();
	}	
	stop = 0;
}
void enter_fcc_p_bandas(void)
{
	for (counter_name=0;counter_name<3;counter_name++)
	{
		fcc_p_bandas[counter_name] = ' ';
	}
	counter_name = 0;
	while((counter_name < 3))
	{
		while(read == 0)
		{
			botread();
		}
		if((read>=0x30)&&(read<0x3A))
		{	
			sendCode(nData,read);
			fcc_p_bandas[counter_name] = read;
			counter_name++;
		}
		reset_flag();
	}	
	stop = 0;
}
void enter_fcc_r_bandas(void)
{
	for (counter_name=0;counter_name<3;counter_name++)
	{
		fcc_r_bandas[counter_name] = ' ';
	}
	counter_name = 0;
	while((counter_name < 3))
	{
		while(read == 0)
		{
			botread();
		}
		if((read>=0x30)&&(read<0x3A))
		{	
			sendCode(nData,read);
			fcc_r_bandas[counter_name] = read;
			counter_name++;
		}
		reset_flag();
	}	
	stop = 0;
}
void cfg_ECG_options(void)
{
	writeLCD_menu(1);
	op_multi_select();
		if (read == 'A')
		{
			writeLCD_menu(2);
			reset_flag();
			op_select();
			if(read == 'A')
			{
				writeLCD_menu(3);
				reset_flag();
				sendCode(nIns,0x94);
				enter_device_name();
			}
			else if (read == 'B')
			{
				writeLCD_menu(4);
				reset_flag();
				sendCode(nIns,0x94);
				enter_pass();
			}
		}
		else if(read == 'B')
		{
			writeLCD_menu(5);
			reset_flag();
			op_select();
			if(read == 'A')
			{
				writeLCD_menu(6);
				reset_flag();
				sendCode(nIns,0x9D);
				enter_fcc_p_bandas();
			}
			else if (read == 'B')
			{
				writeLCD_menu(7);
				reset_flag();
				sendCode(nIns,0x9D);
				enter_fcc_r_bandas();
			}
		}
		else if(read == 'C')
		{
			reset_flag();
		}
}
void confirmacion(void)
{
	show_cfg();
	op_select();
	if (read == 'A')
	{
		verificacion();
		reset_flag();
		if(error)
		{
			writeLCD_menu(9);
			op_select();
			error = 0;
		}
	}
	reset_flag();
}
void show_cfg(void)
{
	writeLCD_menu(8);
	sendCode(nIns,0xC6);
	for(counter_name=0;counter_name<5;counter_name++)
	{
		sendCode(nData,name_device[counter_name]);
	}
	sendCode(nIns,0x99);
	for(counter_name=0;counter_name<4;counter_name++)
	{
		sendCode(nData,password[counter_name]);
	}
	sendCode(nIns,0xD8);
	for(counter_name=0;counter_name<3;counter_name++)
	{
		sendCode(nData,fcc_r_bandas[counter_name]);
	}
	sendCode(nIns,0xE3);
	for(counter_name=0;counter_name<3;counter_name++)
	{
		sendCode(nData,fcc_p_bandas[counter_name]);
	}
	sendCode(nIns,0xD3);
}
void verificacion(void)
{
	fcc_p = ((fcc_p_bandas[0]-0x30)*100)+((fcc_p_bandas[1]-0x30)*10)+((fcc_p_bandas[2]-0x30));
	fcc_r =	((fcc_r_bandas[0]-0x30)*100)+((fcc_r_bandas[1]-0x30)*10)+((fcc_r_bandas[2]-0x30));
	if((fcc_p<10)||(fcc_p>365)||(fcc_r<8)||(fcc_r>258))
	{
		error = 1;
	}
}
