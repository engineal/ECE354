#include "basic_io.h"
#include "UDP_layer.h"
#include "helper.h"

int UDPPack(UDPFrame* frame, unsigned char* output)
{
    int s = 0;
    
    int_to_char(output, frame->sourcePort, &s, 2);
    int_to_char(output, frame->destPort, &s, 2);

    // Add 8 to payload frame as the header adds
    // 8 bytes.
    int length = frame->dataLength + UDP_HEADER_LENGTH;
    int_to_char(output, length, &s, 2);
    
    // Set the checksum bytes to zero to prepare for
    // the checksum being computed on this header.
    int_to_char(output, 0, &s, 2);
    
    // Transfer payload data to final output
    charncat(output, frame->data, &s, frame->dataLength);

    // Compute the checksum
    int checksum = computeChecksum(output, length);
    int chcksmLocation = 6;
    int_to_char(output, checksum, &chcksmLocation, 2);

    return s;
}

void UDPUnpack(unsigned char* input, UDPFrame* frame)
{
    frame->sourcePort = (input[0]<<8) | input[1];
    frame->destPort = (input[2]<<8) | input[3];
    int length = (input[4]<<8) | input[5];
    frame->dataLength = length - UDP_HEADER_LENGTH;
    frame->checksum = (input[6]<<8) | input[7];
    // Clear checksum
    input[6] = 0;
    input[7] = 0;
    
    charnuncat(frame->data, input, 8, frame->dataLength);
}

void fillUDPHeader(UDPFrame* frame, int sourcePort, int destPort, char* data, int dataLength) {
    frame->sourcePort = sourcePort;
    frame->destPort = destPort;
    frame->checksum = 0;
    frame->data = data;
    frame->dataLength = dataLength;
}

void printUDPHeader(UDPFrame* frame) {
    printf("UDP header:\n");
    printf("source port: %d\n", frame->sourcePort);
    printf("destination port: %d\n", frame->destPort);
    printf("checksum: %x\n", frame->checksum);
    printf("data:");
    int i;
    for (i = 0; i < frame->dataLength; i++) {
        if(i%8 == 0)
            printf("\n");
        printf("0x%2X,", frame->data[i]);
    }
    printf("\n\n");
}
