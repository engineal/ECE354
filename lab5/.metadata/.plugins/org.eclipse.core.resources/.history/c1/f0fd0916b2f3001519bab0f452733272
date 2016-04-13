#ifndef UDP_H
#define UDP_H

typedef struct
{
    char* localIP;
    int localPort;
    char* localMAC;
    
    char* destIP;
    int destPort;
    char* destMAC;   
} EthernetInfo;


void udpSend(
    char* data, int valueSize, 
    EthernetInfo* info);
    
int udpDecode(char* data, 
    int dataLength, 
    char* returnedData, 
    EthernetInfo* info);

#endif /*UDP_H*/
