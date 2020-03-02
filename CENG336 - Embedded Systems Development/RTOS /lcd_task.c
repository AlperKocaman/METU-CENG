/* 
Yavuz Selim YESILYURT - 2259166
Alper KOCAMAN - 2169589
*/


/**********************************************************************
 *---------------------------PURPOSE OF THE LCD TASK------------------
 	- properly printing current map information to LCD
 **********************************************************************/

/**********************************************************************
 * ----- LOCAL FUNCTIONS EXPLANATIONS(only Lcd_refresh() changed ) ----
 *Lcd_refresh() -> prints related part of the map information by using lcdToggle
 **********************************************************************/

#include "common.h"
#include <p18cxxx.h>
#include <p18f8722.h>
#include "LCD.h"

/**********************************************************************
 * ----------------------- LCD USER SETTINGS --------------------------
 **********************************************************************/
#define COLUMN            16              /* Character number per line */
#define LINE              2               /*      Number of line       */


/**********************************************************************
 * --------------- LCD function prototypes -----------------
 **********************************************************************/
void InitLCD(void);
void ToggleEpinOfLCD(void);
void WriteDataToLCD(char value);
void WriteStringToLCD(const char *s);
void WriteCommandToLCD(unsigned char Command);
void Delay_LCD_ms(unsigned int delay);
void Lcd_refresh(void);
void WaitState(void);
void ClearLCDScreen(void);
void Lcd_position(unsigned char type, unsigned char value);
void LcdPrintData(unsigned char value, unsigned char positionX, unsigned char positionY);
void LcdPrintString(const char *s, unsigned char positionX,  unsigned char positionY);

/**********************************************************************
 * ---------------------- LCD global variables ------------------------
 **********************************************************************/
EventMaskType LCDevent;
unsigned char LCDchar[LINE][COLUMN];
extern char map[4][16];
extern lcdToggle;

/**********************************************************************
 * ----------------------------- LCD TASK -----------------------------
 * 
 * Refresh LCD screen whenever an LCD_EVENT is fired!
 * 
 **********************************************************************/
TASK(LCD)
{
    
    PIE1bits.RC1IE = 1;		// enable USART receive interrupt
    INTCONbits.RBIE = 1; 	// enable RB interrrupt
    INTCONbits.RBIF = 0; 	// RB flag is cleared
    ADCON1 = 0x8E;				
    ADCON0 = 0x00;
    InitLCD();

    SetRelAlarm(LCD_ALARM2, 1, 1000);
    while(1)
    {
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        Lcd_refresh();
    }
    TerminateTask();
}

/**********************************************************************
 * Print at screen what is on the LCDchar buffer (both lines).
 *
 * @param  void
 * @return void 
 **********************************************************************/
void Lcd_position(unsigned char line, unsigned char pos)
{
    switch(line)
    {
        case 0:
            WriteCommandToLCD(0x80+pos);
            break;
        case 1:
            WriteCommandToLCD(0xc0+pos);
            break;
    };
    
}

void Lcd_refresh(void)
{
  unsigned char i, j;
  
  /* cursor should be gone to the beginning of the first line */
  WriteCommandToLCD(0x02);
  if(lcdToggle == 0){ 				// first 2 lines should be pressed
     
  for ( i = 0 ; i < LINE; i++) 		// for loop to print two lines
    {
    Lcd_position(i, 0); 
    for (j = 0; j < COLUMN; j++) 	// for loop to print characters
      WriteDataToLCD(map[i][j]); 	// related map character is printed with the aid of this function
    }
       
  }
  else{ 							// 3rd and 4th lines should be pressed
  
    for (i = 2 ; i < LINE+2; i++) 	// for loop to print two lines
    {
      Lcd_position(i-2, 0);
      for (j = 0; j < COLUMN; j++) 	// for loop to print characters
        WriteDataToLCD(map[i][j]); 	// related map character is printed with the aid of this function
    }
      
  }
}

/**********************************************************************
 * Write a command or data on the LCD bus.
 *
 * @param  value     IN  value of the data placed on the bus
 * @return void 
 **********************************************************************/
void WriteCommandToLCD(unsigned char Command)
{
    WaitState();
    Nop();
    LATBbits.LATB2 = 0;                 // It is a command

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD |(Command&0xF0);      // Write Upper nibble of data
    ToggleEpinOfLCD();                  // Give pulse on E pin

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD | ((Command<<4)&0xF0);// Write Lower nibble of data

    ToggleEpinOfLCD();                  // Give pulse on E pin
}

void WriteStringToLCD(const char *s)
{
    WaitState();
    Nop();
    while(*s)
        WriteDataToLCD(*s++);   // print first character on LCD
}

/**********************************************************************
 * Write the data on the bus (8 bits mode only).
 *
 * @param  c         IN  data written 
 * @return void 
 **********************************************************************/
void WriteDataToLCD(char value)
{
    WaitState();
    Nop();
    LATBbits.LATB2 = 1;                 // It is data

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD | (value&0xF0);     // Write Upper nibble of data
    ToggleEpinOfLCD();                  // Give pulse on E pin

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD | ((value<<4)& 0xF0); // Write Lower nibble of data


    ToggleEpinOfLCD();                  // Give pulse on E pin
    Nop(); Nop();
    Nop(); Nop();
}

/**********************************************************************
 * Enable the data present on the bus.
 *
 * @param  void
 * @return void 
 **********************************************************************/
void ToggleEpinOfLCD(void)
{
    LATBbits.LATB5 = 1;                // Give a pulse on E pin
    Delay_LCD_ms(E_Delay);             // so that LCD can latch the
    LATBbits.LATB5 = 0;                // data from data bus
    Delay_LCD_ms(E_Delay);
}

/**********************************************************************
 * Generic routine to create a delay of many milliseconds.
 *
 * @param  delay     IN  time to wait in ms
 * @return void 
 **********************************************************************/
void Delay_LCD_ms(unsigned int delay)
{
  SetRelAlarm(LCD_ALARM, delay, 0);
  WaitEvent(ALARM_EVENT);
  GetEvent(LCD_TASK_ID, &LCDevent);
  if (LCDevent & ALARM_EVENT)
    ClearEvent(ALARM_EVENT);
  return;
}

/**********************************************************************
 * Init phase of the LCD.
 * Do not modify this sequence.
 *
 * @param  void
 * @return void 
 **********************************************************************/
void InitLCD(void)
{

    //TRISA = 0;
    //TRISC = 0;
    TRISE = 0;
    TRISF = 0;
    TRISG = 0;

    TRISH = 0;
    TRISJ = 0;

    //PORTA = 0;
    //PORTC = 0;
    PORTE = 0;
    PORTF = 0;
    PORTG = 0;

    PORTH = 0;
    PORTJ = 0;


    LATBbits.LATB5  = 0;   // E  = 0
    LATBbits.LATB2  = 0;   // RS = 0
    LATDbits.LATD4  = 0;   // Data bus = 0
    LATDbits.LATD5  = 0;   // Data bus = 0
    LATDbits.LATD6  = 0;   // Data bus = 0
    LATDbits.LATD7  = 0;   // Data bus = 0
    TRISBbits.TRISB5 = 0;   // Make Output
    TRISBbits.TRISB2 = 0;   // Make Output
    TRISDbits.TRISD4 = 0;   // Make Output
    TRISDbits.TRISD5 = 0;   // Make Output
    TRISDbits.TRISD6 = 0;   // Make Output
    TRISDbits.TRISD7 = 0;   // Make Output
    LATBbits.LATB5  = 0;   // E  = 0
    LATBbits.LATB2  = 0;   // RS = 0
    
    TRISBbits.TRISB4 = 1;   // In order to make RB4 input

        ///////////////// Reset process from datasheet //////////////
    Delay_LCD_ms(15);
    Delay_LCD_ms(15);

	PORTD &= 0x0F;			  // Make Data pins zero
	PORTD |= 0x30;			  // Write 0x3 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

    Delay_LCD_ms(6);

	PORTD &= 0x0F;			  // Make Data pins zero
	PORTD |= 0x30;			  // Write 0x3 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

    Delay_LCD_ms(1);
    //__delay_us(300);

	PORTD &= 0x0F;			  // Make Data pins zero
	PORTD |= 0x30;			  // Write 0x3 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

    Delay_LCD_ms(2);

	PORTD &= 0x0F;			  // Make Data pins zero
	PORTD |= 0x20;			  // Write 0x2 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

    Delay_LCD_ms(2);
  /////////////// Reset Process End ////////////////
	WriteCommandToLCD(0x2C);    //function set  //2C ya da 2D
	WriteCommandToLCD(0x0C);    //display on,cursor off,blink off //OxOC cursor offf
	WriteCommandToLCD(0x01);    //clear display


}

/**********************************************************************
 * Copy a string of characters into the LCDchar buffer.
 *
 * @param  s         IN  string to copy into the buffer
 * @param  positionX IN  column selection
 * @param  positionY IN  line selection
 * @return void 
 **********************************************************************/
void LcdPrintString(const char *s,  unsigned char positionX, unsigned char positionY)
{
  while (*s)
  {
    LCDchar[positionY][positionX] = *s++;
    positionX++;
  }
}

/**********************************************************************
 * Convert a data (8 bits only) into a string of 2 characters.
 *
 * @param  value     IN  Value converted in string of characters
 * @param  positionX IN  column selection
 * @param  positionY IN  line selection
 * @return void
 **********************************************************************/
void LcdPrintData(unsigned char value, unsigned char positionX, unsigned char positionY)
{
  LCDchar[positionY][positionX] = 0x30 + (value / 10);
  LCDchar[positionY][positionX+1] = 0x30 + (value % 10);
}

/**********************************************************************
 * Erase the local buffer LCDchar.
 *
 * @param  void
 * @return void 
 **********************************************************************/
void ClearLCDScreen(void)       // Clear the Screen and return cursor to zero position
{
    WriteCommandToLCD(0x01);    // Clear the screen
    Delay_LCD_ms(2);              // Delay for cursor to return at zero position
}

/**********************************************************************
 * Wait until LCD is not busy
 *
 * @param  void
 * @return void 
 **********************************************************************/
void WaitState(void)
{
    Delay_LCD_ms(1);
    return;
}

/* End of File : lcd_task.c */