#include <stdio.h>
#include "cqueue.h"

int main(){
    Cqueue *cqueue = qcCreate(10);

    qcEnqueue(cqueue, (void*)10);
    qcEnqueue(cqueue, (void*)20);
    qcEnqueue(cqueue, (void*)30);
    qcEnqueue(cqueue, (void*)40);

    printf("%d\n", qcFirst(cqueue));
    imprime(cqueue);

    qcDequeue(cqueue);
    qcDequeue(cqueue);

    printf("%d\n", qcFirst(cqueue));
    imprime(cqueue);

    qcDequeue(cqueue);
    qcDequeue(cqueue);

    imprime(cqueue);

    if(qcIsEmpty(cqueue)){
        printf("Lista vazia\n");
    } else {
        printf("Lista contem itens\n");
    }

    if(qcDestroy(cqueue)){
        printf("Lista destruida\n");
    } else {
        printf("Erro ao destruir\n");
    }
}
