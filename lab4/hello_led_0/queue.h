#ifndef QUEUE_H
#define QUEUE_H

#define QLENGTH 20

typedef struct
{
    char* items[QLENGTH];
    int lengths[QLENGTH];
    int pointer;
} Queue;

void push(Queue*, char*, int);
int pop(Queue*, char*);
int size(Queue*);
int isEmpty(Queue*);
int isFull(Queue*);

#endif /*QUEUE_H*/