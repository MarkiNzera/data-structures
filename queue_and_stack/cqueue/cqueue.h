#ifndef CQUEUE_H_
#define CQUEUE_H_

typedef struct _queue_ Cqueue;
Cqueue* qcCreate(int max);
int qcDestroy(Cqueue *q);

int incCirc(int i, int max);
int decCirc(int i, int max);

int qcEnqueue(Cqueue *q, void* elm);
void* qcDequeue(Cqueue *q);

void* qcFirst(Cqueue *q);
int qcIsEmpty (Cqueue *q);
int qcPromoteLast(Cqueue *q, int n);
void imprime(Cqueue *q);

#endif