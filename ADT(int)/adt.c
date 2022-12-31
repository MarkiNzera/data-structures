#ifndef __ADT_C_
#define __ADT_C_

#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

#define FALSE 0
#define TRUE 1

typedef struct _adt_{
    int numItens;
    int maxItens;
    int *item;

} Adt;

Adt *adtCreate(int maxItens){
    if (maxItens <= 0){
        return NULL;
    }

    Adt *adt = (Adt*)malloc(sizeof(Adt));
    if(adt == NULL){
        return NULL;
    }

    adt->item = (int*)malloc(sizeof(int) * maxItens);
    if(adt->item == NULL){
        free(adt);
        return NULL;
    }

    adt->numItens = 0;
    adt->maxItens = maxItens;

    return adt;
}

int adtDestroy(Adt* adt){
    if(adt != NULL){
        if(adt->numItens == 0){
            free(adt->item);
            free(adt);
            return TRUE;
        }
    }
    return FALSE;
}

int adtInsert(Adt *adt, int item){
    if(adt == NULL){
        return FALSE;
    }

    if(adt->numItens >= adt->maxItens){
        return FALSE;
    }

    adt->item[adt->numItens] = item;
    adt->numItens++;
    return TRUE;
}

int adtRemove(Adt *adt, int key){
    if(adt == NULL || adt->numItens <= 0){
        return FALSE;
    }

    int aux;
    int pop = FALSE;
    for(int i = 0; i < adt->numItens; i++){
        if(adt->item[i] == key){
            aux = i;
            pop = adt->item[i];
            break;
        }
    }


    for(int i = aux; i <= adt->numItens; i++){
        adt->item[i] = adt->item[i + 1];
    }

    adt->numItens--;

    return pop;

}

int adtRemoveNth(Adt *adt, int nth){
    if(adt == NULL || adt->numItens <= 0 || adt->numItens < nth){
        return FALSE;
    }

    int pop = adt->item[nth];
    
    for(int i = nth; i <= adt->numItens; i++){
        adt->item[i] = adt->item[i + 1];
    }

    adt->numItens--;

    return pop;

}

int adtQuery (Adt *adt, int key){
    if(adt == NULL || adt->numItens <= 0){
        return FALSE;
    }

    int aux = FALSE;
    for(int i = 0; i < adt->numItens; i++){
        if(adt->item[i] == key){
            return TRUE;
        }
    }
    return FALSE;
}

void printAdt(Adt *adt){
    for(int i = 0; i < adt->numItens; i++){
        printf("%d ", adt->item[i]);
    }
    printf("\n");
}

#endif