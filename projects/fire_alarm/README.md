
Overview
--------------------------------------------
* Name: PIC12F675 fire sensor alarm.
* Description: PIC12F675 fire sensor alarm. 
Input from Ky-026 fire sensor module
Output to Relay and Status LED. Written in C code.  
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in C can be found in file fire_alarm.c.
The firmware is written in C and compiled with xc8 v2.00 for PIC on the 
IDE MPLAB X 5.05.

Flame in the target area will trigger the flame sensor module(KY-026), 
and the triggers signal will be sent to the control circuit. The output of the alarm system 
can be connected to external alarms, thru the relay circuit. 
The PIC12F675 works as a interface between the detection device 
and the alarm circuit. 

There is an initial delay of 30 seconds.
A LED is connected to port GP0. The LED blinks every 500mS during this delay time.

After Start delay, the PIC starts monitoring the voltage of Ky026 output.
The LED blinking pattern is now changed to indicate the “standby” mode.
In standby mode, The LED turns on for 80mS every ~= 10 seconds. 
This is achieved by timer0 overflow and an internal counter variable.

The KY-026 Flame Sensor Modules detect infra red emissions.
light detection within the range of 760 – 1100nm.
It based on an LM 393 comparator and a phototransistor. 
With both digital and analog output and sensitivity setting via potentiometer. 
See picture for schematic at bottom of Readme.
This sensor modules has a 4-pin connection( operates at 5 volt)
1. digital Output
2. analog output
3. vcc 
4. Gnd

A PIC12F675 micro-controller continuously monitors the digital output (through GP5)
from the  sensor module. When fire is sensed, It then checks the analog output
If both outputs indicate flame detection it triggers alarm state.

The PIC then turns on the relay (SRD-05VDC-SL-C) by GP1 going high. A "Keyes SRy1" relay module can  be used for the relay circuit. The Relay has a second LED(LED2) in its circuit 
which indicates its on.
This output will remain High, as long as the fire 
exists, and this active condition is indicated by status LED being on. 

**Program flow**

1. start
2. Wait 30 seconds, sensor stabilisation delay
3. Monitor Sensor and Status LED in standby 
4. If Sensor alert = turn on Relay and Status LED 
5. Turn off relay, Status LED and goto 3 when/if Sensor alert ends.

**GPIO function PIC12F675 Pin Assignment**

1. Status LED   GP0
2. RELAY circuit signal input  GP1
3. Sensor digital signal output D0 GP5
4. Sensor analog signal output A0 GP5

**Status LED modes**

1. Start init delay blinks on/off every 500mS 
2. Standby State on for 80mS every 10 seconds
3. Solid on = Alarm state

![schematic](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/fire_alarm.png)



![1sensor](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/ky026.jpg)

