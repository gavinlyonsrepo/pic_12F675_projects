
/* ====== Header =======
 * File:  
 * Author: Gavin Lyons
 * IDE: MPLAB X v
 * Compiler: xc8 v
 * Description: see URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 
 */

/* ======= Includes ========*/
#include <xc.h>

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
 #define _XTAL_FREQ 4000000  // 4MHZ internal crystal
 

/* ======= Globals========*/


/* ==== Function prototypes ===== */
void setup(void);

 
/* ====== Main loop ======= */
void main(void) {
    
    setup();
    while(1){
             __nop();
            }
   
    return;
    }
/* ======== End of Main. =========  */

/* ====== Functions space ======= */

 
/* Setup function:
 * Setups the SPECIAL FUNCTION REGISTERS  registers of PIC
 */
void setup (void)
{
    ADCON0 = 0x00;        // Turn off the ADC
    ANSEL = 0x00;         // Turn off ADC
    CMCON = 0x07;        // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO = 0x00;       //  rest all output 
    GPIO=0x00;           // set all pins low
}

/* =========== EOF ============*/
