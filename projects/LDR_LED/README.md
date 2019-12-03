
Overview
--------------------------------------------
* Name: LDR_LED
* Description: LED display with LED array with 74HC595 Serial Shift 
  Register with PIC 12F675, 8 LEDs 5 modes. Input from a LDR(light dependent resistor) and push button
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)

Features
----------------------

In this folder the source code (written in C) can be found.
The file is main.c. This project is a variant of the 8 LED display with added LDR for day/night control.

8 LEDS are attached to pins QA-QH of 74HC595. Data in the form of 
an 8-bit binary counter from 0 to 256 is outputted to shift register
and displayed on LED array and then looped. thus implementing an 8-bit 
binary counter with just 3 outputs of PIC. 

Once finished the count, it then counts down.
Next it displays 4 different LED chaser and flashing patterns to the display
and then loops again. 

| Function Name | Function |
| --- | ---|
| CountUp | 8 bit binary counter 0x00 to 0xFF | 
| CountDown | 8 bit binary counter 0xFF to 0x00 | 
| KnightRider | LED chaser mode left to right and back again | 
|  KnightRiderMode2 | LED chaser mode starts at both ends meets in middle | 
|  KnightRiderMode3 | LED chaser mode ,upper and lower nibble track each other  | 
|  Flash | LED flash mode, upper and lower nibble flash alternate | 

A push button is attached to GP3 pin  which is held 
high by a pull up resistor , when button is pressed it goes logic low.
This button is checked by firmware on startup, if pressed it switches all LEDS
on constantly, so unit can be used as a mini-lamp.

In addition a LDR(light dependent resistor) circuit is attached to GP4 forming a voltage divider. It is read by ADC module. If Light is detected the unit goes to sleep mode, If it is dark it initiates the LED display cycle and then checks LDR again  when finished. The threshold is at 500 or ~ 2.5 V for 5 volt vcc.
The LDR was calibrated at: Night time was measured at 4V (LDR 88kohms) , Day light was 1.2V (LDR 6.7kohms).

When the unit goes to sleep it is woken by the watchdog timer which is set to a prescaler of 128.
The timer of 18mS * 128 gives a total sleep time of ~ 2.3 seconds. It wakes up checks LDR goes back to sleep
which just takes a few mS. So the PIC is mostly asleep during the day ... mostly.

GPIO function on PIC 3 lines to 74HC595

1. SER  / Serial Data  pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2

![schematic ](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/LDR_LED.png)
