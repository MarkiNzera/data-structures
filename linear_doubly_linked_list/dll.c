#ifndef _DLL_C_
#define _DLL_C_

#include <stdlib.h>
#include <stdio.h>

typedef struct _dlnode_ {
    struct _dlnode_ *next, *prev;
    void* data;
} DLNode;

typedef struct _dllist_ {
    DLNode *first;
    DLNode *cur;
} DLList;

DLList* dllCreate(){
    DLList *l;
    l = (DLList*) malloc(sizeof(DLList));
    if(l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }

    return NULL;
}

int dllDestroy(DLList *l){
    if(l != NULL){
        if(l->first == NULL){
            free(l);
            return 1;
        }
    }
    return 0;
}

int dllInsertAsFirst(DLList *l, void* data){
    if(l != NULL){
        DLNode *newnode = (DLNode*)malloc(sizeof(DLNode));
        if(newnode != NULL){
            newnode->data = data;
            newnode->prev = NULL;
            newnode->next = l->first;
            if(l->first != NULL){
                l->first->prev = newnode;
            }
            l->first = newnode;
            return 1;
        }
    }

    return 0;
}

int dllInsertAsLast(DLList *l, void* data){
    DLNode *last = NULL, *newnode;
    if(l != NULL){
        newnode = (DLNode*)malloc(sizeof(DLNode));
        if(newnode != NULL){
            newnode->data = data;
            newnode->next = NULL;
            if(l->first != NULL){
                last = l->first;
                while(last->next != NULL){
                    last = last->next;
                }
            }

            newnode->prev = last;
            if(last != NULL){
                last->next = newnode;
            } else {
                l->first = newnode;
            }

            return 1;
        }
    }
    return 0;
}

int dllInsertNth(DLList *l, int p, void* data){
    DLNode *nth, *newnode; int i = 0;
    if(l == NULL) return 0;

    if(l->first != NULL){
        if(p > 0){
            nth = l->first;
            while(i < p - 1 && nth->next != NULL){
                i++;
                nth = nth->next;
            }

            if(i - 1 == p - 1){
                newnode = (DLNode*)malloc(sizeof(DLNode));
                if(newnode != NULL){
                    newnode->data = data;
                    newnode->prev = nth;
                    newnode->next = nth->next;
                    nth->next->prev = newnode;
                    nth->next = newnode;

                    return 1;
                }
            }
        } else if(p == 0){
            newnode = (DLNode*)malloc(sizeof(DLNode));
            if(newnode != NULL){
                dllInsertAsFirst(l, data);

                return 1;
            }
        }
    }
    

    return 0;
}

void* dllRemoveFirst(DLList *l){
    if(l == NULL) return NULL;

    if(l->first != NULL){
        DLNode *prim = l->first;
        void* data = prim->data;

        l->first = prim->next;
        if(prim->next != NULL){
            l->first->prev = NULL;
        }

        return data;
    }
    

    return NULL;
}

void* dllRemoveLast(DLList *l){
    if(l == NULL) return NULL;

    if(l->first != NULL){
        DLNode *prev = NULL, *last = l->first;
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

        return data;
    }

    return NULL;
}

void* dllRemoveSpec(DLList *l, void* key, int(*cmp)(void*, void*)){
    DLNode *prevnode, *nextnode;
    if(l != NULL){
        if(l->first != NULL){
            DLNode *spec = l->first; 
            int stat = cmp(spec->data, key);
            while(spec->next != NULL && stat != 1){
                spec = spec->next;
                stat = cmp(spec->data, key);
            }

            if(stat == 1){
                nextnode = spec->next;
                prevnode = spec->prev;
                void* data = spec->data;
                if(prevnode != NULL){
                    prevnode->next = nextnode;
                } else {
                    l->first = nextnode;
                }
                if(nextnode != NULL){
                    nextnode->prev = prevnode;
                }

                free(spec);
                return data;
            }
        }
    }

    return NULL;
}

void* dllRemoveLeft(DLList *l, void* key, int(*cmp)(void*, void*)){
    DLNode *prevnode, *nextnode;
    if(l != NULL){
        if(l->first != NULL){
            DLNode *spec = l->first;
            int stat = cmp(spec->data, key);
            while(spec->next != NULL && stat != 1){
                spec = spec->next;
                stat = cmp(spec->data, key);
            }

            if(stat == 1){
                DLNode *left = spec->prev;
                nextnode = left->next;
                prevnode = left->prev;
                void* data = left->data;
                if(prevnode != NULL){
                    prevnode->next = nextnode;
                } else {
                    l->first = nextnode;
                }

                if(nextnode != NULL){
                    nextnode->prev = prevnode;
                }

                free(left);
                return data;
                
            }
        }
    }

    return NULL;
}

void* dllRemoveNth (DLList *l, int k){
    DLNode *prevnode, *nextnode;
    if(l != NULL){
        if(l->first != NULL){
            DLNode *spec = l->first;
            int counter = 0;
            while(spec->next != NULL && counter != k){
                spec = spec->next;
                counter++;
            }

            if(counter == k){
                nextnode = spec->next;
                prevnode = spec->prev;
                void* data = spec->data;

                if(prevnode != NULL){
                    prevnode->next = nextnode;
                } else {
                    l->first = nextnode;
                }

                if(nextnode != NULL){
                    nextnode->prev = prevnode;
                }

                free(spec);
                return data;

            }

        }
    }

    return NULL;
}

int dllRemoveEven(DLList* l) {
    if (l != NULL) {
        if (l->first != NULL) {
            DLNode *spec = l->first, * aux, * prevnode, * nextnode;
            void* data;
            int counter = 0;
            while (spec->next != NULL) {
                if (counter % 2 == 0) {
                    prevnode = spec->prev;
                    nextnode = spec->next;
                    data = spec->data;

                    if (prevnode != NULL) {
                        prevnode->next = nextnode;
                    }
                    else {
                        l->first = nextnode;
                    }

                    if (nextnode != NULL) {
                        nextnode->prev = prevnode;
                    }

                    aux = spec;
                    spec = spec->next;
                    free(aux);
                } else {
                    spec = spec->next;

                }
                
                counter++;
            }
            return 1;
        }
    }

    return 0;
}

void* dllGetFirst(DLList *l){
    if(l != NULL){
        if(l->first != NULL){
            l->cur = l->first;
            return l->cur->data;
        }
    }

    return NULL;
}

void* dllGetNext(DLList *l){
    if(l != NULL){
        if(l->cur != NULL){
            if(l->cur->next != NULL){
                l->cur = l->cur->next;
                return l->cur->data;
            }          
        }
    }

    return NULL;
}

void* dllQuery(DLList *l, void* key, int(*cmp)(void*, void*)){
    if(l != NULL){
        if(l->first){
            DLNode *aux = l->first;
            int stat = cmp(aux->data, key);
            while(aux->next != NULL && stat != 1){
                aux = aux->next;
                stat = cmp(aux->data, key);
            }

            if(stat){
                return aux->data;
            }
        }
    }

    return NULL;
}

int dllEsvazia(DLList *l){
    if(l != NULL){
        if(l->first){
            DLNode *cur = l->first, *prevnode, *nextnode, *aux;
            void* data;
            while(cur != NULL){
                nextnode = cur->next;
                prevnode = cur->next;
                data = cur->data;

                if(prevnode != NULL){
                    prevnode = nextnode;
                } else{
                    l->first = nextnode;
                }

                if(nextnode != NULL){
                    nextnode->prev = prevnode;
                }
                aux = cur;
                cur = cur->next;

                free(aux);

            }   

            return 1;
        }
    }

    return 0;
}

#endif
