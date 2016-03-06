#ifndef ETHERNET_LAYER_H
#define ETHERNET_LAYER_H

typedef struct {
    unsigned char dest_addr[6];
    unsigned char src_addr[6];
    unsigned char type[2];
    unsigned char* data;
    int dataLength;
    unsigned char checksum[4];
} ethernetFrame;

int ethPack(ethernetFrame*, unsigned char*);
int ethUnpack(unsigned char*, int, ethernetFrame*);
void generateCRCChecksum(unsigned char*);

#endif /*ETHERNET_LAYER_H*/
