#include "constVar.h"
#include "enablePulseLCD.h"
void LCDwriteData(uint8_t data)
{
   // declare struct variable binary of type fourBit
    fourBit binary;
    
    //declare pointer of type fourBit to access the structure members
    fourBit *ptr;
    
    // direct the struct pointer to point at the struct variable binary
    ptr = &binary;
    
    //send high byte to LCD
    RS = HI;
    ptr->D7H = (data & 0x80)>>7;
    ptr->D6H = (data & 0x40)>>6;
    ptr->D5H = (data & 0x20)>>5;
    ptr->D4H = (data & 0x10)>>4;
    __delay_ms(5);
    enablePulseLCD();
    
    //send low byte to LCD
    RS = HI;
    ptr->D7L = (data & 0x08)>>3;
    ptr->D6H = (data & 0x04)>>2;
    ptr->D5H = (data & 0x02)>>1;
    ptr->D4H = (data & 0x01);
    __delay_ms(5);
    enablePulseLCD();
    
    
}
