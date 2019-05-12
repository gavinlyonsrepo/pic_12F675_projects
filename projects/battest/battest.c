
/* ====== Header =======
 * File: Battery level tester 
 * Author: Gavin Lyons
 * IDE: MPLAB X v5.05
 * Compiler: xc8 v2.05
 * Description: see URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 01 March 2019, 15:23
 */

/* ======= Includes ========*/
#include <xc.h>
#include <stdint.h>

/* ======== Define and Pragma Directives   ======== */

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = ON     // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

/*define clock freq*/
 #define _XTAL_FREQ 4000000  // 4MHZ internal crystal

// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //pin 7 to serial data in pin 14 
#define RCLK_595 GP1  //pin 6 to  storage register clock input pin 12 "latch" 
#define SCLK_595 GP2 //pin 5 to shift register clock input pin 11 "storage"

//seven segment symbols
#define sym_b 0x7C     // b fgedcba 01111100 
#define sym_E 0x79     // E fgedcba 01111001 
#define sym_DASH 0x40  // - fgedcba 01000000
#define sym_BOT_DASH 0x10  // _ fgedcba 00010000

/* ======= Globals========*/
 char data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
unsigned int ADC_value = 0;

/* ==== Function prototypes ===== */
void setup(void);
void sclock(void);
void rclock(void);
void data_display(unsigned int data);
void ADCData(void);
unsigned int GetADCValue(void);

/* ====== Main loop ======= */
void main(void) {
    
    setup();
 
    while(1){
       ADC_value = GetADCValue();
        ADCData();
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
    ADCON0 = 0x81;        // Turn on the A/D Converter ADFM and ADON
    ANSEL = 0x18;         // Clear Pin selection bits
    CMCON = 0x07;        // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO = 0x10;       //  Gp4 input rest all output 
    GPIO   = 0x00;           // set all pins low
     data_display(sym_BOT_DASH);
    __delay_ms(50);
}

/* ADCData:
 * This function will talk the ADc data and convert it to voltage 
 * and parse for display function.
 */
void ADCData(void)
{ 
     uint8_t  digit1, digit2, digit3 , digit4;
    ADC_value = (ADC_value*49)/100;
    //digit1 = (ADC_value/1000)%10; always zero not needed
    digit2 = (ADC_value/100)%10;
    digit3 = (ADC_value/10)%10;
    digit4 =  ADC_value%10;
    
    data_display(sym_b); // B e for begin
     __delay_ms(1000);
    //data_display(data[digit1]);   always zero not needed
    // __delay_ms(1000); always zero not needed
    data_display(data[digit2]);
     __delay_ms(1000);
     data_display(sym_DASH); //dash for decimal point
     __delay_ms(1000);
    data_display(data[digit3]);
     __delay_ms(1000);
    data_display(data[digit4]);
     __delay_ms(1000);
    data_display(sym_E); // E for end
     __delay_ms(1000);   

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

	while(GO_nDONE);

            //wait for conversion completion
    return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}
 
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


/* =========== EOF ============*/