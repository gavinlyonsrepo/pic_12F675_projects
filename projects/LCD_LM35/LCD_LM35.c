/* ====== Header =======
 * File:   LCD_LM35.c
 * Author: Gavin Lyons
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.05
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on on 10 February 2019, 20:24
 */

/* ======= Includes ========*/
#include <xc.h>
#include <stdint.h> /* For uint8_t definitions etc */
#include <stdio.h> /* for sprintf */

/* ======== Define and Pragma Directives   ======== */

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF     // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF    // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF    // MCLR
#pragma config BOREN = OFF    // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF       // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF      // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000  // 4MHZ internal crystal
 
#define SDATA GPIO2 //pin 5 to SER pin 14 
#define SCLK GPIO1 //pin 6 to SCLK  pin 11
#define RCLK GPIO0 //pin 7 to RCLK pin 12

/* ======= Globals========*/
unsigned char dataout;


/* ==== Function prototypes ===== */
void setup(void);
//Shift register 595
void shiftout(unsigned char ch);
//LCD
void LCDtoggle(void);
void LCDnibbles(unsigned char ch);
void LCDcmd(unsigned char cmd);
void LCDdata(unsigned char data);
void LCDinit(void);
void LCDprint(const char* str);
void LCDgoto(char x, char y);
//ADC LM35
unsigned int GetADCValue(void);
void DisplayData(void);

/* ====== MAIN LOOP ======= */
void main(void) {
    
   setup();
   LCDinit(); 
   __delay_ms(10);
   while(1)
   {
       DisplayData();
        __delay_ms(1000);
   }
   return;
    }
/* ======== End of Main. =========  */


/* ====== FUNCTIONS SPACE ======= */

 
/* Setup function:
 * Setups the SPECIAL FUNCTION REGISTERS  registers of PIC
 */
void setup (void)
{
    ANSEL = 0x18;  
    ADCON0 = 0x81;       // Turn on the A/D Converter ADFM and ADON
    CMCON = 0x07;        // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO = 0x10;       //  rest all output but GP4
    GPIO = 0x00;           // set all pins low
}

/* Function name : DisplayData
 * Get value from LM35 sensor and display it to LCD
 */
void DisplayData(void)
{
        unsigned int  ADC_value = 1;
        uint16_t  temperature= 0;
        char str1[3];
        char str2[3];
        ADC_value = GetADCValue();
        temperature=(ADC_value*49);
        sprintf(str1, "%u%u", (temperature/1000)%10, (temperature/100)%10);
        sprintf(str2, "%u%u", (temperature/10)%10, (temperature/1)%10);
        LCDgoto(0,0);
        LCDprint("Temperature");
        LCDgoto(0,2);
        LCDprint(str1);
        LCDprint(".");
        LCDprint(str2);
        LCDprint("'");
        LCDprint("C");
        
}

/*
 * Function Name: GetADCValue :
 * Get ADC value from GP4 and return it as 
 * unsigned int.
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

/* Function name : shiftout
 * Shift out data to shift register
 */
void shiftout(unsigned char ch)
   {
   char x;
   unsigned char dummy = ch;
   for(x=0;x<8;x++)
       {
       SDATA = 0;
       if(dummy & 0x80) SDATA = 1;
       SCLK = 1;
       __nop();
       SCLK = 0;
       dummy<<=1;    
       }
   RCLK = 1;
   __nop();
   RCLK = 0;
   }

//flip the bit RW The control pin R/W determines if the data transfer between the LCD module and 
//an external microcontroller are actual character data or command/status.
void LCDtoggle(void)
   {
   dataout ^= 0x10;
   shiftout(dataout);
   dataout ^= 0x10;
   shiftout(dataout);
   }

/* Function Name :Write_LCD_Nibble
 *  Used by LCDData() and LCD_Cmd() 
 * functions to send LCD data and command as two nibbles.
*/
void LCDnibbles(unsigned char ch)
   {
   dataout &= 0xF0;
   dataout += (ch>>4) & 0xF;
   shiftout(dataout);
   LCDtoggle();
   dataout &= 0xF0;
   dataout += ch & 0xF;
   shiftout(dataout);
   LCDtoggle();
   }

/* Function Name : Write_LCD_Cmd
 *  Writes a command byte to the LCD module.
 */
void LCDcmd(unsigned char cmd)
   {
   dataout = 0;
   LCDnibbles(cmd);
   __delay_us(100);
   }

/* Function Name : Write_LCD_Data 
 * Sends a character byte to display at current cursor position.
 */
void LCDdata(unsigned char data)
   {
   dataout = 0x20;
   LCDnibbles(data);
   __delay_us(100);
   }

/* Function Name : LCDinit
 * Initializes the 16×2 character LCD module to operate into 4-bit mode,
 * 2 lines display, 5×7 size character, display ON, with cursor OFF.
 */
void LCDinit(void)
   {
   __delay_ms(15);
   dataout = 2;
   LCDtoggle(); // Wake-Up Sequence
   __delay_ms(5);
   LCDtoggle();
   __delay_ms(5);
   LCDtoggle();
   __delay_ms(5);
   LCDcmd(0x28); // 4-bits, 2 lines, 5x7 font
   LCDcmd(0xC); // Display ON, No cursors
   LCDcmd(0x6); // Entry mode- Auto-increment, No Display shifting
   LCDcmd(0x1); 
   }
 
/* Function name LCDprint :
 *  Writes a character string at the current cursor position.
 */
void LCDprint(const char* str)
   {
   while(*str != 0)
       LCDdata(*str++);
   }

/* Function name LCDgoto
 * Changes the current cursor position
 */
void LCDgoto(char x, char y)
   {
   char addr = 0x80;
   if(y==2) addr = 0xC0;
   addr+=x;
   LCDcmd(addr);
   }
/* =========== EOF ============*/
