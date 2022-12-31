#include <stdio.h>

#include "csll.h"

int cmp(void* a, void* b){
    int x = (int) a;
    int y = (int) b;

    if (x == y) return 1;
    else return 0;
}

void imprime(Sllist *l){
    void* aux = csllGetFirst(l);
    void* first = aux;
    printf("%d ", *((int*)aux));
    while((aux = csllGetNext(l)) != first){
        printf("%d ", *((int*)aux));
    }
    printf("\n");
}

int main() {
    Sllist* list = csllCreate();
    
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
    

    csllInsertAsFirst(list, p3Ptr);
    csllInsertAsFirst(list, p2Ptr);
    csllInsertAsFirst(list, p1Ptr);
    csllInsertAsLast(list, p4Ptr);
    csllInsertBeforeSpec(list, p4Ptr, p5Ptr, cmp);
    csllInsertAfterSpec(list, p4Ptr, xPtr, cmp);

    imprime(list);

    csllRemoveFirst(list);
    csllRemoveLast(list);
    csllRemove(list, p1Ptr, cmp);

    csllPunishFirst(list);
    imprime(list);
    csllPromoteLast(list);
    imprime(list);
    printf("%d\n", csllNNodes(list));

    

    return 0;
}

