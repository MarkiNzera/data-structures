#ifndef _CDLL_C_
#define _CDLL_C_

#include <stdio.h>
#include <stdlib.h>
#include "cdll.h"

typedef struct _dlnode_{
    void *data;
    struct _dlnode_ *next;
    struct _dlnode_ *prev;
}Dlnode;

typedef struct _dllist_{
    Dlnode *first;
    Dlnode *cur;
}Dllist;

Dllist* cdllCreate(){
    Dllist *l = (Dllist*)malloc(sizeof(Dllist));
    if(l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }

    return NULL;
}

int cdllDestroy(Dllist *l){
    if(l != NULL){
        if(l->first == NULL){
            free(l);
            return 1;
        }
    }

    return 0;
}

int cdllInsertAsFirst(Dllist* l, void* data) {
    Dlnode *newnode, *aux;
    if (l != NULL) {
        newnode = (Dlnode*)malloc(sizeof(Dlnode));

        if (newnode != NULL) {
            newnode->data = data;
            if (l->first == NULL) {

                newnode->next = newnode;
                newnode->prev = newnode;
                l->first = newnode;

                return 1;
            } else {
                aux = l->first;
                while (aux->next != l->first) {
                    aux = aux->next;
                }

                aux->next = newnode;
                l->first->prev = newnode;
                newnode->next = l->first;
                l->first = newnode;
                newnode->prev = aux;

                return 1;
            }
        }

    }

    return 0;
}

int cdllInsertAsLast(Dllist* l, void* data) {
    Dlnode* newnode, * aux;
    if (l != NULL) {
        newnode = (Dlnode*)malloc(sizeof(Dlnode));
        if (newnode != NULL) {
            newnode->data = data;
            if (l->first != NULL) {
                aux = l->first;
                while (aux->next != l->first) {
                    aux = aux->next;
                }

                newnode->next = aux->next;
                aux->next = newnode;
                newnode->prev = aux;
                l->first->prev = newnode;
                

                return 1;
            }
            else {
                l->first = newnode;
                newnode->next = l->first;
                newnode->prev = l->first;
                return 1;
            }
        }
    }

    return 0;
}

int cdllInsertNth(Dllist *l, int p, void* data){
    Dlnode *nth, *newnode; int i = 0;
    if(l == NULL) return 0;
    
    if(l->first != NULL){
        if(p > 0){
            nth = l->first;
            while(i < p - 1 && nth->next != l->first){
                i++;
                nth = nth->next;
            }

            if(i == p - 1){
                newnode = (Dlnode*)malloc(sizeof(Dlnode));
                if(newnode != NULL){
                    newnode->data = data;
                    newnode->prev = nth;
                    newnode->next = nth->next;
                    nth->next->prev = newnode;
                    nth->next = newnode;

                    return 1;
                }
            }
        } else if (p == 0){
            newnode = (Dlnode*)malloc(sizeof(Dlnode));
            if(newnode != NULL){
                cdllInsertAsFirst(l, data);

                return 1;
            }
        }
    } 
    

    return 0;
}

void* cdllGetFirst(Dllist *l){
    if(l != NULL){
        if(l->first != NULL){
            l->cur = l->first;
            return l->cur->data;
        }
    }

    return NULL;
}

void* cdllGetNext(Dllist *l){
    if(l != NULL){
        if(l->cur != NULL){
            l->cur = l->cur->next;
            return l->cur->data;
        }
    }

    return NULL;
}

void* cdllQuery(Dllist *l, void* key, int(*cmp)(void*, void*)){
    Dlnode *spec;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            int stat = cmp(spec->data, key);
            while(spec->next != l->first && stat != 1){
                spec = spec->next;
                stat = cmp(spec->data, key);
            }

            if(stat == 1){
                return spec->data;
            }
        }
    }

    return NULL;
}

void* cdllRemoveSpec(Dllist *l, void* key, int(*cmp)(void*, void*)){
    Dlnode *spec;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            int stat = cmp(spec->data, key);
            while(spec->next != l->first && stat != 1){
                spec = spec->next;
                stat = cmp(spec->data, key);
            }

            Dlnode *prevnode, *nextnode;
            if(stat == 1){
                prevnode = spec->prev;
                nextnode = spec->next;

                if(spec == l->first){
                    l->first = nextnode;
                } 
                prevnode->next = nextnode;
                nextnode->prev = prevnode;

                void* data = spec->data;
                free(spec);
                
                return data;
            }
        }
    }

    return NULL;
}

void* cdllRemoveFirst(Dllist *l){
    if(l != NULL){
        if(l->first != NULL){
            Dlnode *prim = l->first, *prevnode, *nextnode;
            void* data = prim->data;
            l->first = prim->next;

            prevnode = prim->prev;
            nextnode = prim->next;
            
            prevnode->next = nextnode;
            nextnode->prev = prevnode;

            free(prim);
            return data;
            
        }
    }

    return NULL;
}

void* cdllRemoveLast(Dllist *l){
    if(l != NULL){
        if(l->first != NULL){
            Dlnode *last = l->first, *prevnode, *nextnode;
            while(last->next != l->first){
                last = last->next;
            }

            prevnode = last->prev;
            nextnode = last->next;

            prevnode->next = nextnode;
            nextnode->prev = prevnode;

            void* data = last->data;
            free(last);

            return data;
        }
    }

    return NULL;
}

#endif
