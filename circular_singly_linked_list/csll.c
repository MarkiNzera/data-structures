#ifndef _CSLL_C_
#define _CSLL_C_

#include <stdio.h>
#include <stdlib.h>
#include "csll.h"

typedef struct _slnode_{
    void *data;
    struct _slnode_ *next;
}Slnode;

typedef struct _sllist_{
    Slnode *first;
    Slnode *cur;
}Sllist;

Sllist* csllCreate(){
    Sllist *l;
    l = (Sllist*)malloc(sizeof(Sllist));
    if(l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }

    return NULL;
}

int csllDestroy(Sllist *l){
    if(l == NULL) return 0;

    if(l->first == NULL){
        free(l);
        return 1;
    }
    

    return 0;
}

int csllInsertAsFirst(Sllist* l, void* data) {
    Slnode* newnode, * aux;
    if (l != NULL) {
        newnode = (Slnode*)malloc(sizeof(Slnode));

        if (newnode != NULL) {
            newnode->data = data;
            if (l->first == NULL) {

                newnode->next = newnode;
                l->first = newnode;

                return 1;
            }
            else {
                aux = l->first;
                while (aux->next != l->first) {
                    aux = aux->next;
                }

                aux->next = newnode;
                newnode->next = l->first;
                l->first = newnode;
                return 1;
            }
        }

    }

    return 0;
}

int csllInsertAsLast(Sllist* l, void* data) {
    Slnode* newnode, * aux;
    if (l != NULL) {
        newnode = (Slnode*)malloc(sizeof(Slnode));
        if (newnode != NULL) {
            newnode->data = data;
            if (l->first != NULL) {
                aux = l->first;
                while (aux->next != l->first) {
                    aux = aux->next;
                }

                newnode->next = aux->next;
                aux->next = newnode;

                return 1;
            }
            else {
                l->first = newnode;
                newnode->next = l->first;
                return 1;
            }
        }
    }

    return 0;
}

int csllInsertNth(Sllist *l, int p, void* data){
    Slnode *nth, *newnode; int i = 0;
    if(l != NULL){
        if(l->first != NULL){
            if(p > 0){
                nth = l->first;
                while(i < p - 1 && nth->next != l->first){
                    i++;
                    nth = nth->next;
                }

                if(i == p - 1){
                    newnode = (Slnode*)malloc(sizeof(Slnode));
                    if(newnode != NULL){
                        newnode->data = data;
                        newnode->next = nth->next;
                        nth->next = newnode;
                        return 1;
                    }
                }
            }else if(p == 0){
                newnode = (Slnode*)malloc(sizeof(Slnode));
                if(newnode != NULL){
                    Slnode* last = l->first;
                    while (last->next != l->first) {
                        last = last->next;
                    }
                    newnode->data = data;
                    newnode->next = l->first;
                    l->first = newnode;
                    last->next = l->first;

                    return 1;
                }
            }
        }
    }
    return 0;
}

int csllInsertBeforeSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*)){
    Slnode *spec, *prev = NULL; int stat;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            stat = cmp(spec->data, key);
            while(spec->next != l->first && stat != 1){
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
                        newnode->next = newnode;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

int csllInsertAfterSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*)){
    Slnode *spec, *newnode;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            int stat = cmp(spec->data, key);
            while(spec->next != l->first && stat != 1){
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
    }

    return 0;
}

void* csllGetFirst(Sllist *l){
    if(l != NULL){
        if(l->first != NULL){
            l->cur = l->first;
            return l->cur->data;
        }
    }

    return NULL;
}

void* csllGetNext(Sllist *l){
    if(l != NULL){
        if(l->cur != NULL){
            l->cur = l->cur->next;
            return l->cur->data;
        }
    }

    return NULL;
}

void* csllRemoveFirst(Sllist *l){
    void* data; Slnode *prim;
    if(l != NULL){
        if(l->first != NULL){
            Slnode *last = l->first;
            while(last->next != l->first){
                last = last->next;
            }
            prim = l->first;
            last->next = prim->next;
            data = prim->data;
            l->first = prim->next;
            
            free(prim);
            return data;
        }
    }

    return NULL;
}

// void* csllRemove(Sllist *l, void* key, int (*cmp)(void*, void*)){
//     Slnode *spec, *prev;
//     if(l != NULL){
//         if(l->first != NULL){
//             spec = l->first; prev = spec->next;
//             int stat = cmp(spec->data, key);
//             while(spec->next != l->first && stat != 1){
//                 spec = prev;
//                 spec = spec->next;
//                 stat = cmp(spec->data, key);
//             }

//             if(stat == 1){
//                 void* data = spec->data;
//                 if(l->first == spec){
//                     csllRemoveFirst(l);
//                 } else {
//                     prev->next = spec->next;
//                 }
//                 free(spec);
                
//                 return data;
//             }
//         }
//     }

//     return NULL;
// }

void* csllRemoveLast(Sllist *l){
    if(l != NULL){
        if(l->first != NULL){
            Slnode *prev = NULL;
            Slnode *last = l->first;

            while(last->next != l->first){
                prev = last;
                last = last->next;
            }
            void* data = last->data;
            if(prev != NULL){
                prev->next = last->next;
            } else {
                l->first = NULL;
            }
            free(last);

            return data;
        }
    }

    return NULL;
}

void* csllQuery(Sllist *l, void *key, int (*cmp)(void*, void*)){
    Slnode *spec;
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

Slnode* csllGetLastNode(Sllist *l){
    Slnode *last;
    if(l != NULL){
        if(l->first != NULL){
            last = l->first;
            while(last->next != l->first){
                last = last->next;
            }
            return last;
        } 
    }

    return NULL;
}

int csllNNodes(Sllist *l){
    int i = 0; Slnode *last;
    if(l == NULL) return -1;

    if(l->first != NULL){
        last = l->first; i++;
        
        while(last->next != l->first){
            last = last->next;
            i++;
        }
        
        return i;
    }
    

    return 0;
}

int csllPunishFirst(Sllist *l){
    if(l == NULL) return 0;
    if(l->first == NULL) return 0;

    Slnode *aux = l->first, *last = l->first;
    l->first = l->first->next;
    
    while(last->next != l->first){
        last = last->next;
    }

    last->next = aux;
    aux->next = l->first;

    return 1;
}

int csllPromoteLast(Sllist *l){
    if(l == NULL) return 0;
    if(l->first == NULL) return 0;

    Slnode *prev = NULL, *last = l->first;

    while(last->next != l->first){
        prev = last;
        last = last->next;
    }

    if(prev != NULL){ 
        l->first = last;
    } else {
        return 0;
    }

    return 1;

}

void* csllGetMiddleData(Sllist *l){
    if(l == NULL) return NULL;
    if(l->first == NULL) return NULL;

    int tam = csllNNodes(l), i = 0;
    int middle = tam / 2;
    Slnode *aux = l->first;

    while(aux->next != l->first && i < middle){
        i++;
        aux = aux->next;
    }

    return aux->data;
}


#endif
