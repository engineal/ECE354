#include "queue.h"
#include "basic_io.h"

Queue* initQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->start = 0;
    queue->end = 0;
    return queue;
}

void enqueue(Queue* queue, ethernetFrame* item) {
    if (!isFull(queue)) {
        queue->items[queue->end] = item;
        queue->end = (queue->end + 1) % QLENGTH;
    }
}

ethernetFrame* dequeue(Queue* queue) {
    if (!isEmpty(queue)) {
        ethernetFrame* result = queue->items[queue->start];
        queue->start = (queue->start + 1) % QLENGTH;
        return result;
    }
    return NULL;
}

ethernetFrame* peek(Queue* queue) {
    if (!isEmpty(queue)) {
        return queue->items[queue->start];
    }
    return NULL;
}

int size(Queue* queue) {
    if(queue->end >= queue->start) {
		return queue->end - queue->start;
	} else {
		return QLENGTH - queue->start + queue->end;
	}
}

int isEmpty(Queue* queue) {
    return queue->start == queue->end;
}

int isFull(Queue* queue) {
    return (queue->end + 1) % QLENGTH == queue->start;
}