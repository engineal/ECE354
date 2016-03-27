#include "ethernet.h"
#include "basic_io.h"
#include "DM9000A.C"
#include "layers/ethernet_layer.h"

volatile int ackReceived;

void ethernetInit(char localMAC[]) {
    DM9000_init(localMAC);
}

int ethernetSend(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ackReceived = 0;
    while (!ackReceived) {
        ethernetFrame ethFrame;
        fillEthernetHeader(&ethFrame, destMAC, localMAC, data, length);
        //printEthernetHeader(&ethFrame);
        unsigned char ethernetData[ETHERNET_HEADER_LENGTH + length];
        int ethernetLength = ethPack(&ethFrame, ethernetData);
        
        TransmitPacket(ethernetData, ethernetLength);
        
        msleep(1000);
    }
    
    return 1;
}

int ethernetSendNoACK(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame ethFrame;
    fillEthernetHeader(&ethFrame, destMAC, localMAC, data, length);
    //printEthernetHeader(&ethFrame);
    unsigned char ethernetData[ETHERNET_HEADER_LENGTH + length];
    int ethernetLength = ethPack(&ethFrame, ethernetData);
    
    TransmitPacket(ethernetData, ethernetLength);
    
    return 1;
}

int ethernetReceive(
    char* returnedData, 
    char* localMAC)
{
    unsigned char data[68];
    int dataLength = 0;
    int aaa=ReceivePacket(data,&dataLength);
    if (!aaa) {
        ethernetFrame ethFrame;
        ethFrame.data = returnedData;
        if (ethUnpack(data, dataLength, &ethFrame, localMAC)) {
            //printEthernetHeader(&ethFrame);
            if (ethFrame.data[0] == 0xF0) {
                ackReceived++;
            } else {
                char ackData[] = {0xF0};
                ethernetSendNoACK(ackData, 1, ethFrame.src_addr, localMAC);
                return ethFrame.dataLength;
            }
        }
    }
    return -1;
}
