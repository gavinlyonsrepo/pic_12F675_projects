
/*
 * File:   led_pwm.c
 * Author: gavin lyons
 *  Purpose  : Main file for PWM code for PIC12F675 using timer0.
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 
 * Created on 24 August 2018, 18:59
 * Url: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */

#include <xc.h>

// Config word
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);


// Define CPU Frequency
// This must be defined, if __delay_ms() or 
// __delay_us() functions are used in the code
#define _XTAL_FREQ   4000000    
// Define PWM pin
#define PWM_Pin    GP4
#define usdelay  10
// Define PWM variable, It can have a value 
// from 0 (0% duty cycle) to 255 (100% duty cycle)
unsigned char PWM = 0;

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


void InitPWM(void)
{
	// Use timer0 for making PWM
	//make prescaler 1:2
	OPTION_REG &= 0xC0;     // Intialise timer0
	
	T0IE = 1;				// Enable Timer0 interrupt
	GIE = 1;				// Enable global interrupts
}

// Main function
void main()
{	
	ANSEL  = 0x00;       // Set ports as digital I/O, not analog input
	ADCON0 = 0x00;		 // Shut off the A/D Converter
	CMCON  = 0x07;		 // Shut off the Comparator
	VRCON  = 0x00;	     // Shut off the Voltage Reference
	TRISIO = 0x00;       // All output
	GPIO   = 0x00;       // Make all pins 0
	
	InitPWM();			 // Initialize PWM

	// PWM=0 means 0% duty cycle and 
	// PWM=255 means 100% duty cycle
	//PWM = 127;			 // 50% duty cycle 
	int d = 1;
	// cycle PWM from 255 to 0 to 255 to etc
	while (1) {
	PWM += d;
	if(PWM == 255) d = -1;
	__delay_ms(usdelay);
	if(PWM ==   0) d = 1;
  }
	
}
