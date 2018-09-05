; *  =========== HEADER ===========
; * File:   shift_asm.asm
; * Function: PIC12F675 8-bit binary counter, LED Array and  shift register
; * Author: Gavin Lyons
; * URl: https://github.com/gavinlyonsrepo/pic_12F675_projects
; * Created on 010918 , 15:34
; * IDE: MPLAB X v4.2 
; * Compiler: MPASMWIN v5.77
;

;  START
	list      p=12f675            ; list directive to define processor
	#include <p12f675.inc>        ; processor specific variable definitions
; Set Config Word address  
 __CONFIG _INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _CPD_OFF
	
 

; ========== RAM VARIABLES DEFINITIONS =================

    cblock 0x20
      COUNT1
      COUNT2
      COUNT3
      DATA
      DATA_COPY
    endc
    
 ;program origin zero memory location
   org 0
 
; symbolic name section define pins connect to pic from 74HC595
SERIN_595 EQU 0  ; serial data in pin 14 
LATCH_595 EQU 1 ; storage register clock input pin 12 "latch/RCLK""
STORE_595 EQU 2 ;shift register clock input pin 11 "storage/SCLK"

; ======== SETUP ==============
    bcf STATUS, RP0 ; Bank 0
    clrf GPIO ; clear GPIO , low
    movlw b'111'
    movwf CMCON ; Turns the comparator off,
    bsf STATUS, RP0 ; bank 1
    clrf ANSEL	  ; All Analog pins are assigned as digital I/O
    clrf TRISIO   ;  digital outputs,
    bcf STATUS, RP0; Bank 0 .

; ========== MAIN LOOP ===================
loop
    call Delay_1S

; The HC595 shifts in from Serial in  on STORE_595 low-high transitions.
SHIFT_CLOCK macro
    bcf GPIO, STORE_595
    bsf GPIO, STORE_595
    endm

; Increment DATA and copy it.
    incf DATA, F
    movf DATA, W
    movwf DATA_COPY

; Clock the least significant bit of DATA_COPY into the shift register, and
; rotate bits
SHIFT_LSB_AND_CLOCK macro
    bcf GPIO, SERIN_595
    btfsc DATA_COPY, 0 ;skip if zero 
    bsf GPIO, SERIN_595 ;set serial high
    SHIFT_CLOCK      ;set the clock
    rrf DATA_COPY, F 
    endm
    
    ; bit 0 to 8 
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK
    SHIFT_LSB_AND_CLOCK

; Tick on the storage register clock(RCLK or latch) to copy the shift register in.
    bcf GPIO, LATCH_595
    bsf GPIO, LATCH_595

; Repeat this forever.
    goto loop

; ========= SUB ROUNTINES=========
; Generated cycle-accurate delay code using
; http://www.golovchenko.org/cgi-bin/delay . 
Delay_1S:
            ;999997 cycles
    movlw   0x08
    movwf   COUNT1
    movlw   0x2F
    movwf   COUNT2
    movlw   0x03
    movwf   COUNT3
Delay_0
    decfsz  COUNT1, f
    goto    $+2
    decfsz  COUNT2, f
    goto    $+2
    decfsz  COUNT3, f
    goto    Delay_0

            ;3 cycles
    goto    $+1
    nop
    movlw 63
    movwf COUNT1
    return
    
    end
