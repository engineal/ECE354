#ifndef UDP_H
#define UDP_H

#include "layers/udp_layer.h"
#include "ip.h"

#define UDP_LENGTH       IP_DATA_LENGTH
#define UDP_DATA_LENGTH  (UDP_LENGTH-UDP_HEADER_LENGTH)

typedef struct
{
    char* localIP;
    int localPort;
    char* localMAC;
    
    char* destIP;
    int destPort;
    char* destMAC;   
} UDPInfo;

void udpSend(char*, int, UDPInfo*);
int udpReceive(char*, UDPInfo*);

#endif /*UDP_H*/
