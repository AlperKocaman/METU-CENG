LIST    P=18F8722

#INCLUDE <p18f8722.inc> 
    
CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

UDATA_ACS
    ctr1 res 1
    ctr2 res 1
    ctr3 res 1
    b_pres res 1
    
ORG     0x00
goto    main

init1
 
movlw h'0F'
movwf ADCON1 

clrf PORTA
clrf PORTB
clrf PORTC
clrf PORTD
clrf PORTE 
clrf LATA 
clrf LATB
clrf LATC 
clrf LATD
clrf LATE
 
clrf b_pres
   
movlw b'11110000'
movwf TRISA       ; to make RA4 input
    
movlw b'11111000'
movwf TRISE       ;to make RE3-RE4 input

movlw b'11110000'
movwf TRISB
movwf TRISC
movwf TRISD 
        
movlw h'0F'
movwf LATA
movwf LATB
movwf LATC
movwf LATD  
    
return
 
init2
 
clrf LATA
clrf LATB
clrf LATC
clrf LATD
 
return
 
state1: 
 
   btfss LATA , 0  
   goto A0
   
   btfss LATA , 1
   goto A1
   
   btfss LATA , 2 
   goto A2
   
   btfss LATA , 3 
   goto A3
   
   btfss LATB , 0
   goto B0
   
   btfss LATB , 1
   goto B1
   
   btfss LATB , 2
   goto B2 
   
   btfss LATB , 3 
   goto B3 
   
   btfss LATC , 0
   goto C0
   
   btfss LATC , 1
   goto C1
   
   btfss LATC , 2
   goto C2
   
   btfss LATC , 3
   goto C3 
   
   btfss LATD , 0 
   goto D0 
   
   btfss LATD , 1
   goto D1
   
   btfss LATD , 2
   goto D2
   
   btfss LATD , 3
   goto D3
   
   call control
   
   goto state1 
   
   A0:
    movlw b'00000001'
    movwf LATA
    call delay
    goto state1
    
   A1:
    movlw b'00000011' 
    movwf LATA
    call delay
    goto state1
    
   A2:
    movlw b'00000111' 
    movwf LATA
    call delay
    goto state1
    
   A3:
    movlw b'00001111'
    movwf LATA
    call delay
    goto state1
    
   B0:
    movlw b'00000001'
    movwf LATB
    call delay
    goto state1
    
   B1:
    movlw b'00000011' 
    movwf LATB
    call delay
    goto state1
    
   B2:
    movlw b'00000111'  
    movwf LATB
    call delay
    goto state1
    
   B3:
    movlw b'00001111'
    movwf LATB
    call delay
    goto state1
    
   C0:
    movlw b'00000001'
    movwf LATC
    call delay
    goto state1
    
   C1:
    movlw b'00000011' 
    movwf LATC
    call delay
    goto state1
    
   C2:
    movlw b'00000111' 
    movwf LATC
    call delay
    goto state1
    
   C3:
    movlw b'00001111'
    movwf LATC
    call delay
    goto state1
    
   D0:
    movlw b'00000001'
    movwf LATD
    call delay
    goto state1
    
   D1:
    movlw b'00000011'
    movwf LATD
    call delay
    goto state1
    
   D2:
    movlw b'00000111' 
    movwf LATD
    call delay
    goto state1
    
   D3:
    movlw b'00001111'
    movwf LATD
    call delay
    goto state1
    
state2:
    
    btfsc PORTE , 3
    goto  state2_3
    
    btfsc PORTE , 4
    goto  state2_4
    
    goto state2
 
return 
    
state2_3:
    
    btfsc PORTE , 3
    goto state2_3
    
    goto state1
    
state2_4:    
    
    btfsc PORTE , 4
    goto state2_4
    
    goto state3

state3:
    
   btfsc LATD , 3 
   goto d3 
   
   btfsc LATD , 2
   goto d2
   
   btfsc LATD , 1
   goto d1
   
   btfsc LATD , 0
   goto d0
   
   btfsc LATC , 3
   goto c3
   
   btfsc LATC , 2
   goto c2
   
   btfsc LATC , 1
   goto c1
   
   btfsc LATC , 0
   goto c0 
     
   btfsc LATB , 3
   goto b3
   
   btfsc LATB , 2
   goto b2
   
   btfsc LATB , 1
   goto b1 
   
   btfsc LATB , 0 
   goto b0 
   
   btfsc LATA , 3  
   goto a3
   
   btfsc LATA , 2
   goto a2
   
   btfsc LATA , 1 
   goto a1
   
   btfsc LATA , 0 
   goto a0
   
   call control
   
   goto state3 
   
   a0:
    movlw b'00000000'
    movwf LATA
    call delay
    goto state3
    
   a1:
    movlw b'00000001' 
    movwf LATA
    call delay
    goto state3
    
   a2:
    movlw b'00000011' 
    movwf LATA
    call delay
    goto state3
    
   a3:
    movlw b'00000111'
    movwf LATA
    call delay
    goto state3
    
   b0:
    movlw b'00000000'
    movwf LATB
    call delay
    goto state3
    
   b1:
    movlw b'00000001' 
    movwf LATB
    call delay
    goto state3
    
   b2:
    movlw b'00000011'  
    movwf LATB
    call delay
    goto state3
    
   b3:
    movlw b'00000111'
    movwf LATB
    call delay
    goto state3
    
   c0:
    movlw b'00000000'
    movwf LATC
    call delay
    goto state3
    
   c1:
    movlw b'00000001' 
    movwf LATC
    call delay
    goto state3
    
   c2:
    movlw b'00000011' 
    movwf LATC
    call delay
    goto state3
    
   c3:
    movlw b'00000111'
    movwf LATC
    call delay
    goto state3
    
   d0:
    movlw b'00000000'
    movwf LATD
    call delay
    goto state3
    
   d1:
    movlw b'00000001'
    movwf LATD
    call delay
    goto state3
    
   d2:
    movlw b'00000011' 
    movwf LATD
    call delay
    goto state3
    
   d3:
    movlw b'00000111'
    movwf LATD
    call delay
    goto state3   
    
delay
    
    movlw d'10'
    movwf ctr3
    
    loop_3
    
	movlw h'b9'
	movwf ctr2 

	loop_2

	    movlw h'9F'
	    movwf ctr1

	    loop_1
		
		call control
		decfsz ctr1 , 1 
		goto loop_1
		decfsz ctr2 , 1
		goto loop_2
		decfsz ctr3 , 1 
		goto loop_3
    
return
		
control:
    
   btfsc PORTA , 4 
   call  b_pres1  
    
   btfss b_pres ,0
   goto no_op
   
   btfsc PORTA , 4
   return
   
   movlw b'00000000'
   movwf b_pres
   goto state2
   
b_pres1:
    
    btfsc b_pres ,0
    return
    movlw b'00000001'
    movwf b_pres
    return
    
no_op:
    NOP
    NOP
    NOP
    NOP
    return
    
delay_without_control:
    
    movlw h'41'
    movwf ctr3
    
    loop_c
    
	movlw h'A0'
	movwf ctr2
    
	loop_b
    
	    movlw h'9F'
	    movwf ctr1
    
	    loop_a
    
		decfsz ctr1 , 1
		goto loop_a
		decfsz ctr2 , 1
		goto loop_b
		decfsz ctr3 , 1
		goto loop_c
    
return

main:
    
call init1
    
call delay_without_control
call delay_without_control
call delay_without_control
call delay_without_control
    
call init2
    
call delay_without_control
call delay_without_control
    
goto state1
    
end





