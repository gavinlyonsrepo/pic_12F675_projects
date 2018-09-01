
Overview
--------------------------------------------
* Name: 74HC595_C
* Description: 8-bit binary counter LED array with  74HC595 Serial Shift Register with PIC 12F675
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in 74HC595_C.

8 LEDS are attached to pins QA-QH of 74HC595. Data in the form of 
an 8-bit binary counter from 0 to 256 is outputted to shift register
and display on array and then looped. thus implementing an 8-bit 
binary counter with just 3 outputs of PIC. 


GPIO function on PIC 3 lines to 74HC595

1. SER Serial / Data in pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2



![schematic ](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/shift.png)

