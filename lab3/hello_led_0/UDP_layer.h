#ifndef UDP_LAYER_H
#define UDP_LAYER_H

#define UDP_HEADER_LENGTH 8

typedef struct
{
    // Source and destination ports.
    // Both are 16 bits each.
    unsigned int sourcePort;
    unsigned int destPort;

    // This is the previous data that will be sent 
    // along with the header.
    unsigned char* data;
    int dataLength;
} UDPFrame;

int UDPPack(UDPFrame*, unsigned char*);
int UDPUnpack(unsigned char*, UDPFrame*, unsigned int);
void fillUDPHeader(UDPFrame*, int, int, char*, int);
void printUDPHeader(UDPFrame*);

#endif /* UDP_LAYER_H */
