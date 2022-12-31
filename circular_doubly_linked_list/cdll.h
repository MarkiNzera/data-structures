#ifndef _CSLL_H_
#define _CSLL_H_

typedef struct _dlnode_ Dlnode;
typedef struct _dllist_ Dllist;

Dllist* cdllCreate();
int cdllDestroy(Dllist *l);

int cdllInsertAsFirst(Dllist *l, void* data);
int cdllInsertAsLast(Dllist *l, void* data);
int cdllInsertNth(Dllist *l, int p, void* data);

void* cdllGetFirst(Dllist *l);
void* cdllGetNext(Dllist *l);

void* cdllQuery(Dllist *l, void* key, int(*cmp)(void*, void*));
void* cdllRemoveFirst(Dllist *l);
void* cdllRemoveSpec(Dllist *l, void* key, int(*cmp)(void*, void*));
void* cdllRemoveLast(Dllist *l);

#endif
