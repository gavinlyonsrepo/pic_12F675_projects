
/* ====== Header =======
 * File:   dht11_12.c
 * Author: Gavin Lyons
 * IDE: MPLAB X v4.2 
 * Compiler: xc8 v1.45
 * Description: see URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_12F675_projects
 * Created on 08 September 2018, 17:58
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
// Interfacing 74HC595 Serial Shift Register
#define SER_595 GP0 //serial data in pin 14 
#define RCLK_595 GP1  // storage register clock input pin 12 "latch" or Rclk
#define SCLK_595 GP2 //shift register clock input pin 11 "storage" or sclk
//  Interfacing DHT11 sensor signal in. 
#define DHT11_pin GP4

//seven segment symbols
#define sym_b 0x7C     // b fgedc 1111100 
#define sym_t 0x78     // t fged 1111000 
#define sym_H  0x76    // H fegbc 1110110
#define sym_E  0x79     // E bc(off) 1111001 
#define sym_C  0x39     // C 
#define sym_DASH  0x40    // -

/* ======= Globals========*/
char data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67}; //Character array nums 1-10
unsigned short  Check, Temp, RH, Sum ;

/* ==== Function prototypes ===== */
void setup(void);
void sclock(void);
void rclock(void);
void DataDisplay(unsigned int data);
void DataScroll();
void DataRead();

char ReadData();
void StartSignal();
void CheckResponse();
 
/* ====== Main loop ======= */
void main(void) {
    
    setup();
    DataDisplay(sym_b);  // Display b to LED seven segment (begin )
   __delay_ms(2000); // wait two seconds for sensor to stabilize from power up
   
    while(1){

        DataDisplay(sym_b);  // Display b to LED seven segment (i.e. begin loop )
         __delay_ms(1000); 
        DataDisplay(sym_DASH); //display a DASH error code (unseen if no error) while talking to sensor 
        StartSignal(); //send start signal to DHT11 sensor
        CheckResponse(); //get response from DHT11 sensor
        
        if(Check == 1)  // Did DHT11 respond ? 
           {
            DataRead();
            if(Sum == (RH + Temp)) // is the Checksum OK?
                 {
                   DataScroll();    
                 }else //bad checksum error code display
                {
                      DataDisplay(sym_C); //NO response from DHT C
                }
           }else // no response error code display
           {
               DataDisplay(sym_E); //NO response from DHT E
           }
           __delay_ms(2000);
    }
   
    return;
    }
/* ======== END of MAIN =========  */


/* ====== Functions space ======= */

/* DataScroll function to scroll the data to Seven segment*/
void DataScroll()
{ 
                    //temp
                    DataDisplay(sym_t);  //display t from temp
                    __delay_ms(1000); 
                     DataDisplay(data[(Temp / 10) % 10]); //first digit
                     __delay_ms(1000); 
                     DataDisplay(data[Temp % 10]);  //second digit
                     __delay_ms(1000); 
                   
                     //humidity
                     DataDisplay(sym_H);  // display H for humidity
                     __delay_ms(1000); 
                     DataDisplay(data[(RH / 10) % 10]); //first digit
                      __delay_ms(1000); 
                     DataDisplay(data[RH % 10]); //second digit
}

/* dataRead function: read  the sensor data */
void DataRead()
{
            // Read in the four bytes
            RH = ReadData(); // intergal Humidity byte into RH
            ReadData();   // discard decimal byte
            Temp = ReadData(); //intergal temperature byte into temp
            ReadData();  // discard decimal byte
            Sum = ReadData(); // checksum byte into sum 
}

/* StartSignal Function: 
  sends request 18uS low pulse for data to the sensor*/
void StartSignal(){
 TRISIO4 = 0;    //Set TRISIO4 as output
 DHT11_pin = 0;    //GP4 sends 0 to DHT11 (request)
 __delay_ms(18);
 DHT11_pin = 1;    //GP4 sends 1 DHT 
 __delay_us(30);
 TRISIO4 = 1;  //Set TRISIO4 as input
  }

/* Check Response function: 
  Check if DHT responded to Start signal 
  40uS low pulse 80uS high pulse*/
 void CheckResponse(){
 Check = 0;
 __delay_us(40);
 if (DHT11_pin == 0){
 __delay_us(80);
 if (DHT11_pin == 1)   Check = 1;   __delay_us(40);}
 }
 
 /* ReadData function:
  Read in one byte of data from DHT11 sensor returns byte as char.
  */
 char ReadData(){
 char i, j;
 for(j = 0; j < 8; j++){
    while(!DHT11_pin); //Wait until GP4 goes HIGH (50uS)
    __delay_us(30);
    if(DHT11_pin == 0)
          i&= ~(1 << (7 - j));  //Its a zero Clear bit 
    else {i|= (1 << (7 - j));  //Its a 1 Set bit 
    while(DHT11_pin);}  //Wait until GP4 goes LOW
 }
 
 return i;
 }
 
/* Setup function:
 * Setups the SPECIAL FUNCTION REGISTERS  registers of PIC
 */
void setup (void)
{
    ADCON0 = 0x00;        // Turn off the A/D Converter ADFM and ADON
    ANSEL = 0x00;      
    CMCON = 0x07;		 // Shut off the Comparator
    VRCON = 0x00;        // Shut off the Voltage Reference
    TRISIO = 0xF8;       // GP4 and GP3 input, rest all output 011000
    GPIO=0x00;           // set all pins low
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

/* DataDisplay:
 * This function will send the data to serial line 74HC9595
 */
void DataDisplay(unsigned int data){
    for (int i=0 ; i<8 ; i++){
        SER_595 = (data >> i) & 0x01; // bit shift and bit mask data. 
        sclock(); //enable data storage clock
    }
    rclock(); // Data latch
}
/* =========== EOF ============*/