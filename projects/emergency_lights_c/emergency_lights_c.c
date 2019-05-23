/*
 * File:   emergency_lights_c.c
 * Author: Gavin Lyons
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.05
 * Created on 25 August 2018, 14:52
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */

#include <xc.h>
#include <stdint.h> /* For uint8_t definitions etc */

/*define clock freq*/
#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif


// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

//GPIO function
#define r_LED1  GP0
#define r_LED2  GP1
#define push_button  GP2
#define b_LED1  GP4
#define b_LED2  GP5

//Delay times
#define DELAY1 50
#define DELAY2 100
#define DELAY3 150
#define DELAY4 200


// Var to hold key press index. 
uint8_t key = 0;

//Function prototypes:
void setup(void);
void InitExternal_INT(void);
void __interrupt() my_ISR(void);
void blink_LEDs_1(void);
void blink_LEDs_2(void);
void blink_LEDs_3(void);
void blink_LEDs_4(void);
void Turn_ON_LEDs(void);
void Turn_OFF_LEDs(void);

// ------- Main LOOP ---------- 
void main(void)
{
setup();
       
    while(1)
    {
        switch(key)
        {
            case 0:Turn_OFF_LEDs(); break;
            case 1:blink_LEDs_1(); break;
            case 2:blink_LEDs_2(); break;
            case 3:blink_LEDs_3(); break;
            case 4:blink_LEDs_4(); break;
            case 5:Turn_ON_LEDs(); break;
        }
    }
}
// -------- End of MAIN LOOP ---------

//setup function
void setup(void)
{
    ANSEL  = 0x00;       // Set ports as digital I/O, not analog input
	ADCON0 = 0x00;		 // Shut off the A/D Converter
	CMCON  = 0x07;		 // Shut off the Comparator
	VRCON  = 0x00;	     // Shut off the Voltage Reference
	TRISIO = 0x04;       // GP2 input all others output
	GPIO   = 0x00;       // Make all pins 0 except push button GP2
    Turn_OFF_LEDs();
    __delay_ms(500);     //init delay
    InitExternal_INT();
}

//Function to init interupt.
void InitExternal_INT(void)
{
	INTCON     |= 0x90;         // Enable Global + INT interrupt
	OPTION_REG |= 0x40;         // Make INT as positive edge triggered
}

// Function to handle interrupt on GP2 of push button press
void __interrupt() my_ISR(void)
{
    if(INTF)  //If External Edge INT Interrupt
    {
          key++;
          if(key==6)
           {
              key=0;
           }
           INTF = 0;    // Clear the interrupt
    }
          
}

// Function to blink LEDS pattern 1
void blink_LEDs_1(void)
{
      uint8_t loop = 0;
      
      loop = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      for(loop=1;loop<9;loop++)
      {
         b_LED1 ^= 0x1;
         b_LED2 ^= 0x1;
         __delay_ms(DELAY1);
      }
      
      loop = 0;
      b_LED1 = 0;
      b_LED2 = 0;
      for(loop=1;loop<9;loop++)
      {
         r_LED1 ^= 0x1;
         r_LED2 ^= 0x1;
         __delay_ms(DELAY1);
      }
}

// Function to blink LEDS pattern 2
void blink_LEDs_2(void)
{
      b_LED1 = 1;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY3);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 1;
      __delay_ms(DELAY3);
}

// Function to blink LEDS pattern 3
void blink_LEDs_3(void)
{
      b_LED1 = 1;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 0;
      __delay_ms(DELAY4);
      b_LED1 = 0;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 1;
      __delay_ms(DELAY4);
} 

// Function to blink LEDS pattern 4
void blink_LEDs_4(void)
{
      b_LED1 = 1;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 1;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 1;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 1;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 1;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 1;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY2);
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
      __delay_ms(DELAY2);
}

// Function to switch on all LEDS
void Turn_ON_LEDs(void)
{
      b_LED1 = 1;
      b_LED2 = 1;
      r_LED1 = 1;
      r_LED2 = 1;
 }


// Function to switch off all LEDS
void Turn_OFF_LEDs(void)
{
      b_LED1 = 0;
      b_LED2 = 0;
      r_LED1 = 0;
      r_LED2 = 0;
}
// EOF
