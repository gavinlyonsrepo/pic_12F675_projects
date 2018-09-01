;
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
	
 
;----------------------------------------------------------------------
; RAM VARIABLES DEFINITIONS
;----------------------------------------------------------------------
    cblock 0x20
      COUNT1
      COUNT2
      COUNT3
      BITS
      BITS_COPY
    endc
    
 ;program  origin zero memory location
   org 0
 
;symbolic name section define pins connect to pic from 74HC595
HC595_DS EQU 0  ; serial data in pin 14 
HC595_ST_CP EQU 1 ; storage register clock input pin 12 "latch"  
HC595_SH_CP EQU 2 ;shift register clock input pin 11 "storage"

; Bank 0
    bcf STATUS, RP0
    clrf GPIO ; clear GPIO , low

; Turns the comparator off, 
    movlw b'111'
    movwf CMCON

; bank 1
    bsf STATUS, RP0
    clrf ANSEL	; All Analog selections pins are assigned as digital I/O
    clrf TRISIO   ; this turns all pins which can act as digital outputs,
; Bank 0 .
    bcf STATUS, RP0

    
loop
    call Delay_1S

; The HC595 shifts in from DS on SH_CP low-high transitions.
SHIFT_CLOCK macro
    bcf GPIO, HC595_SH_CP
    bsf GPIO, HC595_SH_CP
    endm

; Increment BITS and copy it.
    incf BITS, F
    movf BITS, W
    movwf BITS_COPY

; Clock the least significant bit of BITS_COPY into the shift register, and
; rotate bits,.
SHIFT_LSB_AND_CLOCK macro
    bcf GPIO, HC595_DS
    btfsc BITS_COPY, 0 ;skip if zero 
    bsf GPIO, HC595_DS ;set serial high
    SHIFT_CLOCK      ;set the clock
    rrf BITS_COPY, F 
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
    bcf GPIO, HC595_ST_CP
    bsf GPIO, HC595_ST_CP

; Repeat this forever.
    goto loop

;--------------------
; SUB ROUNTINES
;-------------------------------
; Generated cycle-accurate delay code using
; http://www.golovchenko.org/cgi-bin/delay . Since the code was generated using
; the assumption that the clock is exactly 4MHZ, this won't create a delay of
; exactly one second, since the internal oscillator is not tuned that well.
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