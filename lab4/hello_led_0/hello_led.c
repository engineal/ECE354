#include "basic_io.h"
#include "hello_led.h"
#include "test.h"
#include "LCD.h"
#include "DM9000A.C"
#include "helper.h"
#include "ethernet_layer.h"
#include "IP_layer.h"
#include "UDP_layer.h"
#include "sys/alt_flash.h"
#include "sys/alt_flash_types.h"

unsigned char RXT[68];
int packet_num;

//ether_addr = {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF}; // Set MAC address with our group id as the last byte
unsigned char ip_addr[] = {192, 168, 1, 116};
unsigned int port = 1115;

unsigned char destMAC[] = {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF};
unsigned char destIP[] = {192, 168, 1, 115};
unsigned int destPort = 1114;

#define X 640
#define Y 480

char bin_pix[X][Y];

// run everytime an ethernet interrupt is generated
void ethernet_interrupts()
{
    static int lc = 0;
    printf("lc = %d\n", lc++);
    
    packet_num++;
    int rx_len = 0;
    int aaa=ReceivePacket(RXT,&rx_len);
    if(!aaa)
    {
        printf("Receive Packet Length = %d\n",rx_len);
        int i;
        for(i=0;i<rx_len;i++)
        {
            if(i%8==0)
                printf("\n");
            printf("0x%2X,",RXT[i]);
        }
        printf("\n\n");
        decode_message(RXT, rx_len);
    }
    
    writeDecimalLCD(packet_num);
}

int main(void)
{
    LCD_Test();
    DM9000_init();
    //alt_irq_register(DM9000A_IRQ, NULL, (void*)ethernet_interrupts);
    
    packet_num=0;
    writeDecimalLCD(packet_num);
    writeLEDs(0);
    
    int oldValue = 0;
    while (1)
    {
        // -- SEND --
        int value = readSwitches();
        if (oldValue != value) {
            encode_message(value);
            oldValue = value;
        }
        
        msleep(100);
    }

    return 0;
}

// creates and transmits packet
void encode_message(int value) {
    printf("Sent: %d\n", value);
    
    UDPFrame udpFrame;
    char data[] = {value>>8, value, value>>16};
    fillUDPHeader(&udpFrame, port, destPort, data, 3); //fills IP header with default values
    //printUDPHeader(&udpFrame);
    unsigned char UDPData[UDP_HEADER_LENGTH + 3];
    int UDPLength = UDPPack(&udpFrame, UDPData);
    
    IPFrame ipFrame;
    fillIPHeader(&ipFrame, 4, 1, ip_addr, destIP, UDPData, UDPLength); //fills IP header with default values
    //printIPHeader(&ipFrame);
    unsigned char IPData[IP_HEADER_LENGTH + UDPLength];
    int IPLength = IPPack(&ipFrame, IPData);
    
    ethernetFrame ethFrame;
    fillEthernetHeader(&ethFrame, destMAC, ether_addr, IPData, IPLength);
    //printEthernetHeader(&ethFrame);
    unsigned char ethernetData[ETHERNET_HEADER_LENGTH + IPLength];
    int ethernetLength = ethPack(&ethFrame, ethernetData);
    
    TransmitPacket(ethernetData, ethernetLength);
}

// receives and decodes packet
void decode_message(char* data, int dataLength) {
    printf("Received %d bytes:\n", dataLength);
    
    ethernetFrame ethFrame;
    ethFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(dataLength - ETHERNET_HEADER_LENGTH));
    if (ethUnpack(data, dataLength, &ethFrame, ether_addr)) {
        //printEthernetHeader(&ethFrame);
        
        IPFrame ipFrame;
        ipFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(ethFrame.dataLength - IP_HEADER_LENGTH));
        if (IPUnpack(ethFrame.data, &ipFrame, ip_addr)) {
            //printIPHeader(&ipFrame);
            
            UDPFrame udpFrame;
            udpFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(ipFrame.dataLength - UDP_HEADER_LENGTH));
            if (UDPUnpack(ipFrame.data, &udpFrame, port)) {
                //printUDPHeader(&udpFrame);
                
                interpretCommand(udpFrame.data[0]);
            }
            free(udpFrame.data);
        }
        free(ipFrame.data);
    }
    free(ethFrame.data);
}

void interpretCommand(alt_u32 command) {
    writeLEDs(command);
    switch (command) {
        //ACK
        case 0xAA:
            break;
        //NAK
        case 0xFF:
            break;
        //Get image from flash
        case 0:
            readFlash(bin_pix);
            break;
        //Transmit image
        case 1:
            break;
        //Flip
        case 2:
            imageFlip(bin_pix);
            break;
        //Invert
        case 3:
            imageInvert(bin_pix);
            break;
        //Rotate
        case 4:
            imageRotate(bin_pix);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

int readSwitches()
{
    return inport(SWITCH_PIO_BASE);
}

void writeLEDs(int value)
{
    outport(LED_RED_BASE,value);
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

void readFlash(char image[][Y]) {
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
    int i, j;
    for(i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            alt_read_flash(fd,offset++,&bin_pix,1);
            image[i][j] = bin_pix;
        }
    }
    alt_flash_close_dev(CFI_FLASH_0_NAME);
}


void imageFlip(char image[][Y]) {
    char cpy[X][Y];
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            cpy[X - i][j] = image[i][j];
        }
    }
    
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            image[i][j] = cpy[i][j];
        }
    }
}

void imageInvert(char image[][Y]) {
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            image[i][j] = !image[i][j];
        }
    }
}

void imageRotate(char image[][Y]) {
    char cpy[X][Y];
    int i, j;
    for(i = 0; i < X; i++) {
        for(j = 0; j < Y; j++) {
            if (i > 80 && i < 560) {
                cpy[i][j] = image[j][i];
            } else {
                cpy[i][j] = 0;
            }
        }
    }
    
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            image[i][j] = cpy[i][j];
        }
    }
}
//-------------------------------------------------------------------------

