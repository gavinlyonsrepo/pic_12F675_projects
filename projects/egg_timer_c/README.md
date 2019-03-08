
Overview
--------------------------------------------
* Name: egg timer
* Description: 10 minute egg timer, time displayed by a single seven segment LED module driven by 
a 74HC595 shift register. Time selected by pot and starts clock with push button. written in C code.  
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in file egg_timer_c.c.

10 minute egg timer, time displayed by a single seven segment LED module driven by 
a 74HC595 shift register. Time selected by pot and starts clock with push button. written in C code.  

GPIO function

GPIO function on PIC 3 lines to 74HC595

1. SER Serial / Data in pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2
4. push button GP3 
5. pot GP4(AN4)
6. buzzer GP5

Connections from seven segment single module to shift register pins.

1. A = pin 7 QH
2. B = pin 6 QG
3. C = pin 5 QF
4. D = pin 4 QE
5. E = pin 3 QD 
6. F = pin 2 QC
7. G = pin 1 QB
8. Dot n/c

For more info on pinlayout of seven segment display,  see here.
https://en.wikipedia.org/wiki/Seven-segment_display

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/eggtimer.png)

 

