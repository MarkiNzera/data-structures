#include <stdio.h>
#include "queue.h"

int main(){
    Queue *queue = qCreate(10);

    qEnqueue(queue, (void*)10);
    qEnqueue(queue, (void*)20);
    qEnqueue(queue, (void*)30);
    qEnqueue(queue, (void*)40);
    qPromoteLast(queue, 2);
    
    printf("%d\n", qFirst(queue));
    imprime(queue);

    qDequeue(queue);
    qDequeue(queue);

    printf("%d\n", qFirst(queue));
    imprime(queue);

    qDequeue(queue);
    qDequeue(queue);

    imprime(queue);

    if(qIsEmpty(queue)){
        printf("Lista vazia\n");
    } else {
        printf("Lista contem itens\n");
    }

    if(qDestroy(queue)){
        printf("Lista destruida\n");
    } else {
        printf("Erro ao destruir\n");
    }
}
