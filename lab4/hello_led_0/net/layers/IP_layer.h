#ifndef IP_LAYER_H
#define IP_LAYER_H

#define IP_HEADER_LENGTH 20 // incl. for fields we have as empty

typedef struct {
    int version; // 4 bits
    int id; // 16 bits
    int checksum;
    unsigned char src_addr[4];
    unsigned char dest_addr[4];
    unsigned char* data;
    int dataLength;
} IPFrame;


int IPPack(IPFrame*, unsigned char*);
void IPUnpack(unsigned char*, IPFrame*);
void fillIPHeader(IPFrame*, int, int, char*, char*, char*, int);
void printIPHeader(IPFrame*);

#endif /*IP_LAYER_H*/
