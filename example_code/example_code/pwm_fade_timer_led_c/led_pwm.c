
/*
 * File: led_pwm.c
 * Author: Gavin Lyons
 * PIC: PIC12F675
 * Purpose: File for LED fade using PWM code and timer0 see URL for more details
 * IDE: MPLAB X v4.2
 * Compiler: xc8
 * Created on 24 August 2018, 18:59
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */

#include <xc.h>

// Config word
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);

// Define CPU Frequency
#define _XTAL_FREQ   4000000
// Define PWM pin
#define PWM_Pin    GP4
#define usdelay  10
// Define PWM variable, It can have a value
// from 0 (0% duty cycle) to 255 (100% duty cycle)
unsigned char PWM = 255;

// function to setup PIC
void setup(void)
{
    ANSEL  = 0x00;       // Set ports as digital I/O, not analog input
    ADCON0 = 0x00;       // Shut off the A/D Converter
    CMCON  = 0x07;       // Shut off the Comparator
    VRCON  = 0x00;       // Shut off the Voltage Reference
    TRISIO = 0x00;       // All GPIO output
    GPIO   = 0x00;       // Make all pins low
    WPU    = 0;          // Disable all weak pull up
    InitPWM();           // Initialize PWM
}

// Function to handle interrupt on timer0 overflow.
void interrupt ISR(void)
{
    if(T0IF)  //If Timer0 Interrupt
    {
        if(PWM_Pin) // if PWM_Pin is high
        {
            PWM_Pin = 0;
            TMR0 = PWM;
        }
        else         // if PWM_Pin is low
        {
            PWM_Pin = 1;
            TMR0 = 255 - PWM;
        }
        T0IF = 0;   // Clear the interrupt
    }
}

//Function to init Timer0
void InitPWM(void)
{
    // Use timer0 for making PWM
    OPTION_REG &= 0xCC;     // Intialise timer0
    TMR0 = 0;         // Preload timer register
    T0IE = 1;               // Enable Timer0 interrupt
    GIE = 1;                // Enable global interrupts
}

// Main function
void main()
{
    setup();
    int d = 1;
    
    // cycle PWM from 255 to 0 to 255 to etc
    // PWM=0 means 0% duty cycle 
    //PWM = 127 means 50% duty cycle
    // PWM=255 means 100% duty cycle
    while (1) {
        PWM += d;
        if(PWM == 255) d = -1;
        __delay_ms(usdelay);
        if(PWM ==   0) d = 1;
  }

}
//  EOF
