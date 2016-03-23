#include "ethernet.h"

// creates and transmits packet
void encode_message(
    char* data, 
    int valueSize, 
    int port, 
    int destPort, 
    char* destIP, 
    char* ip_addr,   
    char* destMAC, 
    char* ether_addr) 
{
    printf("Sent: %s\n", data);
    
    UDPFrame udpFrame;
    //char data[] = {value>>8, value, value>>16};
    fillUDPHeader(&udpFrame, port, destPort, data, valueSize); //fills IP header with default values
    //printUDPHeader(&udpFrame);
    unsigned char UDPData[UDP_HEADER_LENGTH + valueSize];
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
int decode_message(
    char* data, 
    int dataLength, 
    char* returnedData, 
    int port, 
    char* ip_addr, 
    char* ether_addr) 
{
    printf("Received %d bytes:\n", dataLength);
    
    int bufferSize = -1;
    
    ethernetFrame ethFrame;
    ethFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(dataLength - ETHERNET_HEADER_LENGTH));
    if (ethUnpack(data, dataLength, &ethFrame, ether_addr)) {
        //printEthernetHeader(&ethFrame);
        
        IPFrame ipFrame;
        ipFrame.data = (unsigned char*) malloc(sizeof(unsigned char)*(ethFrame.dataLength - IP_HEADER_LENGTH));
        if (IPUnpack(ethFrame.data, &ipFrame, ip_addr)) {
            //printIPHeader(&ipFrame);
            
            UDPFrame udpFrame;
            bufferSize = ipFrame.dataLength - UDP_HEADER_LENGTH;
            udpFrame.data = returnedData;//(unsigned char*) malloc(sizeof(unsigned char)*(bufferSize));
            if (UDPUnpack(ipFrame.data, &udpFrame, port)) {
                //printUDPHeader(&udpFrame);
                //unsigned int rx_val = (udpFrame.data[0]<<8) | udpFrame.data[1] | (udpFrame.data[2]<<16);
                //printf("%x\n\n", rx_val);
                //writeLEDs(rx_val);
                //interpretCommand(udpFrame.data[0]);                             
            }
            //free(udpFrame.data);
        }
        free(ipFrame.data);
    }
    free(ethFrame.data);
    return bufferSize;
}
