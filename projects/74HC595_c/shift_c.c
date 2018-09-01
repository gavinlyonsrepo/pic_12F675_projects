/*
 * File:   shift_c.c
 * Function: PIC12F675 8-bit binary counter, LED Array and  shift register
 * Author: Gavin Lyons
 * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 31 August 2018, 19:34
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 */

// Complier  xc8 v1.45
#include <xc.h>

// CONFIGURATION WORD setup
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);

/*define clock freq*/
#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif

// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //serial data in pin 14 
#define RCLK_595 GP1  // storage register clock input pin 12 "latch" 
#define SCLK_595 GP2 //shift register clock input pin 11 "storage"

/*
 *This function clock will enable the Clock.
 */
void sclock(void){
    SCLK_595 = 1;
    __delay_us(500);
    SCLK_595 = 0;
    __delay_us(500);
}
/*
 *This function  will strobe and enable the output trigger.
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
    TRISIO=0x00;         // set as output 
    GPIO=0x00;           // set all pins low
}

/* Main loop */
void main(void) {
    setup();  
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
