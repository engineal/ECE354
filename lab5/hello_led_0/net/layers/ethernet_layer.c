#include "basic_io.h"
#include "helper.h"
#include "ethernet_layer.h"

// Takes a full ethernetFrame struct and stores it into
// output, ready for transmission.
int ethPack(ethernetFrame* frame, unsigned char* output) 
{
    int s = 0;
    
    charncat(output, frame->dest_addr, &s, 6);
    charncat(output, frame->src_addr, &s, 6);
    charncat(output, frame->type, &s, 2);
    charncat(output, frame->data, &s, frame->dataLength);
    
    // Checksum computed automatically
    
    return s;
}

// Takes char* input which holds transmitted packet and interprets it, 
// storing the result in an ethernetFrame struct.
void ethUnpack(unsigned char* input, int inputLength, ethernetFrame* frame) 
{
    charnuncat(frame->dest_addr, input, 0, 6);
    charnuncat(frame->src_addr, input, 6, 6);
    charnuncat(frame->type, input, 12, 2);
    charnuncat(frame->data, input, 14, inputLength - ETHERNET_HEADER_LENGTH);
    frame->dataLength = inputLength - ETHERNET_HEADER_LENGTH;
    frame->checksum = (input[inputLength-4]<<24) | (input[inputLength-3]<<16) | (input[inputLength-2]<<8) | input[inputLength-1];
}

void fillEthernetHeader(ethernetFrame* frame, char* dest_addr, char* src_addr, char* data, int dataLength) {
    charncpy(frame->dest_addr, dest_addr, 6);
    charncpy(frame->src_addr, src_addr, 6);
    frame->type[0] = 0x08;
    frame->type[1] = 0x00;
    frame->data = data;
    frame->dataLength = dataLength;
    frame->checksum = 0;
}

void printEthernetHeader(ethernetFrame* frame) {
    printf("Ethernet header:\n");
    printf("destination address: %2x:%2x:%2x:%2x:%2x:%2x\n", frame->dest_addr[0], frame->dest_addr[1], frame->dest_addr[2], frame->dest_addr[3], frame->dest_addr[4], frame->dest_addr[5]);
    printf("source address: %2x:%2x:%2x:%2x:%2x:%2x\n", frame->src_addr[0], frame->src_addr[1], frame->src_addr[2], frame->src_addr[3], frame->src_addr[4], frame->src_addr[5]);
    printf("type: %x %x\n", frame->type[0], frame->type[1]);
    printf("data:");
    int i;
    for (i = 0; i < frame->dataLength; i++) {
        if(i%8 == 0)
            printf("\n");
        printf("0x%2X,", frame->data[i]);
    }
    printf("\nchecksum: %x\n\n", frame->checksum);
}
