#include "hello_led.h"
#include "basic_io.h"
#include "LCD.h"
#include "image.h"
#include "net/udp.h"
#include "net/ethernet.h"
#include "interpretCommand.h"

int packet_num;

#define LOCAL_MAC {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF}
#define LOCAL_IP_ADDR {192, 168, 1, 116}
#define LOCAL_PORT 1115

#define DEST_MAC {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF}
#define DEST_IP_ADDR {192, 168, 1, 116}
#define DEST_PORT 1115

UDPInfo* ethInfo;

char bin_pix[X][Y];

// run everytime an ethernet interrupt is generated
void ethernet_interrupts()
{
    packet_num++;
    unsigned char data[1024];
    int size = udpReceive(data, ethInfo);
    if (size > 0) {
        // If size = 1, it must be a commanding message
        if (size == 1) {
            printf("Interpreting Command...\n");
            
            if (data[0] < 0x09)
                writeLEDs(data[0]);
            else if (data[0] == 0xAA || data[0] == 0xFF)
                writeGreenLEDs(0xFF);
            interpretCommand(data[0]);
        }
    }
    
    writeDecimalLCD(packet_num);
}

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
    alt_irq_register(DM9000A_IRQ, NULL, (void*)ethernet_interrupts);
    
    packet_num=0;
    writeDecimalLCD(packet_num);
    writeLEDs(0);
    
    int oldValue = 0x0F;
    
    while (1)
    {
        // -- SEND --
        int value = readButtons();
        if (oldValue != value && value != 0) 
        {
            printf("Buttons: %x\n", value);
            int switches = readSwitches();
            
            if (switches >= 0x0 && switches < 0x9)
            {
                char data[] = {switches};
                printf("Sending %d\n", switches);
                udpSend(data, 1, ethInfo);
            }   
        }
        
        oldValue = value;
        
        msleep(100);
    }

    return 0;
}

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
//-------------------------------------------------------------------------

