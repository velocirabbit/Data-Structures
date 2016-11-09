/**
 * Header file for implementation of a basic queue structure.
 *
 */
#ifndef QUEUE
#define QUEUE

 // Macro functions
 #define queueSize(queue)           ((queue)->size)
 #define queueHead(queue)           ((queue)->head)
 #define isQueueHead(queue, item)   ((item) == (queue)->head)

typedef struct queueitem_ {
    void *data;
    struct queueitem_ *next;
} QueueItem;

typedef struct queue_ {
    int size;
    int (*destroy)(void *data);
    char *(*toString)(void *data);
    int (*compare)(void *key1, void *key2);
    QueueItem *head;
    QueueItem *tail;
} Queue;

Queue *initQueue(int (*destroy)(void *data), char *(*toString)(void *data),
                 int (*compare)(void *key1, void *key2));
QueueItem *initQueueItem(void *data);
QueueItem *freeQueueItem(Queue *queue, QueueItem *queueItem);
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
void *peekQueue(Queue *queue);
void queuePrint(Queue *queue);
void queueItemPrint(Queue *queue, QueueItem *queueItem);
void freeQueue(Queue *queue);

#endif
