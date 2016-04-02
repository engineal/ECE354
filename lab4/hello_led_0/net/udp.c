#include "udp.h"
#include "basic_io.h"

// creates and transmits packet
void udpSend(
    char* data, 
    int length, 
    UDPInfo* info) 
{
    UDPFrame frame;
    fillUDPHeader(&frame, info->localPort, info->destPort, data, length);
    //printUDPHeader(&frame);
    unsigned char output[UDP_HEADER_LENGTH + length];
    int outputLength = UDPPack(&frame, output);
    
    ipSend(output, outputLength, info->destIP, info->localIP, info->destMAC, info->localMAC);
}

// receives and decodes packet
int udpReceive(
    char* returnedData, 
    UDPInfo* info) 
{
    unsigned char data[UDP_LENGTH];
    int dataLength = ipReceive(data, info->localIP, info->localMAC);
    if (dataLength > 0) {
        UDPFrame frame;
        frame.data = returnedData;
        UDPUnpack(data, &frame);

        int checksum = 0; //computeChecksum(data, UDP_HEADER_LENGTH);

        if (frame.checksum != checksum) {
            printf("UDP Checksum fail: %x != %x\n", frame.checksum, checksum);
        } else if (frame.destPort != info->localPort) {
            printf("Port fail: %d != %d\n", frame.destPort, info->localPort);
        } else {
            //printUDPHeader(&frame);
            return frame.dataLength;
        }
    }
    return -1;
}
