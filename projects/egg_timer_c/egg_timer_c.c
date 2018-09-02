 
/* ====== Header =======
 * File:   egg_timer_c.c
 * Author: Gavin Lyons
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 02 September 2018, 13:02
 */


/* ======= Includes ========*/
#include <xc.h> // Complier  xc8 v1.45

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
// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //serial data in pin 14 
#define RCLK_595 GP1  // storage register clock input pin 12 "latch" 
#define SCLK_595 GP2 //shift register clock input pin 11 "storage"
//  Interfacing push button and Buzzer
#define push_button GP3 // push button
#define buzzer GP5  // Buzzer


/* ======= Globals========*/
 char data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
  unsigned int ADC_value = 0;
 
 /* ======== Function space ===========*/
 
/* sclock:
 * This function clock will enable the storage Clock to 74HC595
 */
void sclock(void){
    SCLK_595 = 1;
    __delay_us(500);
    SCLK_595 = 0;
    __delay_us(500);
}
/* rclock:
 * This function will strobe/latch and enable the output trigger of 74HC595
 */
void rclock(void){
    RCLK_595 = 1;
    __delay_us(500);
    RCLK_595 = 0;
    }

/* data_display:
 * This function will send the data to serial line 74HC9595
 */
void data_display(unsigned int data){
    for (int i=0 ; i<8 ; i++){
        SER_595 = (data >> i) & 0x01; // bit shift and bit mask data. 
        sclock(); //enable data storage clock
    }
    rclock(); // Data latch
}

/* Setup function:
 * Setups the SPECIAL FUNCTION REGISTERS  registers of PIC
 */
void setup (void)
{
    ADCON0 = 0x81;        // Turn on the A/D Converter ADFM and ADON
    ANSEL = 0x18;        // Clear Pin selection bits
    CMCON = 0x07;		 // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO = 0x18;       // GP4 and GP3 input, rest all output 011000
    GPIO=0x00;           // set all pins low
}

/* GetADCValue:
 * Gets the ADC value from GP4 , returns it as unsigned int 0-1023 
 */
unsigned int GetADCValue(void)
{
	//ADCON0 &= 0xf3;      // Clear Channel selection bits 
    ADCON0 |= 0x0c;      // Select GP4 pin as ADC input CHS1:CHS0: to 11
    
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE);     //wait for conversion completion
    return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}

/* start timer:
 * Function to deal with timer countdown and buzzer  
 */
void start_timer(void)
{
    while(1)
    {
    
        for(unsigned int i = 0 ; i < 2; i++)
        {
            __delay_ms(30000); // wait a minute
        }
    ADC_value --; //decrement countdown
    data_display(data[ADC_value]); // display new value.
        if (ADC_value== 0) // is it zero
        {
            data_display(0x5E); //display d for done
            buzzer = 1; // set buzzer on
                 for(unsigned int i = 0 ; i < 4; i++)
                        {
                       __delay_ms(30000); // wait a minute
                        } // leave buzzer on fro two minutes
            buzzer = 0; 
            while(1)
            {
                __nop; // wait for hard reset by user.
            }
        }
    }
}

/* Push_button_check
 * Function to check and debounce push button press
 */
void push_button_check(void)
{
     if(push_button == 0) //If Switch is pressed
     {
         __delay_ms(75); //Provides required delay
        if(push_button == 0)
        {
            buzzer = 1;
            __delay_ms(500); // beep buzzer to let user now time started
            buzzer = 0;
            start_timer();
        }
        
     }
}

/* ====== Main loop ======= */
void main(void) {
    setup();  
    while(1){
        //get ADC value
        ADC_value =  GetADCValue();
        if (ADC_value <= 100) 
        {
            ADC_value = 1;
        }else if (ADC_value >= 999)
        {
             ADC_value = 9;
        } else
        {
         ADC_value = (ADC_value/100);
        }
        // Display to LED seven segment
        data_display(data[ADC_value]);
        //Check Push button
        push_button_check();
        __delay_ms(1000);
    }
    return;
    }
/* ======== END =========  */