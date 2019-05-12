
Overview
--------------------------------------------
* Name: Battery tester
* Description: Battery level of AA/AAA cell under load displayed on a single seven segment LED module driven by 
a 74HC595 shift register.   
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code  can be found in file battest.c.
Written in C code(xc8).

The ADC value at GPIO4 is displayed as a
voltage on the 7-seg digit in a scrolling display, 

b for begin, E for end and middle dash for decimal point.
Bottom dash only is an error code: Unit went thru setup function but hanged up before 
measurement displayed. The Battery is under load. 
  
Example calculation:

ADC measurement * (VCC/ADC resolution) = result.

1. 300 measured on ADC
2. 300 * (5/1024)  = 1.464 volts 
3. b1-46E on display = 1.46 volts 


GPIO function

GPIO function on PIC 3 lines to 74HC595

1. SER Serial / Data in pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2
4. Battery under test = GP4(AN4)

Connections from seven segment single module to shift register pins.

1. A = pin 7 QH
2. B = pin 6 QG
3. C = pin 5 QF
4. D = pin 4 QE
5. E = pin 3 QD 
6. F = pin 2 QC
7. G = pin 1 QB

For more info on pinlayout of seven segment display,  see here.
https://en.wikipedia.org/wiki/Seven-segment_display

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/sevenseg.jpg)

Schematic
--------------------

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/battest.png)