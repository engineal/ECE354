#include "hello_led.h"
#include "basic_io.h"
#include "custom_io.h"
#include "LCD.h"
#include "image.h"
#include "net/udp.h"
#include "net/ethernet.h"
#include "interpretCommand.h"

#define LOCAL_MAC {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF}
#define LOCAL_IP_ADDR {192, 168, 1, 116}
#define LOCAL_PORT 1115

#define DEST_MAC {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF}
#define DEST_IP_ADDR {192, 168, 1, 116}
#define DEST_PORT 1115

UDPInfo* ethInfo;

char bin_pix[X][Y];

int main(void)
{
    // Default Ethernet settings.
    UDPInfo i;   
    char localIP[] = LOCAL_IP_ADDR; 
    char localMAC[] = LOCAL_MAC;
    char destIP[] = DEST_IP_ADDR;
    char destMAC[] = DEST_MAC;
    i.localIP = localIP;
    i.localMAC = localMAC;
    i.localPort = LOCAL_PORT;    
    i.destIP = destIP;
    i.destMAC = destMAC;
    i.destPort = DEST_PORT;
    ethInfo = &i;
    
    LCD_Test();
    ethernetInit(ethInfo->localMAC);
    init_vga();
    
    writeLEDs(0);
    
    int oldValue = 0;
    unsigned char data[1024];
    
    while (1)
    {
        // -- SEND --
        int value = readButtons();
        if (oldValue != value && value == 8) 
        {
            int switches = readSwitches();
            if (switches >= 0x0 && switches < 0x9)
            {
                char data[] = {switches};
                printf("Sending %d\n", switches);
                udpSend(data, 1, ethInfo);
            }   
        }
        oldValue = value;
        
        // send queued packets
        ethernet_worker();
        
        // -- RECEIVE --
        int size = udpReceive(data, ethInfo);
        if (size > 0) {
            // If size = 1, it must be a commanding message
            if (size == 1) {
                printf("Interpreting Command...\n");
                
                if (data[0] < 0x09)
                    writeLEDs(data[0]);
                else if (data[0] == MSG_ACK)
                    writeGreenLEDs(0xFF);
                else if (data[0] == MSG_NAK)
                    writeLEDs(0x3FFFF);
                interpretCommand(data[0]);
            }
        }
        
        msleep(100);
        writeLEDs(0);
        writeGreenLEDs(0);
    }

    return 0;
}

//-------------------------------------------------------------------------

