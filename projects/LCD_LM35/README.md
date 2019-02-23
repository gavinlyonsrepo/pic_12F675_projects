
Overview
--------------------------------------------
* Name: LCD_LM35
* Description: A program to read an LM35 temperature sensor and display it on an 
HD44780 16X2 LCD, with a PIC 12F675.
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in C.

**LM35 sensor** 

The LM35 outputs a signal on pin Vout
The LM35 is read via an analog input(GP4) 10mV per degree.
The ADC 10-bit resolution for 5V / 2^10 = 5/1024 = 0.004883.

LM35 calculation:

1. Vout=0.01/°C
2. °C=Vout/0.01
3. °C=Vout*100
4. Vout = ADC_value * (VCC/ADC resolution)
5. °C = (ADC_value * (5/1024)) * 100 
6. °C * 100  =(ADC_value * (5/1024)) * 10000 (turn 0.4883 into 49 to avoid using float)
7. The LHS can then be parsed by code and displayed. 

**74HC595 Shift register**
The LCD is driven using a Shift register 74HC595.
GPIO to the 595.

1. SER Serial / Data in pin 14 GP2
2. SCLK / Storage clock pin 11 GP1
3. RCLK / Latch pin 12 GP0

**HD44780-based character LCD**

HD44780 based character LCD displays use 14 wire connections: 
8 data lines (D0-D7), 3 control lines (RS, E, R/W), 
and three power lines (Vdd, Vss, Vee). Some LCDs come with 
backlight features that help reading display data in low illumination conditions.
They have two additional connections  (LED+ and LED-).

The control pin R/W determines if the data transfer between the LCD module and 
an external microcontroller are actual character data or command/status.
The enable pin (E) initiates the actual data transfer. When writing to the LCD 
display, the data is transferred only on the high to low transition of the E pin.

The Vdd pin (2) should be connected to the positive power supply and Vss (1) to 
ground. Pin 3 (Vee) is for display contrast adjustment, 

Pins 7 to 14 are data lines (D0-D7). Data transfer to and from the display 
can be achieved either in 8-bit or 4-bit mode. 
The 8-bit mode uses all eight data lines to transfer a byte, whereas, in 4-bit mode, 
a byte is transferred as two 4-bit nibbles. In the later case, 
only the upper 4 data lines (D4-D7) are used. 
This technique is beneficial as this saves some input/output pins of microcontroller.
This project uses 4-bit mode.

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/LCD_LM35.png)

