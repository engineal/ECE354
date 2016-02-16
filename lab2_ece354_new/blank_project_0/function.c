#include "my_includes.h"
#include "CAMERA_NIOS2_COMMAND.H"
#include "function.h"
#include "packet.h"
#include "CAMERA_HAL.h"
#include "vga.h"

#ifdef DEBUG_APP
    #define APP_DEBUG(x)    DEBUG(x)  
#else
    #define APP_DEBUG(x)
#endif

//  internal function prototype
void report_result(char *pTitle, bool bSuccess, alt_u32 start_time);
bool video_config(void);
bool memory_read(alt_u8 mem_type, alt_u32 offset, PKLEN_TYPE read_len, alt_u8 szBuf[]);
bool memory_write(alt_u8 mem_type, alt_u32 offset, PKLEN_TYPE write_len, alt_u8 szData[]);
//





////////////////////////////////////////////////////////////////////////
///////////////////// CAMERA CAPTURE ///////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool camera_capture(void){
    bool bSuccess = TRUE;
    CAMERA_CAPTURE_START();
    usleep(500*1000);
    CAMERA_CAPTURE_STOP();
    
    return bSuccess;    
}




////////////////////////////////////////////////////////////////////////
///////////////////// PORT READ ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void camera_port_read(alt_u8 *pBuf, alt_u32 num){
    alt_u32 i;
    alt_u32 data;
    char bin_pix[640*480];
    alt_flash_fd* fd;
    unsigned int offset = 0x10;
    fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
    if (fd==NULL)
    {
        printf("Flash memory open failure\n");
        return;
    }
    unsigned int j;
    unsigned int pix_idx;
    alt_erase_flash_block(fd,offset,640*480);
    j = 0;
    pix_idx = 0;
    for(i=0;i<num;i++)
    {
        if(((i%640) == 0) && i != 0) 
        {
            printf("i : %d\n",i);
            j++;
        }
//        if((i != 0) && ((i%(640*2)) == 0))
//        {              
//        }
        data = CAMERA_READ();
        bin_pix[i] = data;
       // continue with the code here
       
    }
}





