#ifndef _QUEUE_C_
#define _QUEUE_C_

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct _queue_ {
    int front, rear;
    int maxItens;
    void* *item;
}Queue;

Queue* qCreate (int n){
    if(n <= 0) return NULL;

    Queue *q = (Queue*)malloc(sizeof(Queue));

    if(q == NULL) return NULL;

    q->item = (void**)malloc(sizeof(void*) * n);
    
    if(q->item == NULL) {
        free(q);
        return NULL;
    }

    q->maxItens = n;
    q->front = 0;
    q->rear = -1;
    return q;
}

int qDestroy(Queue *q){
    if(q == NULL || q->rear >= 0) return 0;

    free(q->item);
    free(q);
    return 1;

}

int qEnqueue(Queue *q, void* data){
    if(q == NULL || q->rear >= q->maxItens - 1) return 0;

    q->rear++;
    q->item[q->rear] = data;
    return 1;
}

void* qDequeue (Queue *q){
    void* data; int cur, next, i;
    if(q == NULL || q->rear < 0){
        return NULL;
    }

    data = q->item[q->front];
    for(i = q->front; i < q->rear; i++){
        cur = i; next = i + 1;
        q->item[cur] = q->item[next];
    }
    q->rear--;
    return data;
    
}

int qIsEmpty (Queue *q){
    if(q != NULL) return 1;
    if(q->rear < 0) return 1;

    return 0;
}

void* qFirst(Queue *q){
    if(q != NULL && q->rear >= 0){
        return q->item[q->front];
    }

    return NULL;
}

int qPromoteLast(Queue *q, int n){
    void* data;
    int moves, i, j;
    if(q != NULL && n > 0){
        if(q->rear > 0){
            data = q->item[q->rear];
            if(n < q->rear){
                moves = n;
            } else {
                moves = q->rear;
            }
            j = q->rear;
            for(i = moves; i > 0; i--){
                q->item[j] = q->item[j - 1];
                j--;
            }
            q->item[j] = data;

            return 1;
        }
    }
    return 0;
}

void imprime(Queue *q){
    for(int i = 0; i <= q->rear; i++){
        printf("%d ", q->item[i]);
    }
    printf("\n");
}

#endif