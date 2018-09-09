
Overview
--------------------------------------------
* Name: PIC12F675 Temperature display.
* Description: Displays the temperature and humidity readings from a DHT11 sensor to a 
single seven segment LED module driven by a 74HC595 shift register. Written in C code.  
* Author: Gavin Lyons.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)


Features
----------------------

In this folder the source code in C can be found in file dht11_12.c.

This program displays the temperature and humidity readings from a DHT11 sensor to a 
single seven segment LED module driven by a 74HC595 shift register. Written in C code.    

The information is displayed in a scroll like fashion thru the single digit display.
with a second between each display. 

**Program flow**

1. start
2. display b (Begin)
3. wait two seconds for sensor to stabilize
4. Get data from sensor. 
5. display b (Begin)
6. Display t (t for temperature)
7. Display first digit of temperature reading i.e 1 for 19 C
8. Display second digit of temperature reading i.e 9 for 19 C
9. Display H (h for humidity)
10. Display first digit of humidity reading i.e 3 for 38 %
11. Display second digit of humidity reading i.e 8 for 38 %
12. GOTO to 4

**Error codes**

1. E = Comnmunications Error. No response to the PICs request signal from sensor.
2. Dash = Communications Failure. Sensor responded to Start signal but failed 
to communicate data with PIC correctly.
3. C = Checksum Error. Received all data from sensor but it failed checksum. 


Communication Format with DHT11 can be separated into three stages.

1. Request
2. Response
3. Data Reading 5 bytes.
4. Sum the 1st 4 bytes and check if the result is the same as CheckSum(5th byte)


**GPIO function**

GPIO function on PIC, 3 lines to 74HC595

1. SER Serial / Data in pin 14   GP0
2. RCLK / Latch pin 12  GP1
3. SCLK / storage clock pin 11  GP2
4. n/c 
5. DHT11 sensor line. GP4 
6. n/c

**Connections from seven segment single module to shift register pins.**

1. A = pin 7 QH
2. B = pin 6 QG
3. C = pin 5 QF
4. D = pin 4 QE
5. E = pin 3 QD 
6. F = pin 2 QC
7. G = pin 1 QB
8. Dot n/c

For more info on pinlayout of seven segment display,  see here.

https://en.wikipedia.org/wiki/Seven-segment_display

For more info on DHT11 sensor see datasheet here.

https://components101.com/sites/default/files/component_datasheet/DHT11-Temperature-Sensor.pdf

![schematic](https://github.com/gavinlyonsrepo/pic_12F675_projects/blob/master/images/dht11.png)



