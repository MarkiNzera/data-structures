#ifndef _GADT_H_
#define _GADT_H_
typedef struct _gadt_ gAdt;
#ifdef _GADT_C_
gAdt *gadtCreate( int max_itens);
int gadtDestroy (gAdt *c);

int gadtInsert(gAdt *c, void *item);
void* gadtRemove(gAdt *c, void *key, int (*cmp)(void *, void*));
void* gadtQuery (gAdt *c, void *key, int (*cmp)(void *, void*));

void* gadtGetFirst(gAdt *c);
void* gadtGetNext (gAdt *c);
#else
extern gAdt *gadtCreate( int max_itens );
extern int gadtDestroy (gAdt *c);

extern int gadtInsert(gAdt *c, void *item );
extern void* gadtRemove(gAdt *c, void *key, int (*cmp)(void *, void*));
extern void* gadtQuery (gAdt *c, void *key, int (*cmp)(void *, void*));

extern void* gadtGetFirst(gAdt *c);
extern void* gadtGetNext (gAdt *c);
#endif
#endif