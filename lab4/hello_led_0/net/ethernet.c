#include "ethernet.h"
#include "basic_io.h"
#include "custom_io.h"
#include "helper.h"
#include "queue.h"
#include "DM9000A.C"
#include "layers/ethernet_layer.h"

#define ETHERNET_DATA_LENGTH (1024-ETHERNET_HEADER_LENGTH)

char* ether_addr;
int packet_num;

Queue* sendQueue;
Queue* receivedQueue;

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
        frame->data = (char*)malloc(sizeof(char)*ETHERNET_DATA_LENGTH);
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
                printf("Received layer 2 ACK\n\n");
                // Remove packet from send queue for which the layer 2 ack was for
                ethernetFrame* sentFrame = dequeue(sendQueue);
                if (sentFrame != NULL) {
                    free(sentFrame->data);
                    free(sentFrame);
                }
            } else {
                printf("Received Packet\n\n");
                // Add packet to receive queue
                enqueue(receivedQueue, frame);
                return; // don't clean up data that was enqueued
            }
        }
        free(frame->data);
        free(frame);
    }
}

void ethernetInit(char localMAC[]) {
    ether_addr = localMAC;
    packet_num = 0;
    sendQueue = initQueue();
    receivedQueue = initQueue();
    
    writeDecimalLCD(packet_num);
    
    DM9000_init(localMAC);
    alt_irq_register(DM9000A_IRQ, NULL, (void*)ethernet_interrupts);
}

/*
 * Will send the next queued packet, which very well could mean resending
 * the last packet if no layer 2 ack was received.
 *
 * TODO: delay retransmission
 */
void ethernet_worker() {
    //if time is up
    ethernetFrame* frame = peek(sendQueue);
    if (frame != NULL) {
        //printEthernetHeader(frame);
        unsigned char output[ETHERNET_HEADER_LENGTH + frame->dataLength];
        int outputLength = ethPack(frame, output);
        
        printf("Sending %d bytes from queue\n", outputLength);
        TransmitPacket(output, outputLength);
        printf("Sent from queue\n");
    }
}

/*
 * Enqueue the requested packet to be sent
 * Packet will be sent by ethernet_worker() when its turn comes
 * (once all previously sent packets receive acks), and will
 * prevent sending another packet until a layer 2 ack is received for it
 */
void ethernetSend(
    char* data, int length, 
    char* destMAC, char* localMAC)
{
    ethernetFrame* frame = (ethernetFrame*)malloc(sizeof(ethernetFrame));
    char* frameData = (char*)malloc(sizeof(char)*length);
    charncpy(frameData, data, length); // Copy data so it is availible in queue
    fillEthernetHeader(frame, destMAC, localMAC, frameData, length);
    //printEthernetHeader(frame);
    enqueue(sendQueue, frame);
}

/*
 * Send packet at once, not waiting for previous packets to be sent,
 * does not wait for a layer 2 ack
 */
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

/*
 * Receive a packet from the recived queue
 * This packet will be a valid packet (i.e. checksum and MAC address pass)
 * and will not be an layer 2 ack
 *
 * Returns: the length of the returned data, -1 if no packet left to receive
 */
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
