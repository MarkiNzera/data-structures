#ifndef _GADT_C_
#define _GADT_C_
#include <stdio.h>
#include<stdlib.h>
#include "gadt.h"

#define TRUE 1
#define FALSE 0

typedef struct _gadt_{
    int numItens;
    int maxItens;
    int cur;
    void**item;
} gAdt;

gAdt *gadtCreate(int maxItens){
    if(maxItens <= 0){
        return NULL;
    }

    gAdt *c = (gAdt*)malloc(sizeof(gAdt));
    if(c == NULL){
        return NULL;
    }

    c->item = (void**)malloc(sizeof(void*) * maxItens);
    if(c->item == NULL){
        free(c);
        return NULL;
    }

    c->maxItens = maxItens;
    c->numItens = 0;
    c->cur = -1;

    return c;

}

int gadtDestroy(gAdt *c){
    if(c == NULL || c->numItens > 0){
        return FALSE;
    }

    free(c->item);
    free(c);
    return TRUE;

}

int gadtInsert(gAdt *c, void* item){
    if(c == NULL || c->numItens >= c->maxItens){
        return FALSE;
    }

    c->item[c->numItens] = item;
    c->numItens++;
    return TRUE;

}

void* gadtGetFirst(gAdt *c){
    if(c == NULL || c->numItens <= 0){
        return NULL;
    }

    c->cur = 0;
    return c->item[c->cur];
    
}

void* gadtGetNext (gAdt *c){
    if(c == NULL || c->numItens <= 0 || c->cur + 1 >= c->numItens){
        return NULL;
    }

    c->cur++;
    return c->item[c->cur];
}

void* gadtQuery (gAdt *c, void *key, int (*cmp)(void *, void*)){
    if(c == NULL || c->numItens <= 0){
        return NULL;
    }

    int cont, stat;
    cont = 0;
    stat = cmp(c->item[cont], key);
    while(cont < c->numItens && stat == FALSE){
        cont++;
        stat = cmp(c->item[cont], key);
    }

    if(stat == TRUE){
        return c->item[cont];
    }

    return NULL;
}

void *gadtRemove(gAdt *c, void *key, int (*cmp)(void *, void*)){
    if(c == NULL || c->numItens <= 0){
        return NULL;
    }
    int cont = 0, stat = FALSE, aux;
    void* data;
    for(cont = 0; cont < c->numItens; cont++){
        if(cmp(c->item[cont], key)){
            break;
        }  
    }

    
    data = c->item[cont];
    for(int j = cont; j <= c->numItens; j++){
        c->item[j] = c->item[j + 1];
    }
    c->numItens--;
    return data;
    

    return NULL;
}

#endif