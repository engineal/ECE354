#include "helper.h"
#include "ethernet_layer.h"

int ethPack(ethernetFrame* frame, unsigned char* output) {
    int s = 0;
    
    charncat(output, frame->dest_addr, &s, 6);
    charncat(output, frame->src_addr, &s, 6);
    charncat(output, frame->type, &s, 2);
    charncat(output, frame->data, &s, frame->dataLength);
    charncat(output, frame->checksum, &s, 4);
    
    return s;
}

int ethUnpack(unsigned char* input, int inputLength, ethernetFrame* frame) {
    int s = 0;
    
    charnuncat(frame->dest_addr, input, &s, 6);
    charnuncat(frame->src_addr, input, &s, 6);
    charnuncat(frame->type, input, &s, 2);
    charnuncat(frame->data, input, &s, inputLength - 18);
    charnuncat(frame->checksum, input, &s, 4);

    return 0;
}

void generateChecksum(unsigned char* dest) {
    dest[0] = 0x00;
    dest[1] = 0x00;
    dest[2] = 0x00;
    dest[3] = 0x20;
}
