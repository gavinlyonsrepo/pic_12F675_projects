;  START
	list      p=12f675            ; list directive to define processor
	#include <p12f675.inc>        ; processor specific variable definitions

; Set Config Word address  
    __CONFIG _INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _CPD_OFF

;----------------------------------------------------------------------
; RAM VARIABLES DEFINITIONS
;----------------------------------------------------------------------
CBLOCK	0x020
; -------------------
; delays 
	delayCnt:  1	;  delay 100uS
	delayCnt1: 1	;  delay 10mS
	delayCnt2: 1	;  delay 1S
; -------------------
ENDC
;-- PROGRAM
    org 0  ; origin zero memory location
setup
    bsf  STATUS,5 ;rpo bit  bank 1
    clrf ANSEL				; All Analog selections pins are assigned as digital I/O	
    bcf  TRISIO,0 ; set bit 0 output
    bcf  STATUS,5 ;rpo bit bank 0
    movlw	b'00000111'		; 2)Comparator configuration
    movwf	CMCON			; Set GP<2:0> digital IO (comparator Off)
    
loop       
	bcf GPIO,0              ; bit clear Set register 5 bit 0 
	call Delay_1S
	bsf GPIO,0              ; bit set Set register 5 bit 0 
	call Delay_1S
	goto loop
	
; SUB ROUNTINES
	
; Delay 1S
;-----------------------------------------------------------------------------
Delay_1S:					
	movlw	d'100'				
	movwf	delayCnt2			
Delay_1S_1:
	call	Delay_10mS			
	decfsz	delayCnt2,f			 
	goto	Delay_1S_1			
	return

;-----------------------------------------------------------------------------
; Delay 100 mS
;-----------------------------------------------------------------------------
Delay_100mS:					
	movlw	d'10'				
	movwf	delayCnt2			
Delay_100mS_1:
	call	Delay_10mS			
	decfsz	delayCnt2,f			
	goto	Delay_100mS_1			
	return

;-----------------------------------------------------------------------------
; Delay 10 mS
;-----------------------------------------------------------------------------
Delay_10mS:						
	movlw	d'100'				
	movwf	delayCnt1			
Delay_10mS_1:
	call	Delay_100uS			
	decfsz	delayCnt1,f		
	goto	Delay_10mS_1		
	return
;-----------------------------------------------------------------------------
; Delay 100 uS 
;-----------------------------------------------------------------------------
Delay_100uS:					; Call = 2 cycles
	movlw	d'31'				; 1 cycle
	movwf	delayCnt			; 1 cycle
	decfsz	delayCnt,f			; 
	goto	$-1					; 1+2 cycles
    return						; 2 cycles 
	
	END
	
