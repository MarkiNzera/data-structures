#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct _queue_ Queue;

Queue* qCreate (int n);
int qDestroy(Queue *q); 

int qEnqueue (Queue *q, void* data);
void* qDequeue (Queue *q);

int qIsEmpty (Queue *q);
void* qFirst(Queue *q);
int qPromoteLast(Queue *q, int n);
void imprime(Queue *q);

#endif