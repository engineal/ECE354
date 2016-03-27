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
} UDPInfo;

void udpSend(char*, int, UDPInfo*);
int udpReceive(char*, UDPInfo*);

#endif /*UDP_H*/
