
#include "basic_io.h"
#include "hello_led.h"
#include "test.h"
#include "LCD.h"
#include "DM9000A.C"
#include "helper.h"
#include "ethernet_layer.h"
#include "IP_layer.h"

unsigned int aaa,rx_len,i,packet_num;
unsigned char RXT[68];
unsigned char TXT[41]; //21 for only ethernet frame

// run everytime an ethernet interrupt is generated
void ethernet_interrupts()
{
    packet_num++;
    aaa=ReceivePacket(RXT,&rx_len);
    if(!aaa)
    {
        printf("\nReceive Packet Length = %d\n",rx_len);
        /*for(i=0;i<rx_len;i++)
        {
            if(i%8==0)
            printf("\n");
            printf("0x%2X,",RXT[i]);
        }*/
        decode_message();
    }
    outport(SEG7_DISPLAY_BASE,packet_num);
}

int main(void)
{
    LCD_Test();
    //ether_addr = {0x01, 0x60, 0x6E, 0x11, 0x02, 0xFF}; // Set MAC address with our group id as the last byte
    DM9000_init();
    alt_irq_register(DM9000A_IRQ, NULL, (void*)ethernet_interrupts);
  
    packet_num=0;
  
    while (1)
    {
        int value = readSwitches();
        encode_message(value);
        msleep(500);
    }

    return 0;
}

// creates and transmits packet
void encode_message(int value) {
    IPFrame ipFrame;
    fillIPHeader(&ipFrame); //fills IP header with default values
    ipFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*3);
    ipFrame.data[0] = (value>>16)&0xFF;
    ipFrame.data[1] = (value>>8)&0xFF;
    ipFrame.data[2] = value&0xFF;
    
    unsigned char temp[23];
    IPPack(&ipFrame, temp);
    
    ethernetFrame ethFrame;
    charncpy(ethFrame.dest_addr, ether_addr, 6);
    charncpy(ethFrame.src_addr, ether_addr, 6);
    ethFrame.type[0] = 0x08;
    ethFrame.type[1] = 0x00;
    ethFrame.data = temp;
    
    /*ethFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*3);
    ethFrame.data[0] = (value>>16)&0xFF;
    ethFrame.data[1] = (value>>8)&0xFF;
    ethFrame.data[2] = value&0xFF;
    ethFrame.dataLength = 3;*/
    
    int len = ethPack(&ethFrame, TXT);
    TransmitPacket(TXT, len);
    
    free(ipFrame.data);
    free(temp);
    //free(ethFrame.data);
}

// receives and decodes packet
void decode_message() {
    ethernetFrame recEthFrame;
    recEthFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(rx_len - 18));
    ethUnpack(RXT, rx_len, &recEthFrame);
    
    //check mac address, IP, port address before you do this
    IPFrame recIPFrame;
    recIPFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(rx_len - 18 - 20));
    IPUnpack(recEthFrame.data, rx_len, &recIPFrame);
    
    unsigned int rx_val = (recIPFrame.data[0]<<16) | (recIPFrame.data[1]<<8) | recIPFrame.data[2];
    writeLEDs(rx_val);
    
    free(recEthFrame.data);
    free(recIPFrame.data);
}

int readSwitches()
{
    return inport(SWITCH_PIO_BASE);
}

void writeLEDs(int value)
{
    outport(LED_RED_BASE,value);
}


//-------------------------------------------------------------------------


