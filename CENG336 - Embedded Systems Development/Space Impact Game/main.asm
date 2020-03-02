; Yavuz Selim YESILYURT 2259166
; Alper KOCAMAN 2169589 

LIST    P=18F8722

#INCLUDE <p18f8722.inc> 
    
CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

ovCount         udata 0x20  
ovCount			    
timeFactor      udata 0x21  ; Will be used for getting the desired 
timeFactor
timer1val_l	udata 0x22
timer1val_l
timer1val_h	udata 0x23
timer1val_h  
shiftCount      udata 0x24  ; Will be used for counting to 10 for complementing
shiftCount		     
asteroidCount   udata 0x25  ; for keeping the asteroid number 
asteroidCount
ovCount2        udata 0x26  
ovCount2	
utilityReg	udata 0x27  ; LAST DIGIT WILL BE USED AS GAMEUPDATE FLAG 6th digit will be used for DontIncrAst
utilityReg		    ; FIRST digit will be used for updateIsr => YANI GameUpdate, DontIncrAst, x, x, x, x, x, updateIsr
colBast	        udata 0x28
colBast
colCast	        udata 0x29
colCast
colDast	        udata 0x2A
colDast
colEast	        udata 0x2B
colEast
colFast	        udata 0x2C  
colFast
asteroidRegister  udata 0x2D  ; Last 2 digits will be used for Shifting operation 
asteroidRegister
colBlaser       udata 0x2E
colBlaser
colClaser       udata 0x2F
colClaser
colDlaser       udata 0x30
colDlaser
colElaser       udata 0x31
colElaser
colFlaser       udata 0x32 
colFlaser
toBeSentLasers	udata 0x33
toBeSentLasers 
craftRegister	udata 0x34
craftRegister			
score0          udata 0x35   
score0
score1          udata 0x36
score1
score2          udata 0x37
score2
score3          udata 0x38
score3 
disp0		udata 0x39
disp0
disp1		udata 0x40
disp1
disp2		udata 0x41
disp2
disp3		udata 0x42
disp3
ovCount3	udata 0x43  ; 5ms needs to happen timeFactor times so in here count to timeFactor
ovCount3	
temp            udata 0x44
temp
temp2           udata 0x45
temp2
	
org     0x00
goto    init

org     0x08
goto    isr   
	
init:
    ; (Disable) clear interrupt & timer regs
    clrf    INTCON
    clrf    INTCON2
    clrf    RCON
    clrf    PIE1
    clrf    TMR1L
    clrf    TMR1H 
    clrf    TMR0L
    clrf    TMR0H 
    
    ; Configure Output Ports
    clrf    LATA
    clrf    LATB
    clrf    LATC
    clrf    LATD
    clrf    LATE
    clrf    LATF
    clrf    LATG
    clrf    LATH
    clrf    LATJ
    
    clrf    TRISA
    clrf    TRISB
    clrf    TRISC
    clrf    TRISD
    clrf    TRISE
    clrf    TRISF
    clrf    TRISG
    clrf    TRISH
    clrf    TRISJ
    
    clrf    PORTA
    clrf    PORTB
    clrf    PORTC
    clrf    PORTD
    clrf    PORTE
    clrf    PORTF
    clrf    PORTG
    clrf    PORTH
    clrf    PORTJ
    
    movlw h'0F' ; Configure A/D
    movwf ADCON1 ; for digital inputs
    
    movlw   b'11000000'
    movwf    TRISA
    movwf    TRISB
    movwf    TRISC
    movwf    TRISD
    movwf    TRISE
    movwf    TRISF
    
    movlw   b'11111111'
    movwf    TRISG
    
    movlw   b'11110000'
    movwf    TRISH
    
    movlw   b'00000000'    
    movwf    TRISJ  
    
    ;Initialize Timer0 -  Configure such that, it will overflow every 5ms
    
    movlw   b'01001000' ; Disable Timer0 by setting TMR0ON to 0 (for now)
    movwf   T0CON       ; T0CON = b'01000111'
	
    ;Initialize Timer1
    movlw   b'11000000' ;Disable Timer1 by setting T1CON to 0 (for now)
    movwf   T1CON 
    
    ;Initialize initial conf for spaceCraft
    movlw   b'00001000' ; TURN ON RA3
    movwf   LATA
    movwf   craftRegister
    
    ; set 0 to seven segment and disp regs
    movlw   b'00111111' 
    movwf   LATJ
    bsf	    LATH, 3
    movwf   disp0
    movwf   disp1
    movwf   disp2
    movwf   disp3
    
    movlw h'00'
    movwf ovCount
    movwf ovCount2
    movwf ovCount3
    movwf asteroidCount
    movwf utilityReg
    movwf colBast
    movwf colCast
    movwf colDast
    movwf colEast
    movwf colFast
    movwf asteroidRegister
    movwf colBlaser
    movwf colClaser
    movwf colDlaser
    movwf colElaser
    movwf colFlaser
    movwf toBeSentLasers
    movwf score0
    movwf score1
    movwf score2
   
    movlw h'01'
    movwf score3

    movlw h'0A' 
    movwf shiftCount    
    
    movlw h'64'
    movwf timeFactor    ; INIT TIMEFACTOR = 100 FOR 500ms
    
; Enable Global and Timer0 overflow interrupts
    movlw   b'10100000' 
    movwf   INTCON
    bsf	T1CON, 0        ; Start timer1

    main:
	btfss	PORTG, 0 ; check if RG0 is pressed
	goto	main
	bsf	T0CON, 7 ; Start Timer0 by setting TMR0ON to 1
	movff	TMR1L , timer1val_l  
	movff	TMR1H , timer1val_h
	goto gameUpdate
	
    
    ; Check RG1/2/3 and update bits
    mainLoop:
	btfsc	PORTG,1 ; fire
	goto	fire
	btfsc	PORTG,2 ; go down
	goto	goDown
	btfsc	PORTG,3 ; go up
	goto	goUp
	btfsc	utilityReg, 0 ; Interrupt happened, Update Isr
	goto	updateIsr
	btfsc	utilityReg, 7 ; GameUpdate flag is set, Update the game
	goto	gameUpdate
	call showScore	
	goto	mainLoop 
    
    ; RG1 is pressed set corresponding digit of Laser Reg from current position of SpaceCraft using Craft Reg
    fire:
	btfsc	PORTG,1
	goto	fire
	movf	toBeSentLasers, 0 ; Move to W
	iorwf	craftRegister, 0 ; add new fire value to W
	movwf	toBeSentLasers ; update sentLasers reg
	goto	mainLoop
    
    ; RG2 is pressed move craft down => change led and alter location in Craft Reg
    goDown:
	btfsc	PORTG,2
	goto	goDown
	movlw	b'00100000'
	cpfseq	craftRegister
	goto	nextGoDown
	goto	mainLoop
	nextGoDown:
	    movf    LATA, 0 ; Move current LATA to W
	    xorwf   craftRegister, 0 ; Get other values of LATA expect old craft location
	    rlncf   craftRegister ; shift craft 1 left
	    andwf  craftRegister , 0
	    btfss STATUS        , 2
	    goto  gameover   
	    iorwf   craftRegister, 0 ; update LATA with new loc of craft 
	    movwf   LATA ; add it to LATA
	    goto    mainLoop
	
    ; RG3 is pressed move craft up => change led and alter location in Craft Reg
    goUp:
    	btfsc	PORTG,3
	goto	goUp
	movlw	b'00000001'
	cpfseq	craftRegister
	goto	nextGoUp
	goto	mainLoop
	nextGoUp:
	    movf    LATA, 0 ; Move current LATA to W
	    xorwf   craftRegister, 0 ; Get other values of LATA expect old craft location
	    rrncf   craftRegister ; shift craft 1 right
	    andwf  craftRegister , 0
	    btfss STATUS        , 2
	    goto  gameover   
	    iorwf   craftRegister, 0 ; update LATA with new loc of craft
	    movwf   LATA ; add it to LATA
	    goto    mainLoop

    isr:
	btfss	INTCON, 2 ; check if tmr0 flag is set
	retfie	FAST; else
	bcf	INTCON, 2 ; clear tmr0 flag 
	movlw   h'12'      
	movwf   TMR0L
	bsf	utilityReg, 0 ; Set updateIsr bit
	retfie	FAST

    updateIsr:
	bcf	utilityReg, 0 ; Clear updateIsr bit
	movlw	h'A8'
	cpfseq	ovCount ; check if ovCount 
	goto	incrOvcount ; else increment it
	goto	Ovcount2 ; if yes directly go to Ovcount2 process 
	incrOvcount:
	    incf    ovCount ; increment ovCount
	    goto    mainLoop
	Ovcount2:
	    movlw   h'1F' 
	    cpfseq  ovCount2 ; check if ovCount2 
	    goto    incrOvcount2 ; else increment it
	    goto    Ovcount3 ; if yes directly go to Ovcount3 process 
	    incrOvcount2:
		incf    ovCount2 ; increment ovCount2
		goto    mainLoop
	    Ovcount3:
		btfsc score3 , 0
		goto  nextTurn0
		btfsc score3 , 1
		goto   nextTurn1
		btfsc score3 , 2
		goto   nextTurn2
		nextTurn0:
		    bcf score3 , 0 
		    bsf score3 , 1
		    goto finishScore3
		nextTurn1:
		    bcf score3 , 1 
		    bsf score3 , 2
		    goto finishScore3
		nextTurn2:
		    bcf score3 , 2 
		    bsf score3 , 0    
	    finishScore3:	
		movlw	h'00' ; dont forget to clear ovCount and ovCount2 for another 5ms calculation
		movwf	ovCount 
		movwf	ovCount2
		incf    ovCount3 ; increment ovCount3
		movf	ovCount3, 0 ; move ovCount3 to W
		cpfseq  timeFactor ; check if ovCount3 == timeFactor
		goto    mainLoop
		interrupted: ; if yes it means that we are interrupted (means 5ms happened timefactor times)
		    movlw   h'00'   
		    movwf   ovCount3 ; immediately clear ovCount3 
		    bsf	    utilityReg, 7 ; Set gameUpdate bit
		    goto    mainLoop
				
    gameUpdate:
	bcf	utilityReg, 7 ; dont forget to clear Update flag!
	btfss   utilityReg, 6 ; check if 'dontIncrAst' is set
	incf    asteroidCount ; if not set increment asteroidCount
	movlw   h'0B' ; else dont increment and continue
	cpfslt  asteroidCount ; check if asteroidCount < 11
	goto    isrAstCheck0 ; else timefactor = 80
	goto	updateStuff ; if yes no need to update timefactor(=100)
	isrAstCheck0:
	    movlw   h'1F' 
	    cpfslt  asteroidCount ; check if asteroidCount < 31
	    goto    isrAstCheck1 ; else timefactor = 60
	    movlw   h'50' ; if yes update timefactor = 80
	    movwf   timeFactor
	    goto    updateStuff 
	    isrAstCheck1:
		movlw   h'33' 
		cpfslt  asteroidCount ; check if asteroidCount < 51
		goto    isrAstCheck2 ; else timefactor = 40
		movlw   h'3C' ; if yes update timefactor = 60
		movwf   timeFactor
		goto	updateStuff ;
		isrAstCheck2:
		    bsf	    utilityReg, 6 ; Dont forget to set dontIncrementAst = True
		    movlw   h'28' ; if yes update timefactor = 40
		    movwf   timeFactor
	
	updateStuff:
	
	    ; Create 1 Asteroid here
	    call createAsteroid 
	    
	    ; CHECK TYPE1 COLLISIONS AND UPDATE THE REGs and Scores accordingly (dont update LATs)

	    ; Check toBeSentLasers colBast
	    ; type 1 - close one
	    movff toBeSentLasers , temp
	    movff toBeSentLasers , temp2
	    comf  colBast        , 0
	    andwf toBeSentLasers 
	    comf  temp           , 0
	    andwf colBast 

	    movf  toBeSentLasers , 0 ; move latest toBeSentLasers to W
	    xorwf temp2
	    call  countOnes

	    ; Check colBlaser colCast
	    ; type 1 - close one
	    movff colBlaser , temp
	    movff colBlaser , temp2
	    comf  colCast        , 0
	    andwf colBlaser 
	    comf  temp           , 0
	    andwf colCast 

	    movf  colBlaser , 0 ; move latest colBlaser to W
	    xorwf temp2
	    call  countOnes

	    ; Check colClaser colDast 
	    ; type 1 - close one
	    movff colClaser , temp
	    movff colClaser , temp2
	    comf  colDast        , 0
	    andwf colClaser 
	    comf  temp           , 0
	    andwf colDast 

	    movf  colClaser , 0 ; move latest colClaser to W
	    xorwf temp2
	    call  countOnes

	    ; Check colDlaser colEast 
	    ; type 1 - close one
	    movff colDlaser , temp
	    movff colDlaser , temp2
	    comf  colEast        , 0
	    andwf colDlaser 
	    comf  temp           , 0
	    andwf colEast 

	    movf  colDlaser , 0 ; move latest colDlaser to W
	    xorwf temp2
	    call  countOnes

	    ; Check colElaser colFast
	    ; type 1 - close one
	    movff colElaser , temp
	    movff colElaser , temp2
	    comf  colFast        , 0
	    andwf colElaser 
	    comf  temp           , 0
	    andwf colFast 

	    movf  colElaser , 0 ; move latest colElaser to W
	    xorwf temp2
	    call  countOnes

	    ; Check colFlaser asteroidRegister
	    ; type 1 - close one
	    movff colFlaser , temp
	    movff colFlaser , temp2
	    comf  asteroidRegister , 0
	    andwf colFlaser 
	    comf  temp           , 0
	    andwf asteroidRegister 

	    movf  colFlaser , 0 ; move latest colFlaser to W
	    xorwf temp2
	    call  countOnes
	    
	    ; NOW CHECK TYPE2 COLLISIONS AND UPDATE THE REGs and Scores accordingly, ALSO UPDATE THE LATs THIS TIME

	    ; check ast hit the spacecraft, Update LATA
	    movf  craftRegister , 0
	    andwf colBast       , 0
	    btfss STATUS        , 2
	    goto  gameover           ; else do calculations
	    movf  craftRegister , 0
	    iorwf colBast       , 0
	    movwf LATA

	    ; type 2 - Space In Between toBeSentLasers colCast, Update LATB
	    movff toBeSentLasers , temp
	    movff toBeSentLasers , temp2
	    comf  colCast        , 0
	    andwf toBeSentLasers 
	    movff colCast        , LATB       
	    comf  temp           , 0
	    andwf colCast
	    movf  toBeSentLasers , 0
	    iorwf LATB

	    ; W has latest toBeSentLasers here
	    xorwf temp2
	    call  countOnes

	    ;---------------------------
	    ; type 2 - Space In Between colBlaser colDast, Update LATC
	    movff colBlaser , temp
	    movff colBlaser , temp2
	    comf  colDast        , 0
	    andwf colBlaser 
	    movff colDast        , LATC       
	    comf  temp           , 0
	    andwf colDast
	    movf  colBlaser , 0
	    iorwf LATC

	    ; W has latest colBlaser here
	    xorwf temp2
	    call  countOnes

	    ;---------------------------

	    ; type 2 - Space In Between colClaser colEast, Update LATD
	    movff colClaser , temp
	    movff colClaser , temp2
	    comf  colEast        , 0
	    andwf colClaser 
	    movff colEast        , LATD       
	    comf  temp           , 0
	    andwf colEast
	    movf  colClaser , 0
	    iorwf LATD

	    ; W has latest colClaser here
	    xorwf temp2
	    call  countOnes ; count 1's in temp2

	    ;---------------------------

	    ; type 2 - Space In Between colDlaser colFast, Update LATE
	    movff colDlaser , temp
	    movff colDlaser , temp2
	    comf  colFast        , 0
	    andwf colDlaser 
	    movff colFast        , LATE       
	    comf  temp           , 0
	    andwf colFast
	    movf  colDlaser , 0
	    iorwf LATE

	    ; W has latest colDlaser here
	    xorwf temp2
	    call  countOnes ; count 1's in temp2

	    ;---------------------------

	    ; type 2 - Space In Between colElaser asteroidRegister, Update LATF
	    movff colElaser , temp
	    movff colElaser , temp2
	    comf  asteroidRegister , 0
	    andwf colElaser 
	    movff asteroidRegister , LATF       
	    comf  temp           , 0
	    andwf asteroidRegister
	    movf  colElaser , 0
	    iorwf LATF

	    ; W has latest colElaser here
	    xorwf temp2
	    call  countOnes ; count 1's in temp2

	    movff colElaser , colFlaser
	    movff colDlaser , colElaser
	    movff colClaser , colDlaser
	    movff colBlaser , colClaser
	    movff toBeSentLasers , colBlaser
	    clrf  toBeSentLasers 

	    movff colCast , colBast
	    movff colDast , colCast
	    movff colEast , colDast
	    movff colFast , colEast
	    movff asteroidRegister , colFast 

	    goto mainLoop
	
    gameover:                
		goto init

    countOnes
	movlw h'06'
	movwf temp
	Lub:
	    btfsc temp2, 0
	    call IncrementScore ; if 0th bit is 1, incrScore()
	    rrncf temp2 ; else (0)
	    decfsz temp
	    goto Lub
	    return	    
    
createAsteroid
    ; first find the place for new asteroid
    
    clrf asteroidRegister
    btfss timer1val_l , 0     ; last element checked
    goto xxxxx__0
    goto xxxxx__1
    
    xxxxx__0:
    
	btfss timer1val_l , 1
	goto  xxxxx_00
	goto  xxxxx_10
    
    xxxxx__1:
    
	btfss timer1val_l , 1
	goto  xxxxx_01
	goto  xxxxx_11
	
    xxxxx_00:
    
	btfss timer1val_l , 2
	goto  xxxxx000
	goto  xxxxx100
	
    xxxxx_01:
    
	btfss timer1val_l , 2
	goto  xxxxx001
	goto  xxxxx101
	
    xxxxx_10:
    
	btfss timer1val_l , 2
	goto  xxxxx010
	goto  xxxxx110

    xxxxx_11:
	
	btfss timer1val_l , 2
	goto  xxxxx011
	goto  xxxxx111
	
    xxxxx000:
	
	bsf asteroidRegister , 0 
	goto shift_complement
    
    xxxxx100:
	
	bsf asteroidRegister , 4 
	goto shift_complement
    
    xxxxx001:
    
	bsf asteroidRegister , 1 
	goto shift_complement
	
    xxxxx101:
    
	bsf asteroidRegister , 5 
	goto shift_complement
	
    xxxxx010:
    
	bsf asteroidRegister , 2 
	goto shift_complement
	
    xxxxx110:
    
	bsf asteroidRegister , 0 
	goto shift_complement
	
    xxxxx011:
    
	bsf asteroidRegister , 3 
	goto shift_complement
	
    xxxxx111:
	
	bsf asteroidRegister , 1 
    
    shift_complement:
    
	btfsc timer1val_l , 0
	bsf   asteroidRegister     , 6
	btfsc timer1val_h , 0
	bsf   asteroidRegister     , 7
	rrncf timer1val_l
	rrncf timer1val_h
	btfss asteroidRegister , 7
	call  timer1l_makefirst0
	btfsc asteroidRegister , 7
	call  timer1l_makefirst1
	btfss asteroidRegister , 6
	call  timer1h_makelast0
	btfsc asteroidRegister , 6
	call  timer1h_makelast1
	decfsz shiftCount 
	return
	call complement
	return
    
	timer1l_makefirst0:
    
	    bcf timer1val_l , 7
	    return
	
	timer1l_makefirst1:    
    
	    bsf timer1val_l , 7
	    return
	    
	timer1h_makelast0:
    
	    bcf timer1val_h , 7
	    return 
    
	timer1h_makelast1:
    
	    bsf timer1val_h , 7
	    return
	    
	complement:
    
	    comf timer1val_l
	    comf timer1val_h
	    movlw h'0A'
	    movwf shiftCount
	    return
	     
IncrementScore   
    
    incf  score0   
    btfss score0 , 0
    goto xxxx___0 
    goto xxxx___1 
    
    xxxx___0:
	btfss score0 , 1
	goto xxxx__00 
	goto xxxx__10 
    xxxx___1:
	btfss score0 , 1
	goto xxxx__01 
	goto xxxx__11
    xxxx__00:
	btfss score0 , 2
	goto xxxx_000 
	goto xxxx_100 
    xxxx__01:
	btfss score0 , 2
	goto xxxx_001 
	goto xxxx_101 
    xxxx__10:
	btfss score0 , 2
	goto xxxx_010 
	goto xxxx_110 
    xxxx__11:
	btfss score0 , 2
	goto xxxx_011 
	goto xxxx_111
    xxxx_001:	
        btfss score0 , 3
	goto xxxx0001     ;lead to 1
	goto xxxx1001     ;lead to 9 
    xxxx_010:
	btfss score0 , 3   
	goto xxxx0010     ; lead to 2
	goto xxxx1010     ; lead to 10
	
    xxxx0001:               ; 1
	movlw   b'00000110' ; set 1 to seven segment
	movwf   disp0
	return
    xxxx0010:               ;2
	movlw   b'01011011' ; set 2 to seven segment
	movwf   disp0
	return
    xxxx_011:               ; must be 3
	movlw   b'01001111' ; set 3 to seven segment
	movwf   disp0
	return
    xxxx_100:               ; must be 4
	movlw   b'01100110' ; set 4 to seven segment
	movwf   disp0
	return
    xxxx_101:               ; must be 5
        movlw   b'01101101' ; set 5 to seven segment
	movwf   disp0
	return
    xxxx_110:               ;must be 6
	movlw   b'01111101' ; set 6 to seven segment
	movwf   disp0
	return
    xxxx_111:               ; must be 7
	movlw   b'00000111' ; set 7 to seven segment
	movwf   disp0
	return
    xxxx_000:               ; must be 8    
	movlw   b'01111111' ; set 8 to seven segment
	movwf   disp0
	return
    xxxx1001:	            ;9
        movlw   b'01101111' ; set 9 to seven segment
	movwf   disp0
	return
    xxxx1010:               ;10
	movlw   b'00111111' ; set 0 to seven segment 
	movwf   disp0
	clrf    score0
                            ; second digit will be updated
    bsf   score3 , 5        ; second digit flag
    incf  score1   
    btfss score1 , 0
    goto d1xxxx___0 
    goto d1xxxx___1 
    
    d1xxxx___0:
	btfss score1 , 1
	goto d1xxxx__00 
	goto d1xxxx__10 
    d1xxxx___1:
	btfss score1 , 1
	goto d1xxxx__01 
	goto d1xxxx__11
    d1xxxx__00:
	btfss score1 , 2
	goto d1xxxx_000 
	goto d1xxxx_100 
    d1xxxx__01:
	btfss score1 , 2
	goto d1xxxx_001 
	goto d1xxxx_101 
    d1xxxx__10:
	btfss score1 , 2
	goto d1xxxx_010 
	goto d1xxxx_110 
    d1xxxx__11:
	btfss score1 , 2
	goto d1xxxx_011 
	goto d1xxxx_111
    d1xxxx_001:	
        btfss score1 , 3
	goto d1xxxx0001     ;lead to 1
	goto d1xxxx1001     ;lead to 9 
    d1xxxx_010:
	btfss score1 , 3   
	goto d1xxxx0010     ; lead to 2
	goto d1xxxx1010     ; lead to 10
	
    d1xxxx0001:               ; 1
	movlw   b'00000110' ; set 1 to seven segment
	movwf   disp1
	return
    d1xxxx0010:               ;2
	movlw   b'01011011' ; set 2 to seven segment
	movwf   disp1
	return
    d1xxxx_011:               ; must be 3
	movlw   b'01001111' ; set 3 to seven segment
	movwf   disp1
	return
    d1xxxx_100:               ; must be 4
	movlw   b'01100110' ; set 4 to seven segment
	movwf   disp1
	return
    d1xxxx_101:               ; must be 5
        movlw   b'01101101' ; set 5 to seven segment
	movwf   disp1
	return
    d1xxxx_110:               ;must be 6
	movlw   b'01111101' ; set 6 to seven segment
	movwf   disp1
	return
    d1xxxx_111:               ; must be 7
	movlw   b'00000111' ; set 7 to seven segment
	movwf   disp1
	return
    d1xxxx_000:               ; must be 8    
	movlw   b'01111111' ; set 8 to seven segment
	movwf   disp1
	return
    d1xxxx1001:	            ;9
        movlw   b'01101111' ; set 9 to seven segment
	movwf   disp1
	return
    d1xxxx1010:               ;10
	movlw   b'00111111' ; set 0 to seven segment 
	movwf   disp1
	clrf    score1   	
                            ; third digit will be updated
    bsf   score3 , 6        ; third digit flag
    incf  score2   
    btfss score2 , 0
    goto d2xxxx___0 
    goto d2xxxx___1 
    
    d2xxxx___0:
	btfss score2 , 1
	goto d2xxxx__00 
	goto d2xxxx__10 
    d2xxxx___1:
	btfss score2 , 1
	goto d2xxxx__01 
	goto d2xxxx__11
    d2xxxx__00:
	btfss score2 , 2
	goto d2xxxx_000 
	goto d2xxxx_100 
    d2xxxx__01:
	btfss score2 , 2
	goto d2xxxx_001 
	goto d2xxxx_101 
    d2xxxx__10:
	btfss score2 , 2
	goto d2xxxx_010 
	goto d2xxxx_110 
    d2xxxx__11:
	btfss score2 , 2
	goto d2xxxx_011 
	goto d2xxxx_111
    d2xxxx_001:	
        btfss score2 , 3
	goto d2xxxx0001     ;lead to 1
	goto d2xxxx1001     ;lead to 9 
    d2xxxx_010:
	btfss score2 , 3   
	goto d2xxxx0010     ; lead to 2
	goto d2xxxx1010     ; lead to 10
	
    d2xxxx0001:               ; 1
	movlw   b'00000110' ; set 1 to seven segment
	movwf   disp2
	return
    d2xxxx0010:               ;2
	movlw   b'01011011' ; set 2 to seven segment
	movwf   disp2
	return
    d2xxxx_011:               ; must be 3
	movlw   b'01001111' ; set 3 to seven segment
	movwf   disp2
	return
    d2xxxx_100:               ; must be 4
	movlw   b'01100110' ; set 4 to seven segment
	movwf   disp2
	return
    d2xxxx_101:               ; must be 5
        movlw   b'01101101' ; set 5 to seven segment
	movwf   disp2
	return
    d2xxxx_110:               ;must be 6
	movlw   b'01111101' ; set 6 to seven segment
	movwf   disp2
	return
    d2xxxx_111:               ; must be 7
	movlw   b'00000111' ; set 7 to seven segment
	movwf   disp2
	return
    d2xxxx_000:               ; must be 8    
	movlw   b'01111111' ; set 8 to seven segment
	movwf   disp2
	return
    d2xxxx1001:	            ;9
        movlw   b'01101111' ; set 9 to seven segment
	movwf   disp2
	return
    d2xxxx1010:               ;10
	movlw   b'00111111' ; set 0 to seven segment 
	movwf   disp2
	clrf    score2   		
        return              ; third digit will be updated	
	
showScore
	
    call update1st
    btfsc score3 , 5
    call  update2nd
    btfsc score3 , 6
    call  update3rd
    return 
    
    update1st
	btfss score3 , 0
	return
	bcf   LATH , 1
	bcf   LATH , 2
	bsf   LATH , 3
	movff disp0 , LATJ
	return
    update2nd
	btfss score3  , 1
	return
	bcf   LATH , 3
	bcf   LATH , 1
	bsf   LATH , 2
	movff disp1 , LATJ
	return
    update3rd
	btfss score3  , 2
	return
	bcf   LATH , 2
	bcf   LATH , 3
	bsf   LATH , 1
	movff disp2 , LATJ
	return
end
