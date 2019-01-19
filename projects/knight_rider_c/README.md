
Overview
--------------------------------------------
* Name: knight_rider LED pattern. 
* Description: A program to display a LED pattern in a knight rider fashion
With a Pic12F675 and five LEDs. Two alternative programs 5-bit counter and random pattern 
are also available.
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in knight_rider_c.

GPIO function

1. LED1  GP0
2. LED2  GP1
3. LED3  GP2
4. LED4  GP4
5. LED5  GP5


The PIC's GP3 pin is solely an input port so cannot be used.

There is second file called LED_random.c.
This is a variant of original file in which the LED's
are illuminated in a random pattern. 

There is a third file called 5-bit counter. 
This is a variant of original file in which the LED's
from a 5-bit repeating counter.

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/knightrider.png)

