
/*
 * File: LDR.c
 * Function: PIC12F675 LDR test code
 * Author: Gavin Lyons
 * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 13 January 2019, 21:39
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.0
 */

// Complier  xc8 v2.0
#include <xc.h>

/*== define clock freq === */
#define _XTAL_FREQ 4000000 

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

#define  LED1 GP0

/* ==== Function prototypes ===== */
void setup(void);
unsigned int GetADCValue(void);


/* ====== Main loop ======= */
void main(void) {
	setup();
	 unsigned int ADC_value = 0;
	 while(1)
	 {
		 ADC_value = GetADCValue();
		 if (ADC_value >= 500)
		 {
			 LED1 =  1;
		 }else
		 {
			 LED1 =  0;
		 }
		 __delay_ms(500);
	 }
	return;
}
/* ======== END of MAIN =========  */


/* ====== Functions space ======= */


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

	ADCON0 |= 0x0c;      // Select GP4 pin as ADC input CHS1:CHS0: to 11
	
	__delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE);     //wait for conversion completion

	return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}

/* =========== EOF ============*/
