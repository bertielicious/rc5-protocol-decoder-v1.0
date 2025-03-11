#include "constVar.h"
void enablePulseLCD(void)
{
    EN = 1;
    __delay_us(500);
    EN = 0;
    __delay_us(500);
}
