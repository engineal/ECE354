#include "hello_led.h"
#include "basic_io.h"
#include "custom_io.h"
#include "LCD.h"
#include "image.h"
#include "helper.h"
#include "net/udp.h"
#include "net/ethernet.h"
#include "interpretCommand.h"

UDPInfo* ethInfo;

int main(void)
{
    // Default Ethernet settings.
    UDPInfo i;   
    char localIP[] = LOCAL_IP;
    char localMAC[] = LOCAL_MAC;
    char destIP[] = DEST_IP;
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
    char image[X][Y];
    unsigned char data[MAX_PAYLOAD_LENGTH];
    unsigned char pic_data[X*Y/8];
    int packetNum = 0;
    int bytesRec = 0;
    char lastCommand=0x00; 
    
    while (1)
    {
        // -- SEND --
        int switches = readSwitches();
        int master = (switches >> 17) & 0x1;
        if (master || SINGLE) {
            int value = readButtons();
            if (oldValue != value && value == 8) 
            {
                char data[] = {switches & 0xF};
                lastCommand = data[0];
                printf("MASTER: Sending %d\n", data[0]);
                udpSend(data, 1, ethInfo);
            }
            oldValue = value;
        }
        
        // send queued packets
        ethernet_worker();
        
        // -- RECEIVE --
        int size = udpReceive(data, ethInfo);
        if (size > 0) 
        {
            // If size = 1, it must be a commanding message
            if (size == 1) 
            {
                if (data[0] == MSG_ACK)
                {
                    printf(" -- Recieved Ack Message\n\n");
                    writeGreenLEDs(0xFF);
                    if((master || SINGLE) && lastCommand==MSG_TRANSMIT_IMAGE)
                    {
                        //convert to 2d array
                        bitToChar(pic_data, image);
                        
                        //decompress
                        //decompress(image,displayImage); //"image" is a compressed version of the image.
                        
                        // display image
                        //write_vga(displayImage);
                        write_vga(image);
    
                        // reset variables
                        bytesRec = 0;
                        packetNum = 0;
                    }
                    msleep(500);
                    writeGreenLEDs(0);
                }
                else if (data[0] == MSG_NAK)
                {
                    printf(" -- Recieved Nak Message\n\n");
                    writeLEDs(0x3FFFF);
                    msleep(1000);
                    writeLEDs(0);
                }
                else if (!master || SINGLE) {
                    interpretCommand(data[0]);
                }
            } 
            else //this must be picture data from slave to master
            {
                printf("MASTER: packetNum: %d \n", packetNum);
                charncat(pic_data, data, &bytesRec, size); // get data necessary to build your image
                packetNum++;
            }
        }
        msleep(100);
    }

    return 0;
}
