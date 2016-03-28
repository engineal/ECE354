#include "custom_io.h"
#include "basic_io.h"

int readSwitches()
{
    return inport(SWITCH_PIO_BASE);
}

int readButtons()
{
    return inport(BUTTON_PIO_BASE);
}

void writeLEDs(int value)
{
    outport(LED_RED_BASE,value);
}
void writeGreenLEDs(int value)
{
    outport(LED_GREEN_BASE, value);
}

void writeDecimalLCD(int value)
{
    int digits=0;
    
    int i;
    for(i=0; i<8; i++)
    {
        digits |= (value % 10)<<(i*4);
        value = value/10;   
    }
    
    outport(SEG7_DISPLAY_BASE,digits);
}