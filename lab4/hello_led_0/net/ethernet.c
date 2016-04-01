#include "ethernet.h"
#include "basic_io.h"
#include "custom_io.h"
#include "helper.h"
#include "queue.h"
#include "DM9000A.C"
#include "layers/ethernet_layer.h"

char* ether_addr;
int packet_num;

Queue* sendQueue;
Queue* receivedQueue;

volatile int ackReceived;

int compareMAC(char* mac1, char* mac2) {
    int macPass = 1;
    int i;
    for (i = 0; i < 6; i++) {
        macPass &= mac1[i] == mac2[i];
    }
    return macPass;
}

void ethernet_interrupts() {
    writeDecimalLCD(packet_num++);
    
    char data[1024];
    int dataLength = 0;
    int aaa=ReceivePacket(data, &dataLength);
    if (!aaa) {
        printf("Received %d bytes\n", dataLength);
        ethernetFrame* frame = (ethernetFrame*)malloc(sizeof(ethernetFrame));
        frame->data = (char*)malloc(sizeof(char)*(1024-ETHERNET_HEADER_LENGTH));
        ethUnpack(data, dataLength, frame);
        //printEthernetHeader(frame);
        
        int checksum = 0; //computeChecksum(data, ETHERNET_HEADER_LENGTH);
        
        if (frame->checksum != checksum) {
            printf("Ethernet Checksum fail: %x != %x\n\n", frame->checksum, checksum);
        } else if (!compareMAC(frame->dest_addr, ether_addr)) {
            printf("MAC fail: %2x:%2x:%2x:%2x:%2x:%2x != %2x:%2x:%2x:%2x:%2x:%2x\n\n",
                frame->dest_addr[0], frame->dest_addr[1], frame->dest_addr[2], frame->dest_addr[3], frame->dest_addr[4], frame->dest_addr[5],
                ether_addr[0], ether_addr[1], ether_addr[2], ether_addr[3], ether_addr[4], ether_addr[5]);
        } else {
            if (frame->data[0] == 0xF0) {
                printf("Received ACK\n\n");
                ackReceived++;
                //dequeue(sendQueue);
            } else {
                printf("Received Packet\n\n");
                enqueue(receivedQueue, frame);
            }
        }
    } else {
        free(data);        
    }
}

void ethernetInit(char localMAC[]) {
    ether_addr = localMAC;
    packet_num = 0;
    receivedQueue = initQueue();
    
    writeDecimalLCD(packet_num);
    
    DM9000_init(localMAC);
    alt_irq_register(DM9000A_IRQ, NULL, (void*)ethernet_interrupts);
}

void ethernet_worker() {
    ethernetFrame* frame = peek(sendQueue);
    if (frame != NULL) {
        //send frame
    }
}

void ethernetSend(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame frame;
    fillEthernetHeader(&frame, destMAC, localMAC, data, length);
    //printEthernetHeader(&frame);
    unsigned char output[ETHERNET_HEADER_LENGTH + length];
    int outputLength = ethPack(&frame, output);
    
    ackReceived = 0;
    while (!ackReceived) {
        printf("Sending %d bytes\n", outputLength);
        TransmitPacket(output, outputLength);
        printf("Sent, waiting for ACK\n");
        
        msleep(1000);
    }
    printf("ACK acknowledged: %d\n\n", ackReceived);
}

void ethernetSendNoACK(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame frame;
    fillEthernetHeader(&frame, destMAC, localMAC, data, length);
    //printEthernetHeader(&frame);
    unsigned char output[ETHERNET_HEADER_LENGTH + length];
    int outputLength = ethPack(&frame, output);
    
    printf("Sending %d bytes\n", outputLength);
    TransmitPacket(data, outputLength);
    printf("Sent\n\n");
}

int ethernetReceive(
    char* returnedData, 
    char* localMAC)
{
    ethernetFrame* frame = dequeue(receivedQueue);
    if (frame != NULL) {
        //printEthernetHeader(frame);

        printf("Sending ACK\n");
        char ackData[] = {0xF0};
        ethernetSendNoACK(ackData, 1, frame->src_addr, localMAC);

        charncpy(returnedData, frame->data, frame->dataLength);
        free(frame->data);
        free(frame);
        return frame->dataLength;
    }
    return -1;
}
