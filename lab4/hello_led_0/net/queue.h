#ifndef QUEUE_H
#define QUEUE_H

#include "layers/ethernet_layer.h"

#define QLENGTH 20

typedef struct
{
    ethernetFrame* items[QLENGTH];
    int start;
    int end;
} Queue;

Queue* initQueue();
void enqueue(Queue*, ethernetFrame*);
ethernetFrame* dequeue(Queue*);
ethernetFrame* peek(Queue*);
int size(Queue*);
int isEmpty(Queue*);
int isFull(Queue*);

#endif /*QUEUE_H*/
