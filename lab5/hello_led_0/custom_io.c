#include "custom_io.h"
#include "basic_io.h"
#include "VGA.C"
#include "image.h"

int readSwitches()
{
    return inport(SWITCH_PIO_BASE);
}

int readButtons()
{
    return 0xF - inport(BUTTON_PIO_BASE);
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

void init_vga() {
    VGA_Ctrl_Reg vga_ctrl_set;
  
    vga_ctrl_set.VGA_Ctrl_Flags.RED_ON    = 1;
    vga_ctrl_set.VGA_Ctrl_Flags.GREEN_ON  = 1;
    vga_ctrl_set.VGA_Ctrl_Flags.BLUE_ON   = 1;
    vga_ctrl_set.VGA_Ctrl_Flags.CURSOR_ON = 0;
  
    Vga_Write_Ctrl(VGA_0_BASE, vga_ctrl_set.Value);
    Set_Pixel_On_Color(179<<2,139<<2,109<<2);
    Set_Pixel_Off_Color(0,0,0);
    //Set_Cursor_Color(0,1023,0);
    
    int i,j;
    for(i = 0; i < X; i++) {
        for(j = 0; j < Y; j++) {
            if((i % 8) == 0)Vga_Set_Pixel(VGA_0_BASE,i,j);
            else Vga_Clr_Pixel(VGA_0_BASE,i,j);
        }
    }
}

void write_vga(char image[][Y]) {
    int i, j;
    for(i = 0; i < X; i++) {
        for(j = 0; j < Y; j++) {
            if(!image[i][j])Vga_Set_Pixel(VGA_0_BASE,i,j);
            else Vga_Clr_Pixel(VGA_0_BASE,i,j);
        }
    }
}