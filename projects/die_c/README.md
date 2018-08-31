
Overview
--------------------------------------------
* Name| electronic die
* Description| A simulation of a die using pic 12F675 and seven LEDS  
* Author| Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in file dice.c

7 Leds are attached to PIC in the pattern of a die. Based on user input to a push button.
Numbers 1-6 are displayed on LED matrix.

GPIO function

/* pins layout labels*/
1. LED_A  GP0
2. LED_B  GP1
3. LED_C  GP2
4. LED_D  GP4
5. push_button GP5

| Numbers | label | GPIO o/p  pattern|
| ---- | ---- | ---- |
|1 LED_A | 0x01 b00000001 |
|2 LED_B | 0x02 b00000010 |
|3 LED_A + LED_B | 0x03 b00000011 |
|4 LED_B + LED_C | 0x06  b00000110 |
|5 LED_A + LED_B + LED_C   | 0x07 b00000111 |
|6 Six|LED_A + LED_B + LED_C + LED_D |  0x17 b00010111 |
 

![PIC layout](https|//github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/dice.jpg)


![PIC schematic](https|//github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/dice2.png)
