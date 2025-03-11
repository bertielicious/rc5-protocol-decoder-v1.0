#include "constVar.h"
#include "lcdCommand.h"
#include "enablePulseLCD.h"
void clearLCD(void)
{
    RS = LO;
    D7 = 0;
    D6 = 0;
    D5 = 0;
    D4 = 0;
     __delay_ms(5);
     enablePulseLCD();
     
    RS = LO;
    D7 = 0;
    D6 = 0;
    D5 = 0;
    D4 = 1;
     __delay_ms(5);
     enablePulseLCD();
    
   
}
