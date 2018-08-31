/*
 * File:   dice.c
 * Function: PIC12F675 dice sim.
 * Author: Gavin Lyons
 * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 31 August 2018, 13:34
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 */

// Complier  xc8 v1.45
#include <xc.h>
#include <stdlib.h> // for  rand()

// CONFIG ? CONFIGURATION WORD (ADDRESS: 2007h)
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_OFF & CP_OFF & CPD_OFF);

/*define clock freq*/
#ifndef _XTAL_FREQ
  #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif

/* pins layout*/
#define LED_A  GP0
#define LED_B  GP1
#define LED_C  GP2
#define LED_D  GP4
#define push_button GP5

/* Numbers : label : GPIO o/ps
 One: LED_A 0x01 b00000001
 Two: LED_B 0x02 b00000010
 Three: LED_A + LED_B 0x03 b00000011
 Four: LED_B + LED_C 0x06  b00000110
 Five:LED_A + LED_B + LED_C 0x07 b00000111
 Six:LED_A + LED_B + LED_C + LED_D  0x17 b00010111
 */
// Array to hold LEd  patterns to make up dice.
unsigned char led_Array[6] = {0x01,0x02,0x03,0x06,0x07,0x17};

/* setup function*/
void setup (void)
{
    ADCON0=0x00;         // Internal ADC OFF
    ANSEL=0x00;          // All Analog selections pins are assigned as digital I/O
    CMCON = 0x07;		 // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO=0x20;         // set as output except bit 2 GP5=i/p push button
    GPIO=0x20;           // set all pins low except GP5
    OPTION_REG &= 0xCC;  // Intialize timer0 b11001100
    TMR0 = 0 ;           // Preload timer register
}

/* Generate random number and apply to GPIO ports*/
void numPick(void)
{
    unsigned char dice=0;
    dice = rand() % 6;
     switch (dice)
        {
         case 0: GPIO = led_Array[dice]; break;
         case 1: GPIO = led_Array[dice]; break;
         case 2: GPIO = led_Array[dice]; break;
         case 3: GPIO = led_Array[dice]; break;
         case 4: GPIO = led_Array[dice]; break;
         case 5: GPIO = led_Array[dice]; break;
        }   
     __delay_ms(500);
}

/* main loop*/
void main(void)
{
    __delay_ms(50);
    setup();
     do
      {
        if(push_button == 0) //If Switch is pressed
        {
          __delay_ms(75); //Provides required delay
          if(push_button == 0) //If Switch is still pressed
          {
              srand(TMR0); //seed random number every button press with timer value
              numPick();
          }
        }
      }while(1);

}
// EOF