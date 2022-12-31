#include <stdio.h>
#include "stack.h"



int main(){
    Stack *stack = stkCreate(10);

    if(stkIsEmpty(stack)){
        printf("NULL\n");
    }

    stkPush(stack, (void*)10);
    stkPush(stack, (void*)20);
    stkPush(stack, (void*)30);
    stkPush(stack, (void*)40);

    imprimeItens(stack);

    stkPop(stack);

    imprimeItens(stack);

    printf("%d\n", (int)stkTop(stack));

    stkClean(stack);

    if(stkIsEmpty(stack)){
        printf("NULL\n");
    }

    return 0;
}
