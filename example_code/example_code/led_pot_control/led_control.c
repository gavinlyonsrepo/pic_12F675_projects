/*
 * File:   led_control.c.c
 * Author: Gavin Lyons
 * Url: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 12 January 2019, 17:13
 * IDE: : MPLAB X IDE v5.05 
 * Compiler: xc8 v2.0
 */

/* ======= Includes ========*/
#include <xc.h>

/*== define clock freq === */
#define _XTAL_FREQ   4000000    

/* ======== Define and Pragma Directives   ======== */

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

/*GPIO function
 LED1  GP0
 LED2  GP1
 LED3  GP2
 n/c   GP3
 POT1  GP4
 LED5  GP5
*/


/* ======= Globals======== */
char led_Array[5] = {0x00,0x01,0x03,0x07,0x27};

/* ==== Function prototypes ===== */
void setup(void);
unsigned int GetADCValue(void);
void LEDLight(int counter);

/* ====== Main loop ======= */
void main()
{	
	setup();		
    unsigned int ADC_value = 0;
    unsigned int  counter =0;
    while(1)
    {
         //get ADC value
        ADC_value =  GetADCValue();
           if (ADC_value <=99) 
           { 
              counter = 0x00;
           }else if  (ADC_value >=100 && ADC_value <=300)
           {
                counter = 0x01;
           }else  if (ADC_value >=301 && ADC_value <=500)
           {
               counter = 0x02;  
           }else if (ADC_value >501 && ADC_value <=700)
           {
               counter = 0x03; 
           }else if (ADC_value >=701 && ADC_value <=1024)
           {
              counter = 0x04;  
               
           }
     LEDLight(counter);
     counter = 0x00;
     __delay_ms(500);// Half second delay before next reading
    
    }
}
/* ======== END of MAIN =========  */


/* ====== Functions space ======= */


/*
 * Function Name: LEDLight
 */
void LEDLight(int counter)
{
    GPIO  = led_Array[counter]; 
}

/*
 * Function Name: InitADC
 */
void setup(void)
{
	ANSEL   = 0x18;	     // Clear Pin selection bits
	TRISIO  = 0x10;      // GP4 input, rest all output
	GPIO  = 0x00;
    ADCON0 = 0x81;		 // Turn on the A/D Converter ADFM and ADON
	CMCON  = 0x07;		 // Shut off the Comparator, so that pins are available for ADC
	VRCON  = 0x00;	     // Shut off the Voltage Reference for Comparator
}

/*
 * Function Name: GetADCValue
 */
unsigned int GetADCValue(void)
{
	ADCON0 &= 0xf3;      // Clear Channel selection bits 
    ADCON0 |= 0x0c;      // Select GP4 pin as ADC input CHS1:CHS0: to 11
    
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE);     //wait for conversion completion

	return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}

/* =========== EOF ============*/