//**************************************************************************
// FileName       : 8-bit LCD Programming using Port-1
// Microcontroller: LPC2148
// Compiler	  : Keil v-4
// Target Hardware: ARM7 Development Board
// Description 	  : Printing some characters on LCD using LPC2148 controller
// Pin Connection :`LCD datalines (D0 to D7) connected to Port-1 pins  
//                  P1.18 to P1.25 respectively and Rs pin of LCD connected
//                  to P1.26 and EN pin of LCD connected to P1.27 & R/W pin 
//                  of LCD is connected to ground
//***************************************************************************


#include<lpc214x.h>
							
//*************** Function Declaration **************//

void delay(void);
void LCD_init(void);
void LCD_cmd(char cmd);
void LCD_data(char data);
void LCD_string(char *ptr);

//*************** END ofFunction Declaration **************//

//*************** MAIN Program **************//

int main()
{
	PINSEL2 = 0x00000000; // P1.18 to P1.25 configured as GPIO
		
	IODIR1 = 0x0FFC0000; // P1.18 to P1.25 configured as output port

	LCD_init();          // Function call
	
	while(1)
	{
	     LCD_cmd(0x80);	// first line starting address												
	     LCD_string(" ARM ");
 
	     LCD_cmd(0xC0);	// Second line starting address												
	     LCD_string(" MICROCONTROLLER ");									
		
	
	}
}

//*************** END of MAIN Program **************//

//*************** Delay Program **************//

void delay(void)
{
	unsigned int i, j;
	
	for(i = 0 ; i < 1000 ; i++)
		for(j = 0 ; j < 500 ; j++);
}

//*************** END of Delay Program **************//

//*************** LCD initilization Program **************//

void LCD_init()
{
	LCD_cmd(0x38);//selection of  8 bit data,2 lines,7x5 dot matrix 
	LCD_cmd(0x0C);//Display ON cursor OFF
	LCD_cmd(0x01);//clear LCD display
						
}

//*************** END of LCD initilization Program *********//

//*************** LCD Command Program **************//

void LCD_cmd(char cmd)
{
	IOCLR1 = 0x0FFC0000;	
	IOSET1 = cmd << 18 | 0x08000000;				
	delay();																
	IOCLR1 = 0x0FFC0000;										 
}

//*************** END of LCD Command Program *********//

//*************** LCD DATA Program **************//

void LCD_data(char data)
{
	IOCLR1 = 0x0FFC0000;										
	IOSET1 = data << 18 | 0x0C000000;				
	delay();																
	IOCLR1 = 0x0FFC0000;										
}

//*************** END of LCD DATA Program **************//

//*************** LCD string Program **************//
void LCD_string(char *ptr)
{
	while(*ptr)
		LCD_data(*ptr++);
}

//*************** END of LCD string Program **************//
