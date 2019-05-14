/*
 * File:  LED_display.c
 * Function: PIC12F675 led display 3 modes 
 * Author: Gavin Lyons
 * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 31 Jan 2019, 18:34
 * IDE: MPLAB X v5.15
 * Compiler: xc8 v2.05
 */

#include <xc.h>
#include <stdint.h> /* For uint8_t definitions etc */

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000  // 4MHZ crystal

// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //serial data in pin 14 
#define RCLK_595 GP1  // storage register clock input pin 12 "latch" 
#define SCLK_595 GP2 //shift register clock input pin 11 "storage"

#define DEBOUNCE_DELAY 50
#define CHANGE_DELAY 500 
#define SHIFT_COUNT_DELAY 500
#define NUMBER_LOOP 5

/* Function Prototypes */
void sclock(void);
void rclock(void);
void data_submit(uint8_t data);
void setup(void);
void checkbutton(void);
void CountUp(void);
void CountDown(void);
void KnightRider(uint8_t num_loop);
void KnightRiderMode2(uint8_t num_loop);
void KnightRiderMode3(uint8_t num_loop);
void Flash(uint8_t num_loop);

/* Main loop */
void main(void) 
{
    setup();
    checkbutton();

    while (1) 
    {
        CountUp();
        __delay_ms(CHANGE_DELAY);
        CountDown();
        KnightRider(NUMBER_LOOP);
        KnightRiderMode2(NUMBER_LOOP);
        KnightRiderMode3(NUMBER_LOOP);
        Flash(NUMBER_LOOP);
    }
    return;
}
/* End of Main Loop */


/* Function Space */

/* Setup function*/
void setup(void) {
    ADCON0 = 0x00; // Internal ADC OFF
    ANSEL = 0x00; // All Analog selections pins are assigned as digital I/O
    CMCON = 0x07; // Shut off the Comparator
    VRCON = 0x00; // Shut off the Voltage Reference
    TRISIO = 0x08; // set as output except gp3
    GPIO = 0x00; // set all pins low
}

/* Function: knight rider , LED chaser  mode no3*/
void KnightRiderMode3(uint8_t num_loop)
{
    uint8_t counter = 0;
    char Led_Pattern[7] = {0x88, 0x44, 0x22, 0x11, 0x22, 0x44, 0x88};
    /* 10001000 01000100 00100010 00010001 */       
     for (uint8_t i = 0; i < num_loop; i++) 
    {
        for (counter = 0; counter < 7; counter ++) 
            {
            data_submit(Led_Pattern[counter]);
            __delay_ms(CHANGE_DELAY);
            }
    }
}


/* Function: knight rider , LED chaser  mode*/
void KnightRider(uint8_t num_loop) 
{
    uint8_t counter = 0;
    char Led_Pattern[14] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02};
    
     for (uint8_t i = 0; i < num_loop; i++)  
    {
        for (counter = 0; counter < 14; counter ++) 
            {
            data_submit(Led_Pattern[counter]);
            __delay_ms(CHANGE_DELAY);
            }
    }
}

/* Function: knight rider , LED chaser  mode no 2 */
void KnightRiderMode2(uint8_t num_loop) 
{
    uint8_t counter = 0;
    char Led_Pattern[7] = {0x81, 0x42, 0x24, 0x18, 0x24, 0x42, 0x81};
    /* 10000001 01000010 00100100 00011000 */       
     for (uint8_t i = 0; i < num_loop; i++) 
    {
        for (counter = 0; counter < 7; counter ++) 
            {
            data_submit(Led_Pattern[counter]);
            __delay_ms(CHANGE_DELAY);
            }
    }
}
     
/* Function for flash mode */
void Flash(uint8_t num_loop)
{
    uint8_t data = 0x0F;
    
    for (uint8_t i = 0; i < num_loop; i++) 
    {
        data = 0x0F;
        data_submit(data);
        __delay_ms(CHANGE_DELAY);
        data = 0xF0;
        data_submit(data);
        __delay_ms(CHANGE_DELAY);
    }
}

/* Function for 8 bit binary count up mode*/
void CountUp(void) 
{
    uint8_t data = 0x00;
    while (1) 
    {
        data_submit(data);
        __delay_ms(CHANGE_DELAY);
        data++;
        if (data == 0xFF) return;
    }
}

/* Function for 8 bit binary count down mode*/
void CountDown(void) 
{
    uint8_t data = 0xFF;
    while (1) 
    {
        data_submit(data);
        __delay_ms(CHANGE_DELAY);
        data--;
        if (data == 0x00) return;
    }
}

/* This function clock will enable the storage Clock.*/
void sclock(void) 
{
    SCLK_595 = 1;
    __delay_us(SHIFT_COUNT_DELAY);
    SCLK_595 = 0;
    __delay_us(SHIFT_COUNT_DELAY);
}

/* If Button is pressed at startup turn all LEDs on*/
void checkbutton(void) 
{
    if (GPIO3 == 0) //Is Switch is pressed
    {
        __delay_ms(DEBOUNCE_DELAY); //Provides required delay
        if (GPIO3 == 0) //Is Switch is still pressed
        {
            data_submit(0xFF);
            while (1) {
                __nop();
            }
        }
    }
}

/* This function will latch and enable the output trigger.  */
void rclock(void) 
{
    RCLK_595 = 1;
    __delay_us(SHIFT_COUNT_DELAY);
    RCLK_595 = 0;
}

/* This function will send the data to shift register */
void data_submit(uint8_t data) 
{
    for (uint8_t i = 0; i < 8; i++) {
        SER_595 = (data >> i) & 0x01;
        sclock();
    }
    rclock(); // Data finally submitted 
}
// EOF