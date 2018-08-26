/* 
 * File:   blink_c_4.c
 * Author: gavin
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 
 * Created on 20 August 2018, 20:28
 */

#include <xc.h>

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

void main()
{
    GPIO4=0x00;                 // make all GPIO port outputs low
    TRISIO=0x00;                // TRISIO direction ALL pins  output
    ADCON0=0x00;                // Internal ADC OFF
    ANSEL=0x00;                 // All Analog selections pins are assigned as digital I/O
    while(1)
    {
        GPIO4=1;                      // Make GPIO4 port high
        __delay_ms(500); 
        GPIO4=0;                     // Make GPIO4 port low
        __delay_ms(500);
    }

}

