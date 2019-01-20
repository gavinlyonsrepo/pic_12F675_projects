
Overview
--------------------------------------------
* Name: LED Display
* Description: A program to display various LED lighting modes on a PIC12F675 and five LEDs. 
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code (written in C) can be found in 4 files.  
Each file has a different function for same circuit and are stand alone.

File Function:

| File Name | Function | 
| --- | --- | 
| led_display.c | All other files combined in one | 
| 5bitcounter.c | 5 bit binary counter | 
| knight_rider_c.c | Led chaser display | 
| LED_random.c | random  LED patterns | 


led_display.c is the primary file and combines other the other 3 files in one.
It carries out the binary count loop fives times, the LED chaser display 10 times,
and then displays 15 random patterns to the LED array, and then loops again.


GPIO function

1. LED1  GP0
2. LED2  GP1
3. LED3  GP2
4. LED4  GP4
5. LED5  GP5


Note: The PIC's GP3 pin is solely an input port so cannot be used.


![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/knightrider.png)

