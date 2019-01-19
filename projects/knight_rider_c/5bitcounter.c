
/*
 * File:  5bitcounter.c
 * Author: gavin Lyons
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.0
 * pic12F675
 * Created on 19 January 2019, 14:14
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 */


#include <xc.h>

/*define clock freq*/
#define _XTAL_FREQ 4000000  // 4MHZ crystal


// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR master clear reset bit disabled
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)


/*Function Prototypes*/
void setup(void);
void data_submit(char data);

/* Main Loop  */
void main(void) {
    setup();
    char data = 0x00;
    while(1){
        data_submit(data);
        __delay_ms(500);
        data ++;
        if (data == 0x20)
        {
          data = 0x00;
        }
        }
    return;
}
/* END OF MAIN LOOP*/

/* Function Space*/

/*
 * This function will send the data to GPIO pins
 */
void data_submit(char data)
{
    unsigned int i=0;
    char  dataarray[8];
    //extract the bits from  passed data bitmask and   
    for (int i=0 ; i<8 ; i++){
        dataarray[i] = (data >> i) & 0x01; 
        }
    
    //assign bits to  relevant GPIO bits.
    GPIO0=dataarray[0];
    GPIO1=dataarray[1];
    GPIO2=dataarray[2];
    GPIO4=dataarray[3];
    GPIO5=dataarray[4];
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
/* EOF */