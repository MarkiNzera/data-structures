#include <stdio.h>

#include "cdll.h"

int cmp(void* a, void* b){
    int *x = (int*)a, *y = (int*)b;

    if(*x >= *y){
        return 1;
    } else {
        return 0;
    }
}

void imprime(Dllist *l){
    void* aux = cdllGetFirst(l);
    void* first = aux;
    printf("%d ", *((int*)aux));
    while((aux = cdllGetNext(l)) != first){
        printf("%d ", *((int*)aux));
    }
    printf("\n");
}

int main() {
    Dllist* list1 = cdllCreate();
    
    int p1 = 10;
    int p2 = 30;
    int p3 = 20;
    int p4 = 40;
    int p5 = 50;
    int x = 90;
    int* p1Ptr = &p1;
    int* p2Ptr = &p2;
    int* p3Ptr = &p3;
    int* p4Ptr = &p4;
    int* p5Ptr = &p5;
    int* xPtr = &x;
    
    cdllInsertAsFirst(list1, p1Ptr);
    cdllInsertAsFirst(list1, p2Ptr);
    cdllInsertAsFirst(list1, p3Ptr);
    cdllInsertAsLast(list1, p4Ptr);
    imprime(list1);
    cdllInsertNth(list1, 2, p5Ptr);
    imprime(list1);

    
    cdllRemoveFirst(list1);
    cdllRemoveLast(list1);
    cdllRemoveSpec(list1, p1Ptr, cmp);

    imprime(list1);

    void* aux;
    if((aux = cdllQuery(list1, xPtr, cmp))){
        printf("%d", *((int*)aux));
    } else {
        printf("NULL");
    }
    
    return 0;
}

