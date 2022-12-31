#ifndef CQUEUE_C_
#define CQUEUE_C_

#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"

typedef struct _queue_{
    int front;
    int rear;
    int nElms;
    int maxItens;
    void* *elms;
}Cqueue;

int incCirc(int i, int max){
    if(i == max - 1){
        return 0;
    }

    return i + 1;
}

int decCirc(int i, int max){
    if(i == 0){
        return max - 1;
    }

    return i - 1;
}

Cqueue* qcCreate(int max){
    if(max <= 0) return NULL;

    Cqueue *c = (Cqueue*)malloc(sizeof(Cqueue));
    if(c == NULL) return NULL;

    c->elms = (void**)malloc(sizeof(void*) * max);
    if(c->elms == NULL){
        free(c);
        return NULL;
    }

    c->front = 0;
    c->rear = -1;
    c->nElms = 0;
    c->maxItens = max;

    return c;
}

int qcDestroy(Cqueue *q){
    if(q == NULL) return 0;
    if(q->nElms > 0) return 0;

    free(q->elms);
    free(q);
    return 1;

}

int qcEnqueue(Cqueue *q, void* elm){
    if(q == NULL) return 0;
    if(q->nElms >= q->maxItens) return 0;
    
    q->rear = incCirc(q->rear, q->maxItens);
    q->elms[q->rear] = elm;
    q->nElms++;
    return 1;

}

void* qcDequeue(Cqueue *q){
    void* data;
    if(q == NULL) return NULL;
    if(q->nElms <= 0) return NULL;

    data = q->elms[q->front];
    q->front = incCirc(q->front, q->maxItens);
    q->nElms--;

    return data;
}

void* qcFirst(Cqueue *q){
    if(q != NULL && q->rear >= 0){
        return q->elms[q->front];
    }

    return NULL;
}

int qcIsEmpty (Cqueue *q){
    if(q != NULL) return 1;
    if(q->rear < 0) return 1;

    return 0;
}

int qcPromoteLast(Cqueue *q, int n){
    void* data;
    int moves, i, j, prev_j;
    if(q != NULL && n > 0){
        if(q->nElms > 0){
            data = q->elms[q->rear];
            if(n < q->nElms){
                moves = n;
            } else {
                moves = q->nElms;
            }

            j = q->rear;
            for(i = moves; i > 0; i = decCirc(i, q->maxItens)){
                prev_j = decCirc(j, q->maxItens);
                q->elms[j] = q->elms[prev_j];
                j = prev_j;
            }
            q->elms[j] = data;

            return 1;
        }
    }

    return 0;
}

void imprime(Cqueue *q){
    for(int i = q->front; i <= q->rear; i++){
        printf("%d ", q->elms[i]);
    }
    printf("\n");
}


#endif