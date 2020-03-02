/* 
Yavuz Selim YESILYURT - 2259166
Alper KOCAMAN - 2169589
*/

#include "common.h"

/* lcdtoggle is used for changing part of the map that is printed on the LCD */
/* portBpressed is used for if RB4 is pressed by the user to change the part of the LCD that is printed*/
short int lcdToggle = 0, portBpressed = 0; 

/**********************************************************************
 * Function you want to call when an IT occurs.
 **********************************************************************/
  extern void AddOneTick(void);
/*extern void MyOwnISR(void); */
  void InterruptVectorL(void);
  void InterruptVectorH(void);

/**********************************************************************
 * General interrupt vector. Do not modify.
 **********************************************************************/
#pragma code IT_vector_low=0x18
void Interrupt_low_vec(void)
{
   _asm goto InterruptVectorL  _endasm
}
#pragma code

#pragma code IT_vector_high=0x08
void Interrupt_high_vec(void)
{
   _asm goto InterruptVectorH  _endasm
}
#pragma code

/**********************************************************************
 * General ISR router. Complete the function core with the if or switch
 * case you need to jump to the function dedicated to the occuring IT.
 * .tmpdata and MATH_DATA are saved automaticaly with C18 v3.
 **********************************************************************/
#pragma	code _INTERRUPT_VECTORL = 0x003000
#pragma interruptlow InterruptVectorL 
void InterruptVectorL(void)
{
	EnterISR();
	
	if (INTCONbits.TMR0IF == 1)
		AddOneTick();
	
	if (PIR1bits.TX1IF == 1) {
		transmitData(); // transmission interrupt occurs
	}
	if (PIR1bits.RC1IF == 1) {
		dataReceived();
		PIR1bits.RC1IF = 0;	// clear RC1IF flag
	}
    if (RCSTA1bits.OERR)
    {
      RCSTA1bits.CREN = 0;
      RCSTA1bits.CREN = 1;
    }
    if (INTCONbits.RBIF == 1) { 
        
        // user pressed RB4
        if(PORTBbits.RB4)
            portBpressed = 1 ; // portBpressed is set
        else if (!PORTBbits.RB4 && portBpressed) {
        	// this means that RB4 is released now 
        	// portBpressed should be unset in order to take next RB4 presses.
        	//lcdToggle should be reversed.
            portBpressed = 0 ;
            lcdToggle ^= 1;
        }
		INTCONbits.RBIF = 0 ; // RB interrupt flag should be cleared 
    }
    
	LeaveISR();
}
#pragma	code

/* BE CARREFULL : ONLY BSR, WREG AND STATUS REGISTERS ARE SAVED  */
/* DO NOT CALL ANY FUNCTION AND USE PLEASE VERY SIMPLE CODE LIKE */
/* VARIABLE OR FLAG SETTINGS. CHECK THE ASM CODE PRODUCED BY C18 */
/* IN THE LST FILE.                                              */
#pragma	code _INTERRUPT_VECTORH = 0x003300
#pragma interrupt InterruptVectorH nosave=FSR0, TBLPTRL, TBLPTRH, TBLPTRU, TABLAT, PCLATH, PCLATU, PROD, section(".tmpdata"), section("MATH_DATA")
void InterruptVectorH(void)
{
  if (INTCONbits.INT0IF == 1)
    INTCONbits.INT0IF = 0;
}
#pragma	code



extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x003400
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code


/* End of file : int.c */
