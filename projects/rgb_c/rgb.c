/* ====== Header =======
 * File:   rgb.c
 * Author: Gavin Lyons
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 07 September 2018, 14:25
 */

/* ======= Includes ========*/
#include <xc.h> // Complier  xc8 v1.45
#include <stdint.h>

/* ======== Define and Pragma Directives   ======== */

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

/*define clock freq*/
#define _XTAL_FREQ 4000000 // 4MHZ internal crystal

/* ======= Globals========*/

uint8_t  LED_pattern[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x6,0x07};
unsigned int ADC_value = 0;
uint8_t counter=0;

/* ======== Function space ===========*/

/* Setup function */
void setup(void)
{
    ADCON0 = 0x81;     // Turn on the A/D Converter ADFM and ADON
    ANSEL =  0x18; // Clear Pin selection bits
	CMCON  = 0x07;		 // Shut off the Comparator
	VRCON  = 0x00;	     // Shut off the Voltage Reference
	TRISIO = 0xF8;       // gp0 Gp1  Gp2 ouputs
    GPIO = 0x00;         // Make all pins low
}

/* GetADCValue:
 * Gets the ADC value from GP4 , returns it as unsigned int 0-1023 
 */
unsigned int GetADCValue(void)
{
	//ADCON0 &= 0xf3;      // Clear Channel selection bits 
    ADCON0 |= 0x0c;      // Select GP4 pin as ADC input CHS1:CHS0: to 11
    
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE);     //wait for conversion completion
    return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}

/* applys the LED pattern to GPIO port 
 increments counter and applies delay, 
 length of delay depends on ADC result*/
void rgb_func(void)
{
    ADC_value = GetADCValue();
    
   if (ADC_value <= 100) 
        {
            ADC_value = 1;
        }else if (ADC_value >= 999)
        {
             ADC_value = 9;
        } else
        {
         ADC_value = (ADC_value/100);
        }
            
    GPIO = LED_pattern[counter];
    
    for(unsigned int i = 0 ; i < ADC_value; i++)
        {
            __delay_ms(500); 
         }
    counter ++;
    if (counter == 8)
    {
        counter = 0;
    }
}

/* ====== Main loop ======= */
void main(void) 
{
    setup(); 
    while(1){ 
       rgb_func();
    }
    
}
/* ======== END =========  */