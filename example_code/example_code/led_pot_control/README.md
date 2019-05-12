
Overview
--------------------------------------------
* Name: LED array controlled by a pot 
* Description: A program to control an LED array via the input of pot
With a Pic12F675.
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in led_control.c.

The Pot is read via  an analog input on  GPIO4, based
on value the LED array is lit up.

1. MIN range value = no LEDS on
2. Next range = 1 LED on
3. MID range value = 2 LEDS on
4. Next range = 3 LEDS on
5. MAX range value = ALL LEDS on


GPIO function

1. LED1  GP0
2. LED2  GP1
3. LED3  GP2
4. n/c   GP3
4. POT1  GP4
5. LED4  GP5


The PIC's GP3 pin is solely an digital input port so cannot be used as analog input 
or digital output.

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/ledcontrol.png)

