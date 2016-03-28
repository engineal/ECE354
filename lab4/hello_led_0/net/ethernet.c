#include "ethernet.h"
#include "basic_io.h"
#include "custom_io.h"
#include "helper.h"
#include "queue.h"
#include "DM9000A.C"
#include "layers/ethernet_layer.h"

int packet_num;
volatile Queue* receivedQueue;

volatile int ackReceived;

void ethernet_interrupts() {
    writeDecimalLCD(packet_num++);
    
    char* data = (char*)malloc(sizeof(char)*1024);
    int dataLength = 0;
    int aaa=ReceivePacket(data, &dataLength);
    if (!aaa) {
        printf("Received %d bytes\n", dataLength);
        push(receivedQueue, data, dataLength);
    } else {
        free(data);        
    }
}

void ethernetInit(char localMAC[]) {
    packet_num = 0;
    writeDecimalLCD(packet_num);
    receivedQueue = (Queue*)malloc(sizeof(Queue));
    receivedQueue->pointer = 0;
    
    DM9000_init(localMAC);
    alt_irq_register(DM9000A_IRQ, NULL, (void*)ethernet_interrupts);
}

void ethernetSend(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame frame;
    fillEthernetHeader(&frame, destMAC, localMAC, data, length);
    printEthernetHeader(&frame);
    unsigned char output[ETHERNET_HEADER_LENGTH + length];
    int outputLength = ethPack(&frame, output);
    
    ackReceived = 0;
    //while (!ackReceived) {
        printf("Sending %d bytes\n", outputLength);
        TransmitPacket(output, outputLength);
        printf("Sent, waiting for ACK\n");
        
        msleep(1000);
    //}
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

int compareMAC(char* mac1, char* mac2) {
    int macPass = 1;
    int i;
    for (i = 0; i < 6; i++) {
        macPass &= mac1[i] == mac2[i];
    }
    return macPass;
}

int ethernetReceive(
    char* returnedData, 
    char* localMAC)
{
    char* data;
    int dataLength = pop(receivedQueue, data);
    if (dataLength > 0) {
        ethernetFrame frame;
        frame.data = returnedData;
        ethUnpack(data, dataLength, &frame);
        free(data);
        printEthernetHeader(&frame);
        
        int checksum = 0; //computeChecksum(data, ETHERNET_HEADER_LENGTH);
        
        if (frame.checksum != checksum) {
            printf("Ethernet Checksum fail: %x != %x\n\n", frame.checksum, checksum);
        } else if (!compareMAC(frame.dest_addr, localMAC)) {
            printf("MAC fail: %2x:%2x:%2x:%2x:%2x:%2x != %2x:%2x:%2x:%2x:%2x:%2x\n\n",
                frame.dest_addr[0], frame.dest_addr[1], frame.dest_addr[2], frame.dest_addr[3], frame.dest_addr[4], frame.dest_addr[5],
                localMAC[0], localMAC[1], localMAC[2], localMAC[3], localMAC[4], localMAC[5]);
        } else {
            if (frame.data[0] == 0xF0) {
                printf("Received ACK\n\n");
                ackReceived++;
            } else {
                printf("Received Packet\n\n");
                printf("Sending ACK\n");
                char ackData[] = {0xF0};
                //ethernetSendNoACK(ackData, 1, frame.src_addr, localMAC);
                
                return frame.dataLength;
            }
        }
    }
    return -1;
}