/*
 * File:   pushbutton.c
 * Author: gavin
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 
 * Created on 23 August 2018, 18:59
 */

#include <xc.h>

/*define clock freq*/

#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG  PIC12F675 Configuration Bit Settings
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


void main()
{  
    GPIO=0x00;             // set all pins low
    TRISIO=0x04;            // set as output except bit 2 GP2=i/p
    ADCON0=0x00;                // Internal ADC OFF
    ANSEL=0x00;                  // All Analog selections pins are assigned as digital I/O
       do
      {
        if(GPIO2 == 0) //If Switch is pressed
        {
          __delay_ms(50); //Provides required delay
          if(GPIO2 == 0) //If Switch is still pressed
          {
              if (GPIO4 == 0)
              {
                GPIO4=1; //LED on 
                __delay_ms(500);
              }
              else{
                GPIO4=  0; //LED OFF
                __delay_ms(500);
              }
          }
        }
      }while(1);

}


