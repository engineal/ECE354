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

// Returns 1 if succesful, 0 if there was an error.
int UDPUnpack(unsigned char* input, UDPFrame* frame, unsigned int port)
{
    frame->sourcePort = (input[0]<<8) | input[1];
    frame->destPort = (input[2]<<8) | input[3];
    int length = (input[4]<<8) | input[5];
    frame->dataLength = length - UDP_HEADER_LENGTH;
    int checksum = (input[6]<<8) | input[7];
    charnuncat(frame->data, input, 8, frame->dataLength);

    /*int chcksmLocation = 6;
    int_to_char(input, 0, &chcksmLocation, 2);
    int checksum2 = computeChecksum(input, UDP_HEADER_LENGTH);

    // If the saved checksum does not equal the final 
    // checksum, there was an error on transmission.
    int checksumPass = checksum == checksum2;
    if (!checksumPass) {
        printf("UDP Checksum fail: %x != %x\n", checksum, checksum2);
    }*/
    int portPass = frame->destPort == port;
    if (!portPass) {
        printf("Port fail: %d != %d\n", frame->destPort, port);
    }
    return portPass;
}

void fillUDPHeader(UDPFrame* frame, int sourcePort, int destPort, char* data, int dataLength) {
    frame->sourcePort = sourcePort;
    frame->destPort = destPort;
    frame->data = data;
    frame->dataLength = dataLength;
}

void printUDPHeader(UDPFrame* frame) {
    printf("UDP header:\n");
    printf("source port: %d\n", frame->sourcePort);
    printf("destination port: %d\n", frame->destPort);
    printf("data:");
    int i;
    for (i = 0; i < frame->dataLength; i++) {
        if(i%8 == 0)
            printf("\n");
        printf("0x%2X,", frame->data[i]);
    }
    printf("\n\n");
}
