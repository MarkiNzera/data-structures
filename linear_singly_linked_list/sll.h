#ifndef _SLL_H_
#define _SLL_H_

typedef struct _slnode_ Slnode;
typedef struct _sllist_ Sllist;

Sllist* sllCreate();
int sllDestroy(Sllist *l);

int sllInsertAsFirst(Sllist *l, void* data);
int sllInsertAsLast(Sllist *l, void* data);
int sllInsertNth(Sllist *l, int p, void* data);
int sllInsertBeforeSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*));
int sllInsertAfterSpec(Sllist *l, void* key, void* data, int(*cmp)(void*, void*));

void* sllGetFirst(Sllist *l);
void* sllGetNext(Sllist *l);
Slnode* sllGetLastNode(Sllist *l);
void* sllGetMiddleNode(Sllist *l);
int sllNNodes(Sllist *l);

void* sllRemoveFirst(Sllist *l);
void* sllRemoveLast(Sllist *l);
void* sllRemove(Sllist *l, void* key, int (*cmp)(void*, void*));
void* sllQuery(Sllist *l, void *key, int (*cmp)(void*, void*));

int sllPunishFirst(Sllist *l);
int sllPromoteLast(Sllist *l);

#endif
