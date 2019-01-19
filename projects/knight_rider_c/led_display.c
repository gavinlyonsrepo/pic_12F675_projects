/* ====== Header =======
 * File:   led_display.c
 * Author: Gavin lyons
 * Created on 20 January 2019, 16:11
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.0
 * PIC12f675 : LED display project, 3 modes: count, random, knight rider.
 */

/* ======= Includes ========*/
#include <xc.h>
#include <stdlib.h> // for  rand()


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
#define _XTAL_FREQ 4000000 // 4MHZ crystal

/* ======= Globals========*/
unsigned int counter = 0;
unsigned int counter_knight = 0;
char led_Array[12] = {0x00,0x01,0x02,0x04,0x10,0x20,0x21,0x33,0x12,0x37,0x36,0x14};

/* Function Prototypes*/
void setup(void);
void data_submit(char data); //count
void count_mode(void); //count
void ledon(void);//random
void ledon_knight(void); //knightrider

/* Main Loop */
void main(void) {
    setup();
    while(1)
    {
       //count mode
       count_mode();
       counter = 0;
       //knight rider  mode
       ledon_knight(); 
       counter = 0;
       //random mode
       srand(TMR0);
       ledon(); 
       counter = 0;
       
    }
    
    return;
}
/* End of main */


/* Function Space */

/* Setup function: setups PIC12f675*/
void setup (void)
{
    ADCON0=0x00;         // Internal ADC OFF
    ANSEL=0x00;          // All Analog selections pins are assigned as digital I/O
    CMCON = 0x07;		 // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO=0x08;         // set as output except gp3
    GPIO=0x00;           // set all pins low
    OPTION_REG &= 0xCC;  // Intialize timer0 b11001100
    TMR0 = 0 ; // Preload timer register
}

/*
 * Data_submit
 * This function is part of the count mode 
 * will send the data to GPIO pins
 */
void data_submit(char data)
{
    unsigned int i=0;
    char  dataarray[8];
    //extract the bits from  passed data bitmask and   
    for (int i=0 ; i<8 ; i++){
        dataarray[i] = (data >> i) & 0x01; 
        }
    
    //assign extracted bits to  relevant GPIO bits.
    GPIO0=dataarray[0];
    GPIO1=dataarray[1];
    GPIO2=dataarray[2];
    GPIO4=dataarray[3];
    GPIO5=dataarray[4];
}

/* function for 5 bit binary count mode*/
void count_mode(void)
{
    char data = 0x00;
    
    while(counter!=5){
        data_submit(data);
        __delay_ms(1000);
        data ++;
        if (data == 0x20)
        {
            counter ++;
            data = 0x00;
        }
    }
}
/* function to toggle LED patterns
 this is part of random  mode*/
void ledon(void)
{ 
    unsigned char pick=0;
    
    while(counter!=15)
    {
    pick = rand() % 12;
     switch (pick)
        {
         case 0: GPIO = led_Array[pick]; break;
         case 1: GPIO = led_Array[pick]; break;
         case 2: GPIO = led_Array[pick]; break;
         case 3: GPIO = led_Array[pick]; break;
         case 4: GPIO = led_Array[pick]; break;
         case 5: GPIO = led_Array[pick]; break;
         case 6: GPIO = led_Array[pick]; break;
         case 7: GPIO = led_Array[pick]; break;
         case 8: GPIO = led_Array[pick]; break;
         case 9: GPIO = led_Array[pick]; break;
         case 10: GPIO = led_Array[pick]; break;
         case 11: GPIO = led_Array[pick]; break;
        } 
        __delay_ms(1000);
        counter++;
    }
}

/* function to toggle leds patterns
 part of knight rider mode*/
void ledon_knight(void)
{ 
    char led_Array_knight[8] = {0x01,0x02,0x04,0x10,0x20,0x10,0x04,0x02};
    while(counter!=80)
    {
        GPIO = led_Array_knight[counter_knight];
		counter_knight++;
		if (counter_knight==8) counter_knight=0;
        __delay_ms(500);
        counter ++;
    }
}
/* EOF */