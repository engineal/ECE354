#include "udp.h"
#include "ip.h"
#include "basic_io.h"
#include "layers/udp_layer.h"

// creates and transmits packet
int udpSend(
    char* data, 
    int length, 
    UDPInfo* info) 
{
    UDPFrame udpFrame;
    fillUDPHeader(&udpFrame, info->localPort, info->destPort, data, length);
    //printUDPHeader(&udpFrame);
    unsigned char UDPData[UDP_HEADER_LENGTH + length];
    int UDPLength = UDPPack(&udpFrame, UDPData);
    
    return ipSend(UDPData, UDPLength, info->destIP, info->localIP, info->destMAC, info->localMAC);
}

// receives and decodes packet
int udpReceive(
    char* returnedData, 
    UDPInfo* info) 
{
    unsigned char data[68];
    int dataLength = ipReceive(data, info->localIP, info->localMAC);
    if (dataLength > 0) {
        UDPFrame udpFrame;
        udpFrame.data = returnedData;
        if (UDPUnpack(data, &udpFrame, info->localPort)) {
            //printUDPHeader(&udpFrame);
            return udpFrame.dataLength;
        }
    }
    return -1;
}
