#include "ethernet.h"
#include "basic_io.h"
#include "DM9000A.C"
#include "layers/ethernet_layer.h"

volatile int ackReceived;

void ethernetInit(char localMAC[]) {
    DM9000_init(localMAC);
}

void ethernetSend(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame frame;
    fillEthernetHeader(&frame, destMAC, localMAC, data, length);
    //printEthernetHeader(&frame);
    unsigned char ethernetData[ETHERNET_HEADER_LENGTH + length];
    int ethernetLength = ethPack(&frame, ethernetData);
    
    ackReceived = 0;
    while (!ackReceived) {
        TransmitPacket(ethernetData, ethernetLength);
        
        msleep(1000);
    }
}

void ethernetSendNoACK(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame frame;
    fillEthernetHeader(&frame, destMAC, localMAC, data, length);
    //printEthernetHeader(&frame);
    unsigned char ethernetData[ETHERNET_HEADER_LENGTH + length];
    int ethernetLength = ethPack(&frame, ethernetData);
    
    TransmitPacket(ethernetData, ethernetLength);
}

int compareMAC(char* mac1, char* mac2) {
    int macPass = 1;
    int i;
    for (i = 0; i < 6; i++) {
        macPass &= mac1[i] == mac2[i];
    }
    return macPass;
}

int ethernetReceive(
    char* returnedData, 
    char* localMAC)
{
    unsigned char data[68];
    int dataLength = 0;
    int aaa=ReceivePacket(data,&dataLength);
    if (!aaa) {
        ethernetFrame frame;
        frame.data = returnedData;
        ethUnpack(data, dataLength, &frame);
        
        int checksum = 0; //computeChecksum(data, ETHERNET_HEADER_LENGTH);
        
        if (frame.checksum != checksum) {
            printf("Ethernet Checksum fail: %x != %x\n", frame.checksum, checksum);
        } else if (!compareMAC(frame.dest_addr, localMAC)) {
            printf("MAC fail: %2x:%2x:%2x:%2x:%2x:%2x != %2x:%2x:%2x:%2x:%2x:%2x\n",
                frame.dest_addr[0], frame.dest_addr[1], frame.dest_addr[2], frame.dest_addr[3], frame.dest_addr[4], frame.dest_addr[5],
                localMAC[0], localMAC[1], localMAC[2], localMAC[3], localMAC[4], localMAC[5]);
        } else {
            //printEthernetHeader(&frame);
            if (frame.data[0] == 0xF0) {
                ackReceived++;
            } else {
                char ackData[] = {0xF0};
                ethernetSendNoACK(ackData, 1, frame.src_addr, localMAC);
                return frame.dataLength;
            }
        }
    }
    return -1;
}
