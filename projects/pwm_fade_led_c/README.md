
Overview
--------------------------------------------
* Name: Fade in and out an LED in c using PWM.
* Description: A program to change brightness of an LED attached to GP4 using the PICs 
8-bit timer interrupt. 
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in c can be found in file led_pwm_c.

The program fades in and out a LED attached to GP4 by loading timer0 with a 8-bit PWM value.

Whenever timer0 expires and an interrupt is generated, then interrupt ISR() function is executed. In this function, depending upon the state of the PWM_PIN (i-e if it is high or low), timer0 register is loaded with appropriate value. There is a global variable with the name of PWM defined in the code. This variable can have a value from 0 (0% duty cycle) to 255 (100% duty cycle).  PWM variable is changed in the main function to automatically change the duty cycle of the PWM wave. 

In the timer init  function, OPTION_REG is initialized to make timer0 prescalar to be 1:32. Timer0 is an 8bit timer, so it expires after reaching a value of 255. When timer0 prescalar is made 1:32 then 	   

PIC TIMER0 Calculator
 
* Clock Source in Mhz                   4 Mhz
* Fosc                                  4000000.0 Hz
* Fosc / 4                              1000000.0 Hz
* Time Period                           1e-06 sec
* Prescaler                             32
* Timer0 Interrupt Period               0.008192 sec
* Period of Frequency Input To Timer0   3.2e-05 sec
* Period of Time for each Timer0 Count  0.008192 sec

(1000000/256)*32 = 8.192 millisecond.

Whenever timer0 expires, then an interrupt is generated which executes the ISR function. In this function, GP4 pin is toggled every time and timer0 interrupt flag is cleared.




