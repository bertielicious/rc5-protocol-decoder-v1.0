#include "constVar.h"
#include "enablePulseLCD.h"
/* send 0x8X for line 1 text
   send 0xCX for line 2 text*/
void lcdCommand(uint8_t command)
{
    //write high nibble 0x80
    RS = LO;
    D7 = (command & 0b10000000)>>7;
    D6 = (command & 0b01000000)>>6;// if first line, HI if second line of display
    D5 = (command & 0b00100000)>>5;
    D4 =(command & 0b00010000)>>4;
     __delay_us(1000);
     enablePulseLCD();

   /* printf("high Nibble\n");
    printf("D7 %d\n", D7);
    printf("D6 %d\n", D6);
    printf("D5 %d\n", D5);
    printf("D4 %d\n", D4);*/
     
     
     //write position to start writing on the LCD screen
    D7 = (command & 0b00001000)>>3;
    D6 = (command & 0b00000100)>>2;
    D5 = (command & 0b00000010)>>1;
    D4 = (command & 0b00000001);
     __delay_us(1000);
     enablePulseLCD();

    /*printf("low Nibble\n");
    printf("D7 %d\n", D7);
    printf("D6 %d\n", D6);
    printf("D5 %d\n", D5);
    printf("D4 %d\n", D4);*/

}
