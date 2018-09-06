
Overview
--------------------------------------------
* Name: blink LED in c
* Description: Two programs: 
1. A program to blink an LED attached to GPIO0 every 500mS in C using "delay_ms" function
2. A program to blink an LED attached to GPIO0 every 1S in C using Timer(1)
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------
Two programs: 
1. A program to blink an LED attached to GPIO0 every 500mS in C using "delay_ms" function
2. A program to blink an LED attached to GPIO0 every 1S in C using Timer(1) interupts

In this folder the source code in C for program can be found in file blink_c_4.c
In this folder the source code in C for program 2 can be found in file timer_led.c

Calculation for Timer1

1. 4Mhz/4 = Freq osc/4 = 1Mhz
2. 1/(1 Mhz/prescaler/65536-45541) ~= 20mS Interrupt overflow
3. Note: Timer size = 65536, Timer preload = 45541, prescaler = 1
4. internal variable counter of 50 to get 1 Second (50*20mS)
5. Led is toggled every 50 interrupt overflows.

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/blink.jpg)


