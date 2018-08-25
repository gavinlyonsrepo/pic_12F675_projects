/*
 * File:   emergency_lights_c.c
 * Author: gavin Lyons
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 
 * Created on 25 August 2018, 14:52
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */

#include <xc.h>
/*define clock freq*/

#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif

// Config word
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);

//GPIO function
#define r_LED1  GP0
#define r_LED2  GP1
#define push_button  GP2
#define b_LED1  GP4
#define b_LED2  GP5

// Var to hold key press index. 
unsigned int key = 0;

//setup function
void setup(void)
{
    ANSEL  = 0x00;       // Set ports as digital I/O, not analog input
	ADCON0 = 0x00;		 // Shut off the A/D Converter
	CMCON  = 0x07;		 // Shut off the Comparator
	VRCON  = 0x00;	     // Shut off the Voltage Reference
	TRISIO = 0x04;       // GP2 input all others output
	GPIO   = 0x04;       // Make all pins 0
   
}

//Function to init interupt.
void InitExternal_INT(void)
{
	TRISIO2 = 1;                // Make GP2 pin as input

	INTCON     |= 0x90;         // Enable Global + INT interrupt
	OPTION_REG |= 0x40;         // Make INT as posedge triggered
}

// Function to handle interupt on GP2 of push button press
void interrupt ISR(void)
{
    if(INTF)  //If External Edge INT Interrupt
    {
        
          key++;
          if(key==5)
           {
              key=1;
           }
           INTF = 0;    // Clear the interrupt
    }
          
}

// Function to blink leds passed key number
void blink_LEDs(unsigned int key)
{
   unsigned int s = 0;
   if(key == 1)
   {
      s = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      for(s=1;s<9;s++)
      {
         b_LED1 ^= 0x1;
         b_LED2 ^= 0x1;
         __delay_ms(49);
      }
      s = 0;
      b_LED1 = 0;
      b_LED2 = 0;
      for(s=1;s<9;s++)
      {
         r_LED1 ^= 0x1;
         r_LED2 ^= 0x1;
         __delay_ms(49);
      }
   }
   if(key == 2)
   {
      b_LED1 = 1;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(149);
      r_LED1 = 1;
      r_LED2 = 1;
      b_LED1 = 0;
      b_LED2 = 0;
      __delay_ms(149);
   }
   if(key == 3)
   {
      b_LED1 = 1;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 0;
      __delay_ms(199);
      r_LED1 = 0;
      r_LED2 = 1;
      b_LED1 = 0;
      b_LED2 = 1;
      __delay_ms(199);
   }
   if(key == 4)
   {
      b_LED1 = 1;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 1;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 1;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 1;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(99);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(99);
   }
   else
   {
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
   }
}

//Main
void main(void)
{
setup();
InitExternal_INT();
       
    while(1)
    {
        switch(key)
        {
            case 1:blink_LEDs(1); break;
            case 2:blink_LEDs(2); break;
            case 3:blink_LEDs(3); break;
            case 4:blink_LEDs(4); break;
           
        }
    }
}
// EOF
