
/*
 * File:    LED_random.c
 * Author: gavin Lyons
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.0
 * pic12F675
 * Created on 18 January 2019, 21:35
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */

#include <xc.h>
#include <stdlib.h> // for  rand()

/*define clock freq*/
#define _XTAL_FREQ 4000000  // 4MHZ crystal


// Config word
// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

/*GPIO function
 LED1  GP0
 LED2  GP1
 LED3  GP2
 n/c   GP3
 LED4  GP4
 LED5  GP5
*/

char led_Array[12] = {0x00,0x01,0x02,0x04,0x10,0x20,0x21,0x33,0x12,0x37,0x36,0x14};
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
    unsigned char pick=0;
    pick = rand() % 12;
     switch (pick)
        {
         case 0: GPIO = led_Array[pick]; break;
         case 1: GPIO = led_Array[pick]; break;
         case 2: GPIO = led_Array[pick]; break;
         case 3: GPIO = led_Array[pick]; break;
         case 4: GPIO = led_Array[pick]; break;
         case 5: GPIO = led_Array[pick]; break;
         case 6: GPIO = led_Array[pick]; break;
         case 7: GPIO = led_Array[pick]; break;
         case 8: GPIO = led_Array[pick]; break;
         case 9: GPIO = led_Array[pick]; break;
         case 10: GPIO = led_Array[pick]; break;
         case 11: GPIO = led_Array[pick]; break;
        } 
        __delay_ms(1000);
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
