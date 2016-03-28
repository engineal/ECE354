#include "queue.h"

void push(Queue* queue, char* item, int length) {
    if (!isFull(queue)) {
        queue->items[queue->pointer] = item;
        queue->lengths[queue->pointer] = length;
        queue->pointer++;
    }
}

int pop(Queue* queue, char* item) {
    if (!isEmpty(queue)) {
        queue->pointer--;
        item = queue->items[queue->pointer];
        return queue->lengths[queue->pointer];
    }
    return -1;
}

int size(Queue* queue) {
    return queue->pointer;
}

int isEmpty(Queue* queue) {
    return queue->pointer == 0;
}

int isFull(Queue* queue) {
    return queue->pointer == QLENGTH;
}
