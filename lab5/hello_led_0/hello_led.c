#include "hello_led.h"
#include "basic_io.h"
#include "custom_io.h"
#include "LCD.h"
#include "image.h"
#include "helper.h"
#include "net/udp.h"
#include "net/ethernet.h"
#include "interpretCommand.h"
#include "rle.h"

int localPort = LOCAL_PORT;
char localIP[] = LOCAL_IP;
char localMAC[] = LOCAL_MAC;

int destPort = DEST_PORT;
char destIP[] = DEST_IP;
char destMAC[] = DEST_MAC;

int main(void)
{
    LCD_Test();
    ethernetInit(localMAC);
    init_vga();
    
    writeLEDs(0);
    
    int oldValue = 0;
    unsigned char pic_data[3*X*Y];
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
                udpSend(data, 1, destPort, localPort, destIP, localIP, destMAC);
            }
            oldValue = value;
        }
        
        // send queued packets
        ethernet_worker();
        
        // -- RECEIVE --
        unsigned char data[MAX_PAYLOAD_LENGTH];
        int size = udpReceive(data, localPort, localIP);
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
                        printf("MASTER: received %d packets, %d bytes\n", packetNum, bytesRec);
                        
                        char image[X][Y];
                        decompressImage(image, pic_data, bytesRec);
                        
                        printf("decompressed\n");
                        
                        // display image
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
                charncat(pic_data, data, &bytesRec, size); // get data necessary to build your image
                packetNum++;
            }
        }
        msleep(50);
    }

    return 0;
}
