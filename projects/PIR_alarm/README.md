
Overview
--------------------------------------------
* Name: PIC12F675 PIR security Alarm.
* Description: PIC12F675 Passive infra-red (PIR) motion detector security Alarm. 
Input from HC-SR501 PIR sensor.
Output to Relay and Status LED. Written in C code.  
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in C can be found in file PIR_alarm.c.
The firmware is written in C and compiled with xc8 v2.00 for PIC on the 
IDE MPLAB X 5.05.

Human body heat moving across the target area will trigger the PIR sensor(HC-SR501), 
and the trigger signal will be sent to the control circuit. The output of the alarm system 
can be connected to external lamps or alarms, thru the relay circuit. 
The PIC12F675 works as a interface between the detection device 
and the alarm circuit. 

The initial delay of one minute is introduced deliberately to avoid false triggerings, 
because the PIR sensor requires an initial stabilisation time of about 10 to 60 
seconds. Also gives time for user to leave target area. 
A LED is connected to port GP0. The LED blinks every 500mS during this delay time.

After Start delay, the PIC starts monitoring the voltage of PIR output.
The LED blinking pattern is now changed to indicate the “standby” mode.
In standby mode, The LED turns on for 80mS every ~= 5 seconds. 
This is achieved by timer0 overflow and an internal counter variable.

For the PIR sensor a HC-SR501 module is used. See picture at bottom of Readme.
This PIR sensor modules has a 3-pin connection. (Vcc, Output, and ground). 
A PIC12F675 micro-controller continuously monitors the output (through GP5)
from the PIR sensor module. When the motion is sensed, the PIR output voltage is used 
to drive the base of a 2N2222 NPN transistor.

The PIC then turns on the relay (SRD-05VDC-SL-C) by GP1 going high. A "Keyes SRy1" relay module can  be used for the relay circuit. The Relay has a second LED(LED2) in its circuit 
which indicates its on.
This output will remain High, as long as the motion 
exists, and this active condition is indicated by status LED being on. 

**Program flow**

1. start
2. Wait one minute, sensor stabilisation delay
3. Monitor PIR and Status LED in standby 
4. IF PIR alert = turn on Relay and Status LED 
5. Turn off relay, Status LED and GOTO 3 when PIR alert ends.

**GPIO function PIC12F675 Pin Assignment**

1. Status LED   GP0
2. RELAY circuit signal output GP1
3. PIR signal input GP5


**Status LED modes**

1. Start init delay blinks on/off every 500mS 
2. Standby State on for 80mS every 5 seconds
3. Solid on = Alarm state

![schematic](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/PIR_alarm.png)



![1sensor](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/hcsr501pir.jpg)

