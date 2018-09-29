/* ====== Header =======
 * File:   PIR_alarm.c
 * Author: Gavin Lyons
 * IC: PIC12F675
 * IDE: MPLAB X 5.05
 * Compiler: xc8 v2.00
 *  Description: see URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 28 September 2018, 16:40
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

#define LED GP0 
#define RELAY  GP1 
#define PIR    GP5 
#define  LOW 0
#define  ON  1
#define  OFF 0

/* ======= Globals========*/
uint8_t counter=0;

/* ==== Function prototypes ===== */
void setup(void);
void startdelay(void);
void monitorPIR(void);
void __interrupt() my_ISR(void);

/* ====== Main loop ======= */
void main(void) 
{
    setup();
    startdelay();
    while(1)
    {
        monitorPIR();
    }
}
/* ======== END of MAIN =========  */


/* ====== Functions space ======= */

/* Function: setup , 
 * Function to init PIC
 */
void setup(void)
{
  TRISIO     = 0x20; // GP5 configured as input, all others are output
  GPIO       = 0x00;  //all o/p low
  CMCON      = 0x07; // Turn off All Comparators
  OPTION_REG = 0x87; // 256:1 prescalar
  INTCON     = 0x20; // Enable Timer0 Interrupt 
  ANSEL      = 0x00; // turn off ADC
  TMR0       = 0; //timer register offset to zero
  LED = OFF;
  RELAY = OFF;
            
}

/* Function:  monitorPIR
 * monitor PIR input  if low alarm state activated 
 */
void monitorPIR(void)
{
 if (PIR == LOW)
{
  GIE = 0;
  LED = ON;
  RELAY = ON;
  while(PIR == 0);
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
 * because the PIR sensor requires an initial stabilization time of about 
 * 10 to 60 seconds in order to function properly. 
 */
void startdelay(void)
{
  uint8_t index=0;
  for(index=0; index<60; index++)
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
       if(counter == 80)
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
