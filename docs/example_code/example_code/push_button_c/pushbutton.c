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

// Config word
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);


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


