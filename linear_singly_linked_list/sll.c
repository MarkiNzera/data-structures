#ifndef _SLL_C_
#define _SLL_C_

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

typedef struct _slnode_{
    void *data;
    struct _slnode_ *next;
}Slnode;

typedef struct _sllist_{
    Slnode *first;
    Slnode *cur;
}Sllist;

Sllist* sllCreate(){
    Sllist *l;
    l = (Sllist*)malloc(sizeof(Sllist));
    if(l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }
}

int sllDestroy(Sllist *l){
    if(l != NULL) return 0;

    if(l->first == NULL){
        free(l);
        return 1;
    }

    return 0;
}

int sllInsertAsFirst(Sllist *l, void* data){
    Slnode *newnode;
    if(l == NULL) return 0;
    newnode = (Slnode*)malloc(sizeof(Slnode));
    
    if(newnode == NULL ) return 0;

    newnode->data = data;
    newnode->next = l->first;
    l->first = newnode;

    return 1;

}

int sllInsertAsLast(Sllist *l, void* data){
    if(l != NULL){

        Slnode *newnode = (Slnode*)malloc(sizeof(Slnode));
        if(newnode == NULL) return 0;

        newnode->data = data;
        newnode->next = NULL;

        Slnode *last;

        if(l->first == NULL){
            l->first = newnode;
        } else {
            last = sllGetLastNode(l);
            last->next = newnode;
        }

        return 1;
    }

    return 0;
}

int sllInsertNth(Sllist *l, int p, void* data){
    Slnode *nth, *newnode; int i = 0;
    if(l == NULL) return 0;
    
    if(l->first != NULL){
        if(p > 0){
            nth = l->first;
            while(i < p - 1 && nth->next != NULL){
                i++;
                nth = nth->next;
            }

            if(i - 1 == p - 1){
                newnode = (Slnode*)malloc(sizeof(Slnode));
                if(newnode != NULL){
                    newnode->data = data;
                    newnode->next = nth->next;
                    nth->next = newnode;
                    return 1;
                }
            }
        } else if(p == 0){
            newnode = (Slnode*)malloc(sizeof(Slnode));
            if(newnode != NULL){
                sllInsertAsFirst(l, data);

                return 1;
            }
        }
    }
    return 0;
}

int sllInsertBeforeSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*)){
    Slnode *spec, *prev = NULL; int stat;
    if(l == NULL) return 0;

    if(l->first != NULL){
        spec = l->first;
        stat = cmp(spec->data, key);
        while(spec->next != NULL && stat != 1){
            prev = spec;
            spec = spec->next;
            stat = cmp(spec->data, key);
        }   

        if(stat == 1){
            Slnode *newnode = (Slnode*)malloc(sizeof(Slnode));
            if(newnode != NULL){
                newnode->data = data;
                if(prev != NULL){
                    newnode->next = prev->next;
                    prev->next = newnode;
                } else {
                    l->first = newnode;
                    newnode->next = NULL;
                }
                return 1;
            }
        }
    }
    
    return 0;
}

int sllInsertAfterSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*)){
    Slnode *spec, *newnode;
    if(l != NULL || l->first != NULL){
        spec = l->first;
        int stat = cmp(spec->data, key);
        while(spec->next != NULL && stat != 1){
            spec = spec->next;
            stat = cmp(spec->data, key);
        }

        if(stat == 1){
            newnode = (Slnode*) malloc(sizeof(Slnode));
            if(newnode != NULL){
                newnode->data = data;
                newnode->next = spec->next;
                spec->next = newnode;
                return 1;
            }
        }
    }

    return 0;
}

void* sllGetFirst(Sllist *l){
    void* data; Slnode *prim;
    if(l == NULL) return NULL;
    if(l->first != NULL){
        prim = l->first;
        data = prim->data;
        l->cur = l->first;
        return data;
    }

    return NULL;
}

void* sllGetNext(Sllist *l){
    void* data;
    if(l == NULL) return NULL;
    if(l->cur->next != NULL){
        l->cur = l->cur->next;
        data = l->cur->data;

        return data;
    }

    return NULL;
}

Slnode* sllGetLastNode(Sllist *l){
    Slnode *last;
    if(l == NULL) return NULL;
    if(l->first != NULL){
        last = l->first;
        while(last->next != NULL){
            last = last->next;
        }
        return last;
    }

    return NULL;
}

void* sllGetMiddleNode(Sllist *l){
    if(l == NULL) return NULL;

    if(l->first == NULL) return 0;

    int tam = sllNNodes(l), i = 0;
    int middle = tam / 2;
    Slnode *aux = l->first;

    while(aux->next != NULL && i < middle){
        i++;
        aux = aux->next;
    }

    return aux->data;
}

int sllNNodes(Sllist *l){
    int i = 0; Slnode *last;
    if(l == NULL) return -1;
    if(l->first != NULL){
        last = l->first; i++;
        
        while(last->next != NULL){
            last = last->next;
            i++;
        }
         
        return i;
    }

    return 0;
}

void* sllRemoveFirst(Sllist *l){
    void* data; Slnode *prim;
    if(l == NULL) return NULL;
    if(l->first != NULL){
        prim = l->first;
        data = prim->data;
        l->first = prim->next;
        free(prim);
        return data;
    }

    return NULL;
}

void* sllRemoveLast(Sllist *l){
    if(l == NULL) return NULL;
    if(l->first != NULL){
        Slnode *prev = NULL;
        Slnode *last = l->first;

        while(last->next != NULL){
            prev = last;
            last = last->next;
        }
        void* data = last->data;
        if(prev != NULL){
            prev->next = NULL;
        } else {
            l->first = NULL;
        }
        free(last);

        return data;
    }

    return NULL;
}

void* sllRemove(Sllist *l, void* key, int (*cmp)(void*, void*)){
    Slnode *spec, *prev;
    if(l == NULL) return NULL;
    if(l->first != NULL){
        spec = l->first; prev = NULL;
        int stat = cmp(spec->data, key);
        while(spec->next != NULL && stat != 1){
            prev = spec;
            spec = spec->next;
            stat = cmp(spec->data, key);
        }

        if(stat == 1){
            void* data = spec->data;
            if(l->first == spec){ // prev == NULL
                l->first = spec->next;
            } else {
                prev->next = spec->next;
            }
            free(spec);
            
            return data;
        }
    }

    return NULL;
}

void* sllQuery(Sllist *l, void *key, int (*cmp)(void*, void*)){
    Slnode *spec;
    if(l == NULL) return NULL;
    if(l->first != NULL){
        spec = l->first;
        int stat = cmp(spec->data, key);
        while(spec->next != NULL && stat != 1){
            spec = spec->next;
            stat = cmp(spec->data, key);
        }

        if(stat == 1){
            return spec->data;
        }
    }

    return NULL;
}

int sllPunishFirst(Sllist *l){
    if(l == NULL) return 0;
    if(l->first == NULL) return 0;

    Slnode *aux = l->first, *last = l->first;
    l->first = l->first->next;
    
    while(last->next != NULL){
        last = last->next;
    }

    last->next = aux;
    aux->next = NULL;

    return 1;
}

int sllPromoteLast(Sllist *l){
    if(l == NULL) return 0;
    if(l->first == NULL) return 0;

    Slnode *prev = NULL, *last = l->first;

    while(last->next != NULL){
        prev = last;
        last = last->next;
    }

    if(prev != NULL){
        last->next = l->first;
        l->first = last;
        prev->next = NULL;
    } else {
        return 0;
    }

    return 1;

}


#endif
