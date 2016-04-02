#include "interpretCommand.h"
#include "basic_io.h"
#include "image.h"
#include "net/udp.h"

extern UDPInfo* ethInfo;

static void sendACK()
{
    char data[] = {MSG_ACK};
    udpSend(data, 1, ethInfo);
}

static void sendNAK()
{
    char data[] = {MSG_NAK};
    udpSend(data, 1, ethInfo);
}

extern char bin_pix[X][Y];
void interpretCommand(int command) 
{    
    switch (command) 
    {
        //ACK
        case MSG_ACK:
            printf(" -- Recieved Ack Message\n");
            break;
        //NAK
        case MSG_NAK:
            printf(" -- Recieved Nak Message\n");
            break;
        //Get image from flash
        case MSG_GET_IMAGE:
            printf(" -- Recieved Get Image From Flash Message\n");
            readFlash(bin_pix);
            sendACK();
            break;
        //Transmit image
        case MSG_TRANSMIT_IMAGE:
            printf(" -- Recieved Transmit Image Message\n");
            break;
        //Flip
        case MSG_IMAGE_PROC_1:
            printf(" -- Recieved Flip Image Message\n");
            imageFlip(bin_pix);
            sendACK();
            break;
        //Invert
        case MSG_IMAGE_PROC_2:
            printf(" -- Recieved Invert Image Message\n");
            imageInvert(bin_pix);
            sendACK();
            break;
        //Rotate
        case MSG_IMAGE_PROC_3:
            printf(" -- Recieved Rotate Image Message\n");
            imageRotate(bin_pix);
            sendACK();
            break;
        case MSG_IMAGE_PROC_4:
            sendNAK();
            break;
        case MSG_IMAGE_PROC_5:
            sendNAK();
            break;
        case MSG_IMAGE_PROC_6:
            sendNAK();
            break;
        default:
            sendNAK();
            break;
    }
    printf("\n");
}
