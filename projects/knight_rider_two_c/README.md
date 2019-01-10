
Overview
--------------------------------------------
* Name: Knight_rider_two
* Description: 8 LED chaser circuit with a 74HC595 Serial Shift Register and PIC 12F675
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in  knight_rider_two_C.

8 LEDS are attached to pins QA-QH of 74HC595. Data in the form of 
a "knight rider" pattern array is outputted to shift register
and displayed on LED array and then looped, thus implementing a 8 LED chaser circuit
with just 3 outputs of PIC. 

A push button is attached to GPIO 3 pin   which is held 
high by a pull up resistor , when button is pressed  it goes logic low.
This button is checked by sw on startup if activated it switches are LEDS
on constantly so unit can be used as a lamp.



GPIO function on PIC 3 lines to 74HC595

1. SER Serial / Data in pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2



![schematic ](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/shift.png)

