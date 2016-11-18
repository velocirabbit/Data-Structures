/**
 * Implementation of a basic queue structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

Queue *initQueue(int (*destroy)(void *data), char *(*toString)(void *data),
                 int (*compare)(void *key1, void *key2)) {
    Queue *newQueue;
    if ((newQueue = malloc(sizeof(Queue))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new Queue\n");
        newQueue = NULL;
    }
    else {
        newQueue->size = 0;
        newQueue->destroy = destroy;
        newQueue->toString = toString;
        newQueue->compare = compare;
        newQueue->head = NULL;
        newQueue->tail = NULL;
    }
    return newQueue;
}

QueueItem *initQueueItem(void *data) {
    QueueItem *newItem;
    if ((newItem = malloc(sizeof(QueueItem))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new QueueItem\n");
        newItem = NULL;
    }
    else {
        newItem->data = data;
        newItem->next = NULL;
    }
    return newItem;
}

QueueItem *freeQueueItem(Queue *queue, QueueItem *queueItem) {
    destroyQueueItem(queue, queueItem);
    QueueItem *next = queueItem->next;
    free(queueItem);
    return next;
}

void enqueue(Queue *queue, void *data) {
    QueueItem *newItem;
    if ((newItem = initQueueItem(data)) == NULL) {
        fprintf(stderr, "ERROR: Couldn't init new QueueItem to enqueue\n");
    }
    else {
        if (queue->size == 0) {
            queue->tail = newItem;
            queue->head = queue->tail;
        }
        else {
            queue->tail->next = newItem;
            queue->tail = newItem;
        }
        (queue->size)++;
    }
}

void *dequeue(Queue *queue) {
    if (queue->size == 0) {
        fprintf(stderr, "ERROR: Queue is empty; nothing to dequeue\n");
        return NULL;
    }
    QueueItem *front = queue->head;
    queue->head = front->next;
    (queue->size)--;
    if (queue->size == 0)
        queue->tail = queue->head;  // both should point to NULL
    void *frontdata = front->data;
    free(front);
    return frontdata;
}

void *peekQueue(Queue *queue) {
    if (queue->head != NULL)
        return queue->head->data;
    else
        return NULL;
}

void queuePrint(Queue *queue) {
    QueueItem *itemPtr = queue->head;
    for (itemPtr; itemPtr != NULL; itemPtr = itemPtr->next)
        queueItemPrint(queue, itemPtr);
}

void queueItemPrint(Queue *queue, QueueItem *queueItem) {
    printf("%s\n", (queue->toString)(queueItem->data));
}

void freeQueue(Queue *queue) {
    QueueItem *itemPtr = queue->head;
    while (itemPtr != NULL) {
        itemPtr = freeQueueItem(queue, itemPtr);
    }
    free(queue);
}
