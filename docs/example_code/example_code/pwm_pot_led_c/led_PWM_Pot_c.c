/*
 * File:   led_PWM_Pot_c.c
 * Author: gavin lyons
 * Url: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 24 August 2018, 23:18
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v2.0
 */
#include <xc.h>
// Define CPU Frequency
// This must be defined, if __delay_ms() or 
// __delay_us() functions are used in the code
#define _XTAL_FREQ   4000000    
#define PWM_Pin    GP0
// Define PWM variable, It can have a value 
// from 0 (0% duty cycle) to 255 (100% duty cycle)
unsigned char PWM = 127;

/*
   PIC TIMER0 Calculator

Clock Source in Mhz                   4 Mhz
Fosc                                  4000000.0 Hz
Fosc / 4                              1000000.0 Hz
Time Period                           1e-06 sec
Prescaler                             32
Timer0 Interrupt Period               0.008192 sec
Period of Frequency Input To Timer0   3.2e-05 sec
Period of Time for each Timer0 Count  0.008192 sec
(1000000/256) * 32 ~= 8mS				
*/

// Config word
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);

/*
 * Function Name: InitADC
 */
void InitADC(void)
{
	ANSEL   = 0x18;	     // Clear Pin selection bits
	TRISIO  = 0x10;      // GP4 input, rest all output
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

/*
 * Function Name: ISR
 */
void interrupt ISR(void)
{
	if(T0IF)  //If Timer0 Interrupt
	{
		if(PWM_Pin)	// if PWM_Pin is high
		{
			PWM_Pin = 0;
			TMR0 = PWM;
		}
		else	     // if PWM_Pin is low
		{
			PWM_Pin = 1;
			TMR0 = 255 - PWM;
		}

		T0IF = 0;   // Clear the interrupt
	}
}


/*
 * Function Name:InitPwm
 */
void InitPWM(void)
{
	// Use timer0 for making PWM
	OPTION_REG &= 0xCC;     // Intialise timer0
	//INTCON     = 0b10100000;     // Global Interrupt Enabled and TMR0 Overflow Interrupt Enabled
	TMR0       = 0         ;     // Preload timer register
	T0IE = 1;				// Enable Timer0 interrupt
	GIE = 1;				// Enable global interrupts
}
// Main function
void main()
{	
	unsigned int ADC_value = 0;
    
	InitADC();		// Initialize GP4 as ADC input pin
	InitPWM();			 // Initialize PWM
    
    while(1)
    {
     ADC_value = GetADCValue();
     if(ADC_value < 5)
     { 
         PWM = 0;
     }
     else {
         PWM = (ADC_value/4);
     }
     
     __delay_ms(500);					// Half second delay before next reading
    
    }
}