
Overview
--------------------------------------------
* Name: 74HC595_C
* Description: LED display with LED array with 74HC595 Serial Shift 
  Register with PIC 12F675, 8 LEDs 5 modes.
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)

Features
----------------------

In this folder the source code (written in C) can be found.
The main file is led_display.c. T

8 LEDS are attached to pins QA-QH of 74HC595. Data in the form of 
an 8-bit binary counter from 0 to 256 is outputted to shift register
and display on array and then looped. thus implementing an 8-bit 
binary counter with just 3 outputs of PIC. 

Once finished counter it then counts down.
Next it displays 4 different LED chaser and flashing patterns to the display
and then loops again. 

| Function Name | Function |
| CountUp | 8 bit binary counter 0x00 to 0xFF | 
| CountDown | 8 bit binary counter 0xFF to 0x00 | 
| KnightRider | LED chaser mode left to right and back again | 
|  KnightRiderMode2 | LED chaser mode starts at both ends meets in middle | 
|  KnightRiderMode3 | LED chaser mode ,upper and lower nibble track each other  | 
|  Flash | LED flash mode, upper and lower nibble flash alternate | 

A push button is attached to GPIO 3 pin   which is held 
high by a pull up resistor , when button is pressed it goes logic low.
This button is checked by firmware on startup, if pressed it switches all LEDS
on constantly, so unit can be used as a mini-lamp.

GPIO function on PIC 3 lines to 74HC595

1. SER Serial / Data in pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2

![schematic ](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/shift.png)
