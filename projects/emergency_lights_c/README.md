
Overview
--------------------------------------------
* Name: Emergency vehicle lights simulation
* Description: A simulation of the lighting system mounted on Emergency vehicle lights 
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in file emergency_lights_c.c.
4 Leds are attached two red and blue to PIC. The PIC cycles thru various lighting 
patterns based on input from a push button which is read by means of hardware interupt
on GP2. 

GPIO function

* red LED1  GP0.
* red LED2  GP1.
* push_button  GP2. (pulled high by 10K to Vdd)
* blue LED1  GP4.
* blue LED2  GP5.

![PIC](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/emergencylights.png)



