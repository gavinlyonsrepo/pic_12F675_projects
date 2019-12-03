
/*
 * File: main.c
 * Name: LDR_LED
 * Function: PIC12F675 LDR controlled 8 LED project
 * Author: Gavin Lyons
 * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 2 December 2019
 * IDE: MPLAB X v 5.15
 * Compiler: xc8 v2.05
 */

/* ============= LIBS ================*/
#include <xc.h>
#include <stdint.h> /* For uint8_t definitions etc */

/*== DEFINES AND PRAGMAS === */
#define _XTAL_FREQ 4000000 

// CONFIG  PIC12F675 Configuration Bit Settings 
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = ON     // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //serial data in pin 14 
#define RCLK_595 GP1  // storage register clock input pin 12 "latch" 
#define SCLK_595 GP2 //shift register clock input pin 11 "storage"
#define BUTTON1 GP3

#define DEBOUNCE_DELAY 50 //mS
#define CHANGE_DELAY_COUNT 250 //mS
#define CHANGE_DELAY 500  //mS
#define SHIFT_COUNT_DELAY 500 //uS
#define NUMBER_LOOP 5


/* ==== FUNCTION PROTOTYPES ===== */
void setup(void);
void checkbutton(void);

unsigned int GetADCValue(void);
void CheckADC(void);


void sclock(void);
void rclock(void);
void data_submit(uint8_t data);

void LightsOFF(void);
void CountUp(void);
void CountDown(void);
void KnightRider(uint8_t num_loop);
void KnightRiderMode2(uint8_t num_loop);
void KnightRiderMode3(uint8_t num_loop);
void Flash(uint8_t num_loop);


/* ====== MAIN LOOP ======= */
void main(void) {
	setup();
    checkbutton();
	while(1)
    {
        LightsOFF();
        CheckADC();
	}
	return;
}
/* ======== END of MAIN =========  */

/* ====== FUNCTIONS  ======= */
/* Function Name: InitADC */
void setup(void)
{
	ANSEL   = 0x18;	     // Clear Pin selection bits
	TRISIO  = 0x18;      // GP4(ADC) GP3(button) input, rest all output
	GPIO  = 0x00;
	ADCON0 = 0x81;		 // Turn on the A/D Converter ADFM and ADON
	CMCON  = 0x07;		 // Shut off the Comparator, so that pins are available for ADC
	VRCON  = 0x00;	     // Shut off the Voltage Reference for Comparator
    
}

/* Function Name: GetADCValue */
unsigned int GetADCValue(void)
{

	ADCON0 |= 0x0c;      // Select GP4 pin as ADC input CHS1:CHS0: to 11
	
	__delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE);     //wait for conversion completion

	return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
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

/* Function for 8 bit binary count up mode 0 -255*/
void CountUp(void) 
{
    uint8_t data = 0x00;
    while (1) 
    {
        data_submit(data);
        __delay_ms(CHANGE_DELAY_COUNT);
        data++;
        if (data == 0xFF) return;
    }
    __delay_ms(CHANGE_DELAY_COUNT);
}

/* Function for 8 bit binary count down mode 255 to 0*/
void CountDown(void) 
{
    uint8_t data = 0xFF;
    while (1) 
    {
        data_submit(data);
        __delay_ms(CHANGE_DELAY_COUNT);
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
    OPTION_REG = 0b00001111;  // Watchdog timer clear
    CLRWDT(); 
}

void LightsOFF(void)
{
    data_submit(0x00);
    __delay_ms(CHANGE_DELAY);
}

// Function to check LDR via ADC and act id dya or night
void CheckADC(void)
{
    unsigned int ADC_value = 0;    
    ADC_value = GetADCValue();
    
    if (ADC_value >= 500) //nighttime run LED routine
    {   
        CountUp();
        CountDown();
        KnightRider(NUMBER_LOOP);
        KnightRiderMode2(NUMBER_LOOP);
        KnightRiderMode3(NUMBER_LOOP);
        Flash(NUMBER_LOOP);   
    }else // Daytime
    {
        OPTION_REG = 0b00001111;   // Assign 1:128 prescaler to WDT 18ms 2.3s
        NOP(); 
        SLEEP();
        CLRWDT(); 
    }
    __delay_ms(10);
}

/* If Button is pressed at startup turn all LEDs on*/
void checkbutton(void) 
{
    if (BUTTON1 == 0) //Is Switch is pressed
    {
        __delay_ms(DEBOUNCE_DELAY); //Provides required delay
        if (BUTTON1 == 0) //Is Switch is still pressed
        {
            data_submit(0xFF);
            while (1) {
                NOP();
                OPTION_REG = 0b00001111;  
                CLRWDT();
            }
        }
    }
}
/* =========== EOF ============*/