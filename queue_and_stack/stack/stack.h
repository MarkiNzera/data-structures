#ifndef _STACK_H_
#define _STACK_H_

typedef struct _stack_ Stack;
Stack *stkCreate(int max);
int stkDestroy (Stack *s);

int stkPush( Stack *s, void *elm );
void *stkPop( Stack *s );
void *stkTop( Stack *s );

int stkIsEmpty( Stack *s );
void stkDestroyAny(Stack *s, int(*myfree)(void*));
void stkClean(Stack *s);

void imprimeItens(Stack *s);

#endif