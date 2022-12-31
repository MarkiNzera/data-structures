#ifndef _DLL_H_
#define _DLL_H_

typedef struct _dlnode_ DLNode;
typedef struct _dllist_ DLList;

DLList* dllCreate();
int dllDestroy(DLList *l);

int dllInsertAsFirst(DLList *l, void* data);
int dllInsertAsLast(DLList *l, void* data);
int dllInsertNth(DLList *l, int p, void* data);

void* dllRemoveFirst(DLList *l);
void* dllRemoveLast(DLList *l);
void* dllRemoveSpec(DLList *l, void* key, int(*cmp)(void*, void*));
void* dllRemoveLeft(DLList *l, void* key, int(*cmp)(void*, void*));
void* dllRemoveNth (DLList *l, int k);
int dllRemoveEven(DLList *l);

void* dllGetFirst(DLList *l);
void* dllGetNext(DLList *l);

void* dllQuery(DLList *l, void* key, int(*cmp)(void*, void*));
int dllEsvazia(DLList *l);

#endif
