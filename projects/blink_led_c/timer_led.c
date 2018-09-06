/* ====== Header =======
 * File:  timer_led.c
 * Author: Gavin Lyons
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 05 September 2018, 18:02
 */

/* ======= Includes ========*/
#include <xc.h>

/* ======== Define and Pragma Directives   ======== */

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000
#define LED GPIO0

/* ======= Globals========*/

int counter = 1;

 /* ======== Function space ===========*/

void interrupt ISR(void)
{
    if(TMR1IF)
    {
        counter ++;
        //45541 20 mS h =B1 l = E5
        //http://eng-serve.com/pic/pic_timer.html
        TMR1H = 0xB1;
        TMR1L = 0xE5;
        TMR1IF = 0; //TMR1 Overflow Interrupt Flag bit
        
        if(counter  == 50) // 20mS * 50 = 1 Second
        {
           counter = 0;
            LED = ~LED;
        }
    }
}

void timer_init(void)
{
    GIE = 1;      //INTCON bit 7 GIEL: Global Interrupt Enable bit
    PEIE = 1;     //INTCON bit 6 PEIE: Peripheral Interrupt Enable bit
    TMR1IE = 1;   //PIE!1 bit 0 TMR1IE: TMR1 Overflow Interrupt Enable bit
    
    TMR1IF = 0;   //PIR1 bit 0 TMR1IF:TMR1 Overflow Interrupt Flag bit
    TMR1H = 0XB1; 
    TMR1L = 0XE5;
    TMR1ON = 1;  //T1CON bit 0  TMR1ON: Timer1 On bit
}

void setup(void)
{
    TRISIO0 = 0; // GPIO5 output
    ANSEL = 0X00; //turn off ADC
    CMCON = 0X07; //turn off comp
    timer_init();
}

/* ====== Main loop ======= */
void main(void) {
    
    setup();
    
    while(1);
    {
        __nop;
    }
}

/* ======== END =========  */
