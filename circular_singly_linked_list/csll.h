#ifndef _CSLL_H_
#define _CSLL_H_

typedef struct _slnode_ Slnode;
typedef struct _sllist_ Sllist;

Sllist* csllCreate();
int csllDestroy(Sllist *l);

int csllInsertAsFirst(Sllist *l, void* data);
int csllInsertAsLast(Sllist *l, void* data);
int csllInsertNth(Sllist *l, int p, void* data);
int csllInsertBeforeSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*));
int csllInsertAfterSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*));

void* csllGetFirst(Sllist *l);
void* csllGetNext(Sllist *l);

void* csllRemoveFirst(Sllist *l);
void* csllRemoveLast(Sllist *l);
// void* csllRemove(Sllist *l, void* key, int (*cmp)(void*, void*));
void* csllQuery(Sllist *l, void *key, int (*cmp)(void*, void*));

Slnode* csllGetLastNode(Sllist *l);
int csllNNodes(Sllist *l);
void* csllGetMiddleData(Sllist *l);

int csllPunishFirst(Sllist *l);
int csllPromoteLast(Sllist *l);

#endif
