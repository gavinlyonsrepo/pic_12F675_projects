/*
 * File:   shift_c.c
 * Function: PIC12F675 8-bit binary counter, LED Array and  shift register
 * Author: Gavin Lyons
 * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 31 August 2018, 19:34
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.0
 */

// Complier  xc8 v2.0
#include <xc.h>

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)


/*define clock freq*/
#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif


// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //serial data in pin 14 
#define RCLK_595 GP1  // storage register clock input pin 12 "latch" 
#define SCLK_595 GP2 //shift register clock input pin 11 "storage"

/*
 *This function clock will enable the storage Clock.
 */
void sclock(void){
    SCLK_595 = 1;
    __delay_us(500);
    SCLK_595 = 0;
    __delay_us(500);
}
/*
 *This function will latch and enable the output trigger.
 */
void rclock(void){
    RCLK_595 = 1;
    __delay_us(500);
    RCLK_595 = 0;
    }

/*
 * This function will send the data to shift register
 */
void data_submit(unsigned int data){
    for (int i=0 ; i<8 ; i++){
        SER_595 = (data >> i) & 0x01;
        sclock(); 
    }
    rclock(); // Data finally submitted 
}


/* Setup function*/
void setup (void)
{
    ADCON0=0x00;         // Internal ADC OFF
    ANSEL=0x00;          // All Analog selections pins are assigned as digital I/O
    CMCON = 0x07;		 // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO=0x08;         // set as output except gp3
    GPIO=0x00;           // set all pins low
}


/* check button function , 
 if Button is pressed at startup turn all LEDs on*/
void checkbutton (void)
{
       if(GPIO3 == 0) //If Switch is pressed
        {
          __delay_ms(50); //Provides required delay
          if(GPIO3 == 0) //If Switch is still pressed
          {
                while(1){
                    data_submit(0xFF);
                }
          }
        }
}

/* Main loop */
void main(void) {
    setup();  
    checkbutton();
    unsigned int data = 0x00;
    while(1){
        data_submit(data);
        __delay_ms(500);
        data ++;
        if (data == 0xFF)
        {
          data = 0x00;
        }
        }
    return;
    }
// EOF
