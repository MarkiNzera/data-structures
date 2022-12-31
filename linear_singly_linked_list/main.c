#include <stdio.h>

#include "sll.h"

int cmp(void* a, void* b){
    int x = (int) a;
    int y = (int) b;

    if (x == y) return 1;
    else return 0;
}

void imprime(Sllist *l){
    void* aux = sllGetFirst(l);
    printf("%d ", *((int*)aux));
    while((aux = sllGetNext(l)) != NULL){
        printf("%d ", *((int*)aux));
    }
    printf("\n");
}

int main(){
    Sllist *list = sllCreate();

    int p1 = 10;
    int p2 = 30;
    int p3 = 20;
    int p4 = 40;
    int p5 = 50;
    int x = 90;
    int y = 110;
    int* p1Ptr = &p1;
    int* p2Ptr = &p2;
    int* p3Ptr = &p3;
    int* p4Ptr = &p4;
    int* p5Ptr = &p5;
    int* xPtr = &x;
    int* yPtr = &y;

    sllInsertAsFirst(list, p3Ptr);
    sllInsertAsFirst(list, p2Ptr);
    sllInsertAsFirst(list, p1Ptr);
    sllInsertAsLast(list, p4Ptr);
    sllInsertNth(list, 4, p5Ptr);
    sllInsertBeforeSpec(list, p3Ptr, xPtr, cmp);
    sllInsertAfterSpec(list, p3Ptr, xPtr, cmp);

    printf("last node: %d\n", (sllGetLastNode(list)));
    printf("middle: %d\n", *((int*)sllGetMiddleNode(list)));
    printf("n nodes: %d\n", sllNNodes(list));
    
    imprime(list);
    
    sllRemoveFirst(list);
    sllRemoveLast(list);
    sllRemove(list, yPtr, cmp);

    imprime(list);

    void* aux;
    if((aux = sllQuery(list, p4Ptr, cmp))){
        printf("%d\n", *((int*)aux));
    } else {
        printf("NULL\n");
    }

    sllPunishFirst(list);
    imprime(list);

    sllPromoteLast(list);
    imprime(list);

    return 0;

}
