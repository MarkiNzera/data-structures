#ifndef _STACK_C_
#define _STACK_C_

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define FALSE 0
#define TRUE 1

typedef struct _stack_{
    int maxItens;
    int top;
    void* *item;
}Stack;

Stack *stkCreate(int max){
    Stack *s;
    if(max <= 0) return NULL;

    s = (Stack*) malloc(sizeof(Stack));

    if(s == NULL) return NULL;

    s->item = (void**) malloc(sizeof(void*) * max);

    if(s->item == NULL) return NULL;

    s->maxItens = max;
    s->top = -1;
    return s;

}

int stkDestroy(Stack *s){
    if(s == NULL || s->top >= 0) return FALSE;

    free(s->item);
    free(s);
    return TRUE;
}

int stkPush(Stack *s, void *elm){
    if(s == NULL || s->top >= s->maxItens - 1) return FALSE;

    s->top++;
    s->item[s->top] = elm;
    return TRUE;
}

void* stkPop(Stack *s){
    void *aux;
    if(s == NULL || s->top < 0) return NULL;

    aux = s->item[s->top];
    s->top--;
    return aux;
}

void *stkTop(Stack *s){
    void *aux;
    if(s == NULL) return NULL;
    if(s->top < 0) return NULL;

    aux = s->item[s->top];
    return aux;
}

int stkIsEmpty(Stack *s){
    if(s == NULL) return TRUE;
    if(s->top < 0) return TRUE;

    return FALSE;
}

void stkClean(Stack *s){
    void* elm;
    if(s != NULL){
        elm = stkPop(s);
        while(elm != NULL){
            elm = stkPop(s);
        } 
    }
}

void stkDestroyAny(Stack *s, int(*myfree)(void*)){
    void* elm;
    if(s != NULL){
        elm = stkPop(s);
        while(elm != NULL){
            myfree(elm);
            elm = stkPop(s);
        }
    }
}

void imprimeItens(Stack *s){
    for(int i = 0; i <= s->top; i++){
        printf("%d ", s->item[i]);
    }
    printf("\n");
}

#endif
