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
  vga_ctrl_set.VGA_Ctrl_Flags.CURSOR_ON = 1;
  
  Vga_Write_Ctrl(VGA_0_BASE, vga_ctrl_set.Value);
  Set_Pixel_On_Color(1023,1023,1023);
  Set_Pixel_Off_Color(0,0,0);
  Set_Cursor_Color(0,1023,0);

   unsigned int i,j;
   for(i = 0 ; i < 480 ; i++)
   {
        for(j = 0 ; j < 640 ; j++)
        {
            if((j % 8) == 0)Vga_Set_Pixel(VGA_0_BASE,j,i);
            else Vga_Clr_Pixel(VGA_0_BASE,j,i);
        }
   }

//  w16(HcReset,0x00F6);//reset      
//  reset_usb();//config  
//  mouse();


//    szPacket = malloc(PKT_NIOS2PC_MAX_LEN);
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

    while(1)
    {
//        char cmd[2];
        short cmd;
        scanf("%d",&cmd);
//        gets(cmd);
        printf("Command : %d \n", cmd);
        switch(cmd)
        {
           case 0:
                {
                    camera_capture();
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
                    alt_flash_fd* fd;
                    unsigned int offset = 0x10;
                    char bin_pix;
                    fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
                    if (fd==NULL) 
                    {
                        printf("Flash memory open failure\n");
                        return;
                    }
                    
                  printf("Reading binary pixel from flash memory\n");
                       for(i = 0 ; i < 480 ; i++)
                       {
                          for(j = 0 ; j < 640 ; j++)
                            {
                                alt_read_flash(fd,offset,&bin_pix,1);
                                if(!bin_pix)Vga_Set_Pixel(VGA_0_BASE,j,i);
                                else Vga_Clr_Pixel(VGA_0_BASE,j,i);
                                offset++;
                            }
                       }
                       printf("... Done\n");
                    alt_flash_close_dev(CFI_FLASH_0_NAME);                    
                    
                }
        }
    }
 /*
     while(1){
 //           if (!read_packet(szPacket))
//                continue;
                char cmd[2];
                gets(cmd);
                printf(" %d %d\n", cmd[0]-48, cmd[1]-48);
              szPacket[PKT_HEADER_INDEX] = cmd[0] -48;
              szPacket[PKT_OP_INDEX] = cmd[1] -48;
              szPacket[PKT_LEN_INDEX] = 0;
              
            bool bResponse = TRUE, bSuccess = FALSE;
            time_start = alt_nticks();
            alt_u8 OP = szPacket[PKT_OP_INDEX];
            dump_op_name(OP);
            switch(OP){
                case OP_POLLING:
                    bSuccess = op_polling(szPacket); // ack
                    break;
                case OP_CAMERA_CONFIG:
                    bSuccess = op_camera_config(szPacket);
                    break;                    
                case OP_CAMERA_CAPTURE:
                    bSuccess = op_camera_capture(szPacket);
                    break;                    
                case OP_CAMERA_PORT_READ:
                    bSuccess = op_camera_port_read(szPacket);
                    break;                                                                                                                                                                                                     
                case OP_MEMORY_READ:
                    bSuccess = op_memory_read(szPacket);
                    break;    
                case OP_MEMORY_WRITE:
                    bSuccess = op_memory_write(szPacket);
                    break;   
                default:    
                    bResponse = FALSE;
                    break; 
            }  // end of switch
            if (bResponse){  // report result to PC
                alt_u32 time_elapsed;
                PKLEN_TYPE pl_len;
                alt_u32 pk_len;
                memcpy(&pl_len, &szPacket[PKT_LEN_INDEX], sizeof(pl_len));  // payload len
                pk_len = pl_len + PKT_NONEPL_SIZE;
                if (pk_len > PKT_NIOS2PC_MAX_LEN){ 
                    printf(("response packet len too long\r\n"));
                }else{
                    printf("JTAGUART_Write (len=%d)...\r\n", pk_len);    
//                    if (!JTAGUART_Write(szPacket, pk_len)){
 //                       printf("send packet fail, len=%d\r\n", pk_len);
 //                   }    
                        
                }                    
                time_elapsed = alt_nticks() - time_start;
                printf("\r\n%s(OP=%d, %d ms)\r\n", bSuccess?"ok":"ng", OP,  (int)(1000*time_elapsed/ticks_per_sec));    
                //JTAGUART_ClearInput();            
             }  // if response
                        
        
    }  // while(1)
*/
  return 0;
}
