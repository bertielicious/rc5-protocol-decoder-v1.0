/*
 * File:   main.c
 * Author: User
 *
 * Created on 08 February 2025, 12:30
 */


#include "constVar.h"
#include "deviceConfigBits.h"
#include "configOsc.h"
#include "configPins.h"
#include "putch.h"
#include "configEUSART.h"
#include "configIOC.h"
#include "resetRC5.h"
#include "stateMachine.h"
#include "LCD1602init.h"
#include "enablePulseLCD.h"
#include "byteToNib.h"
#include "nibToBin.h"
#include "lcdCommand.h"
#include "clearLCD.h"
#include "LCDwriteData.h"
#include "splashScreen.h"

void main(void) 
{
    //RW = LO;    //always write to LCD
    LED = LO;
    configOsc();
    configPins();
    configEUSART();
    configIOC();
    enablePulseLCD();
    LCD1602init();
    
  uint8_t D4L, D5L, D6L, D7L, D4H, D5H, D6H, D7H;
    
    printf("RC5 protocol\n");
    uint8_t string[13] = "RC5 protocol";
    uint8_t *ascii;
    ascii = string;
    uint8_t lowN, highN = 0;
     
    fourBit binary;
    fourBit *ptr;
    ptr = &binary;
    
   lcdCommand(0xc2);
 
    while(*ascii != 0)
    {  
       // splashScreen(ascii);
        
        byteToNib(*ascii, &lowN, &highN);
       //convert low and high nibbles to binary
        nibToBin(&binary, &lowN, &highN);
 
        RS = HI;
        D7 = ptr->D7H;
        D6 = ptr->D6H;
        D5 = ptr->D5H;
        D4 = ptr->D4H;
       
        enablePulseLCD();
      
        
       // ascii= ascii + 1;
        
        //use D4L-D7L to drive port pins D4 - D7
       
        RS = HI;
        D7 = ptr->D7L;
        D6 = ptr->D6L;
        D5 = ptr->D5L;
        D4 = ptr->D4L;
        
        enablePulseLCD();   
        
        ascii= ascii + 1;
    }
   __delay_ms(1500);
   //clearLCD();
    
    
    while(1)
    {
       while(IR == HI && has_run !=1)
           ;    // wait for first button press on RC5 handset
            while(IR == LO && has_run !=1)
                ;
            if(IR == HI && has_run !=1)
            {
                bits--;
                has_run = 1;                // this block only runs once until system is reset
                INTCONbits.IOCIE = 0;       // master switch disable for interrupt on change   
                RC5_code = RC5_code | 1<<bits; // generates initial RC5 code S1 of 0x2000
                bits--;
                RC5_code = RC5_code | 1<<bits; // generates initial RC5 code S2 of 0x1000
                bits--;                        // keep track of how many of the 14 RC5 bits have been consumed
                state = MID1;
                TMR1H = 0x00;
                TMR1L = 0x00;
                INTCONbits.IOCIE = 1;       // master switch enable for interrupt on change     
                IOCBPbits.IOCBP5 = 0;       // disable interrupt on rising edge
                IOCBNbits.IOCBN5 = 1;       // enable interrupt on falling edge
            }   
            
            else if(IOCIF !=1 && (bits + 1) == 0)  // if no interrupt and all 14 RC5 bits have been consumed by state machine
            {
                printf("RC5 code = %x\n", RC5_code);
               
                
                resetRC5();
              
                T1CONbits.TMR1ON = 0;
            
        }
       /*Test LCD IO all good
       LATAbits.LATA4 = ~LATAbits.LATA4;
       LATAbits.LATA5 = ~LATAbits.LATA5;
       LATBbits.LATB6 = ~LATBbits.LATB6;
       LATCbits.LATC3 = ~LATCbits.LATC3;
       LATCbits.LATC6 = ~LATCbits.LATC6;
       LATCbits.LATC2 = ~LATCbits.LATC2;
       LATBbits.LATB4 = ~LATBbits.LATB4;
       __delay_ms(1000);*/
       
        
    }
                
    return;
}

