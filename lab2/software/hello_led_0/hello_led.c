// It is not necessary that you follow the below coding format. It is just given as the sample way to start the project.
//The functions declared in main functions are declared in file function.c
// Again some start up code is given in function.c 
#include "my_includes.h"
#include "system.h"
#include "basic_io.h"
#include "LCD.h"
#include "sys/alt_irq.h"
#include "VGA.C"
#include "HAL4D13.C"
#include "isa290.h"
#include "reg.h"
#include "buf_man.h"
#include "port.h"
#include "usb.h"
#include "ptd.h"
#include "cheeyu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include "cheeyu.c"
#include "ptd.c"
#include "usb.c"
#include "buf_man.c"
#include "reg.c"
#include "port.c"
#include <sys/times.h>

#include "packet.h"
#include "function.h"
//#include "JtagUart.h"

unsigned int		hc_data;
unsigned int		hc_com;
unsigned int		dc_data;
unsigned int		dc_com;


void init(void)
{
    printf(("\r\n===== DE2 Camera Utility [05/31/2011] =====\r\n"));

    if (LCD_Open())
    {
        LCD_TextOut("Welcome DE2 \nD5M Test\n");
    }
    else
    {
        printf(("[LCD] open fail\r\n"));
    } 
}

void writeTimestamp(int timestamp, int topleftX, int topleftY);

int main(void)
{
    alt_u32 time_start, ticks_per_sec;
    alt_u8 *szPacket; 
    printf("Application starts\n");
    init();
    
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
    for(i = 0 ; i < 480 ; i++)
    {
        for(j = 0 ; j < 640 ; j++)
        {
            if((j % 8) == 0)Vga_Set_Pixel(VGA_0_BASE,j,i);
            else Vga_Clr_Pixel(VGA_0_BASE,j,i);
        }
    }

    // w16(HcReset,0x00F6);//reset      
    // reset_usb();//config  
    // mouse();

    // szPacket = malloc(PKT_NIOS2PC_MAX_LEN);
    szPacket = malloc(16*1024);
    if (!szPacket)
    {
        printf(("malloc fail, program is terminated!\r\n"));
        return 0;
    }
    else
    {
       printf("malloc for (16K bytes) packet buffer success.\n");
    }    
 
    ticks_per_sec = alt_ticks_per_second();
    alt_u8 * pData;
    pData = (volatile alt_u8 *) CFI_FLASH_0_BASE;
    int imageTimeStamp = 0;
    int imageCounter = 0;
    
    while(1)
    {
        int cmd;
        scanf("%d",&cmd);

        printf("Command : %d \n", cmd);
        switch(cmd)
        {
            case 0:
            {
                printf("Capturing image from camera\n");
                camera_capture();
                printf("... Done\n");
                
                // The function "times()" returns how many clock ticks since reset.        
                struct tms buf; 
                imageTimeStamp = times(&buf) / ticks_per_sec;
                imageCounter++;
                break;
            }
            case 1:
            {
                printf("Copying RGB data from FIFO to Flash memory\n");
                camera_port_read(pData, 640*480);
                printf("... Done\n");
                break;
            }
            case 2:
            {
                printf("Normal\n");
                alt_flash_fd* fd;
                unsigned int offset = 0x10;
                char bin_pix;
                fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
                if (fd==NULL) 
                {
                    printf("Flash memory open failure\n");
                    return 0;
                }
                    
                printf("Reading binary pixel from flash memory\n");
                for(i = 0 ; i < 480 ; i++)
                {
                    for(j = 0 ; j < 640 ; j++)
                    {
                        alt_read_flash(fd,offset++,&bin_pix,1);
                        if(!bin_pix)Vga_Set_Pixel(VGA_0_BASE,j,i);
                        else Vga_Clr_Pixel(VGA_0_BASE,j,i);
                    }
                }               
                alt_flash_close_dev(CFI_FLASH_0_NAME);  
                writeTimestamp(imageTimeStamp, 20, 20); 
                writeTimestamp(imageCounter, 500, 20);
                printf("... Done\n");
                break;
            }
            case 3:
            {
                printf("Flip\n");
                alt_flash_fd* fd;
                unsigned int offset = 0x10;
                char bin_pix;
                fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
                if (fd==NULL) 
                {
                    printf("Flash memory open failure\n");
                    return 0;
                }
                
                printf("Reading binary pixel from flash memory\n");
                for(i = 0; i < 480; i++)
                {
                    for(j = 639 ; j >= 0 ; j--)
                    {
                        alt_read_flash(fd,offset++,&bin_pix,1);                        
                        if(!bin_pix)Vga_Set_Pixel(VGA_0_BASE,j,i);
                        else Vga_Clr_Pixel(VGA_0_BASE,j,i);
                    }
                }

                alt_flash_close_dev(CFI_FLASH_0_NAME);
                writeTimestamp(imageTimeStamp, 20, 20); 
                writeTimestamp(imageCounter, 500, 20);
                printf("... Done\n");
                break;
            }
            case 4:
            {
                printf("Invert color\n");
                alt_flash_fd* fd;
                unsigned int offset = 0x10;
                char bin_pix;
                fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
                if (fd==NULL) 
                {
                    printf("Flash memory open failure\n");
                    return 0;
                }
                    
                printf("Reading binary pixel from flash memory\n");
                for(i = 0 ; i < 480 ; i++)
                {
                    for(j = 0 ; j < 640 ; j++)
                    {
                        alt_read_flash(fd,offset++,&bin_pix,1);
                        if(bin_pix)Vga_Set_Pixel(VGA_0_BASE,j,i);
                        else Vga_Clr_Pixel(VGA_0_BASE,j,i);                                
                    }
                }               
                alt_flash_close_dev(CFI_FLASH_0_NAME);  
                writeTimestamp(imageTimeStamp, 20, 20); 
                writeTimestamp(imageCounter, 500, 20);
                printf("... Done\n");
                break;
            }
            case 5:
            {
                printf("Rotate\n");
                alt_flash_fd* fd;
                unsigned int offset = 0x10+80;
                char bin_pix;
                fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
                if (fd==NULL) 
                {
                    printf("Flash memory open failure\n");
                    return 0;
                }
                    
                printf("Reading binary pixel from flash memory\n");
                for(j = 0; j < 640; j++)
                {
                    for(i = 0; i < 480; i++)
                    {
                        if (j > 80 && j < 560) {
                            alt_read_flash(fd,offset++,&bin_pix,1);
                            if(!bin_pix)Vga_Set_Pixel(VGA_0_BASE,j,i);
                            else Vga_Clr_Pixel(VGA_0_BASE,j,i);
                        } else {
                            Vga_Clr_Pixel(VGA_0_BASE,j,i);
                        }
                    }
                    offset+=160;
                }               
                alt_flash_close_dev(CFI_FLASH_0_NAME);  
                writeTimestamp(imageTimeStamp, 20, 20); 
                writeTimestamp(imageCounter, 500, 20);
                printf("... Done\n");
                break;
            }
        }
    }   

  return 0;
}

void drawAscii(char letter, int topleftX, int topleftY);

void writeTimestamp(int timestamp, int topleftX, int topleftY)
{   
    long fontWidth = 8;
    long fontHeight = 13;
    long maxTimestampDigits = 8;
    long padding = 2;
    
    // Draw Black box where timestamp will be
    // Each piece of text is 13x8, max timestamp will be, say, 8 characters long
    int x, y;
    int startX = topleftX - padding;
    int endX = fontWidth*maxTimestampDigits + topleftX + padding;
    int startY = topleftY - padding;
    int endY = topleftY + fontHeight + padding;
    
    for (x = startX; x < endX; x++)
        for (y = startY; y < endY; y++)        
            Vga_Set_Pixel(VGA_0_BASE,x,y);    
    
    // Draw timestamps
    int lc = 0;
    while (lc < maxTimestampDigits)
    {
        // Get current least sig. digit.  
        int value = timestamp%10;      
       
        drawAscii('0'+value, 
            topleftX + (maxTimestampDigits-1-lc)*fontWidth, 
            topleftY);
            
        timestamp /= 10;
            
        lc++;
    }
}

void drawAscii(char letter, int topleftX, int topleftY)
{   
    // Found here: http://stackoverflow.com/questions/2156572/c-header-file-with-bitmapped-fonts/2156872#2156872
    unsigned char letters[95][13] = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// space :32
        {0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},// ! :33
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
        {0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
        {0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
        {0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
        {0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
        {0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
        {0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
        {0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
        {0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
        {0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c},
        {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
        {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
        {0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
        {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
        {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
        {0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06},
        {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
        {0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
        {0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
        {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
        {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
        {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
        {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
        {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
        {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
        {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
        {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
        {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
        {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
        {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
        {0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
        {0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
        {0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
        {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
        {0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
        {0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
        {0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
        {0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
        {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
        {0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
        {0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
        {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
        {0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
        {0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
        {0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
        {0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
        {0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
        {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
        {0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}};  // :126
    int arrayIndex = letter - 32; // Subtract 32 so that the index 0 is the same as ascii "32 (space)"
       
    int x, y;
    // How the huge array above works is that each the 13 horizontal lines for each ascii character 
    // Is represented by 8 bits.  Each of the 8 bits represent whether the x value for that row is 
    // on or off.
    for (y = 0; y < 13; y++)
    {
        char rowValues = letters[arrayIndex][y];
                       
        // Go through each bit in the current y-column.  
        for (x = 0; x < 8; x++)
        {
            // Determine if the pixel is on or not
            int pixelOn = (rowValues >> x) & 0x01;
                 
            // The array data is backwards in both x and y, so we need to flip them
            int pixX = (7-x) + topleftX;
            int pixY = (12-y) + topleftY;
            
            // Turn off the VGA pixel since the font color is black 
            // and the background color is white.
            if (pixelOn) Vga_Clr_Pixel(VGA_0_BASE,pixX,pixY);        
            else Vga_Set_Pixel(VGA_0_BASE,pixX,pixY);    
        }
    }
}
