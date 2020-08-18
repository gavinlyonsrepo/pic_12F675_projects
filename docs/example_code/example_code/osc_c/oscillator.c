/*
 * File:   oscillator.c
 * Author: Gavin Lyons
 * Desc: OUtputs Fosc on pin GP4/OSC2/CLKOUT 
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 16 October 2018, 20:56
 */


#include <xc.h>

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCCLK   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

/*define clock freq*/
#define _XTAL_FREQ 4000000 // 4MHZ internal crystal

void main(void) {
    return;
}
