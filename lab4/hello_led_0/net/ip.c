#include "ip.h"
#include "basic_io.h"
#include "helper.h"

void ipSend(
    char* data, int length,
    char* destIP, char* localIP,
    char* destMAC, char* localMAC)
{
    IPFrame frame;
    fillIPHeader(&frame, 4, 1, localIP, destIP, data, length);
    //printIPHeader(&frame);
    unsigned char output[IP_HEADER_LENGTH + length];
    int outputLength = IPPack(&frame, output);
    
    ethernetSend(output, outputLength, destMAC, localMAC);
}

int compareIP(char* ip1, char* ip2) {
    int ipPass = 1;
    int i;
    for (i = 0; i < 4; i++) {
        ipPass &= ip1[i] == ip2[i];
    }
    return ipPass;
}
    
int ipReceive(
    char* returnedData,
    char* localIP,
    char* localMAC)
{
    unsigned char data[IP_LENGTH];
    int dataLength = ethernetReceive(data, localMAC);
    if (dataLength > 0) {
        IPFrame frame;
        frame.data = returnedData;
        IPUnpack(data, &frame);
        
        int checksum = computeChecksum(data, IP_HEADER_LENGTH);
        
        if (frame.checksum != checksum) {
            printf("IP Checksum fail: %x != %x\n", frame.checksum, checksum);
        } else if (!compareIP(frame.dest_addr, localIP)) {
            printf("IP fail: %d.%d.%d.%d != %d.%d.%d.%d\n",
                frame.dest_addr[0], frame.dest_addr[1], frame.dest_addr[2], frame.dest_addr[3],
                localIP[0], localIP[1], localIP[2], localIP[3]);
        } else {
            //printIPHeader(&frame);
            return frame.dataLength;
        }
    }
    return -1;
}
