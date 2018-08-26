/*
 * File:   knight_rider_c.c
 * Author: gavin Lyons
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 * pic12F675
 * Created on 26 August 2018, 09:52
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */

#include <xc.h>

/*define clock freq*/
#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif

// Config word
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);
/*GPIO function
 LED1  GP0
 LED2  GP1
 LED3  GP2
 LED4  GP4
 LED5  GP5
*/
char led_Array[8] = {0x01,0x02,0x04,0x10,0x20,0x10,0x04,0x02};
int counter = 0;

/* Function to setup pic*/
void setup(void)
{   
    ANSEL  = 0x00;       // Set ports as digital I/O, not analog input
	ADCON0 = 0x00;		 // Shut off the A/D Converter
	CMCON  = 0x07;		 // Shut off the Comparator
	VRCON  = 0x00;	     // Shut off the Voltage Reference
	TRISIO = 0x00;       //  make all pins output
	GPIO   = 0x00;       // Make all pins 0v low.
}

/* function to toggle leds patterns*/
void Ledon(void)
{ 
        GPIO = led_Array[counter];
		counter++;
		if (counter==8) counter=0;
        __delay_ms(500);
}

/* Main */
void main(void) {
    setup();
   
    while (1)
    {
       Ledon(); 
    }
}
/*EOF*/