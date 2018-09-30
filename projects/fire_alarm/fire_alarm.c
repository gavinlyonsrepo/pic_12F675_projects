
/* ====== Header =======
 * File:   fire_alarm.c
 * Author: Gavin Lyons
 * IC: PIC12F675
 * IDE: MPLAB X 5.05
 * Compiler: xc8 v2.00
 *  Description: see URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 *  Created on 30 September 2018, 18:33
 */

/* ======= Includes ========*/
#include <xc.h>
#include <stdint.h> /* For uint8_t definition */

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

/* GPIO pins*/
#define LED GP0 
#define RELAY  GP1 
// Note: ADC is on GP4
#define FIRE    GP5 

#define  ON  1
#define  OFF 0

/* ======= Globals========*/
uint8_t counter=0;

/* ==== Function prototypes ===== */
void setup(void);
void startdelay(void);
void monitorfire(void);
void __interrupt() my_ISR(void);
unsigned int GetADCValue(void);

/* ====== Main loop ======= */
void main(void) 
{
    setup();
    startdelay();
    while(1)
    {
        monitorfire();
    }
}
/* ======== END of MAIN =========  */


/* ====== Functions space ======= */

/* Function: setup , 
 * Function to init PIC
 */
void setup(void)
{
  TRISIO     = 0x30;  // GP5 GP4 configured as input, all others are output
  GPIO       = 0x00;  //all o/p low
  ADCON0     = 0x81; // Turn on the A/D Converter ADFM and ADON
  ANSEL      = 0x18; // Clear Pin selection bits
  CMCON      = 0x07; // Turn off All Comparators
  OPTION_REG = 0x87; // 256:1 prescalar
  INTCON     = 0x20; // Enable Timer0 Interrupt 
  TMR0       = 0; //timer register offset to zero
  LED = OFF;
  RELAY = OFF;
            
}

/* GetADCValue:
 * Gets the ADC value from GP4 , returns it as unsigned int 0-1023 
 */
unsigned int GetADCValue(void)
{
    ADCON0 |= 0x0c;      // Select GP4 pin as ADC input CHS1:CHS0: to 11
    
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE);     //wait for conversion completion
    return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}

/* Function:  monitorfire
 */
void monitorfire(void)
{
 uint16_t ADC_value = 0;
if (FIRE == 1)
{
  ADC_value =  GetADCValue();
  if (ADC_value <= 100) 
        {
             GIE = 0;
             LED = ON;
             RELAY = ON;
            while(FIRE == 1);
        }
}
else
{
  LED = OFF;
  RELAY = OFF;
  GIE = 1; //INTCON register global interrupt enable
 }
}

/*function : startdelay 
 * Delay at start, This initial delay is introduced deliberately to avoid 
 * false triggerings, 
 * because the fire sensor requires an initial stabilization time of about 
 * 10 seconds in order to function properly. 
 */
void startdelay(void)
{
  uint8_t index=0;
  for(index=0; index<30; index++)
    {
     LED = ON;
     __delay_ms(500);        // LED blink 
     LED = OFF;
     __delay_ms(500);
    }
  LED = OFF;
  GIE = 1; //INTCON register global interupts on
}

/* Function ISR
 * to handle timer0 overflow
 */
void __interrupt() my_ISR(void)
{
   GIE = 0; 
    if (T0IF)  
     {
       counter++;
       if(counter == 160)
         {
          LED = ON;
          __delay_ms(80);
          LED = OFF;
          counter = 0;
         }
       }
    T0IF = 0; //INTCON register overflow flag
    GIE = 1; //INTCON global interupt. 
  }

/* =========== EOF ============*/

