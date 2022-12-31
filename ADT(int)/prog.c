#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

#define FALSE 0
#define TRUE 1

void printMenu(){
    printf("O que deseja fazer agora?\n");
    printf("1 - Adicionar um elemento ao cofo\n");
    printf("2 - Remover um elemento do cofo\n");
    printf("3 - Remover uma posicao do cofo\n");
    printf("4 - Verificar a existencia de um elemento no cofo\n");
    printf("5 - Destruir o cofo (finaliza o programa)\n");
    printf("6 - Listar os itens do cofo\n");
}

int main(){
    printf("Bem vindo ao cofo!\n\n");
    printf("Quantos lugares o seu cofo precisa?\n");

    int maxItens;

    scanf("%d", &maxItens);
    while (maxItens < 1){
        printf("Valor inválido!");
        scanf("%d",&maxItens);
    }

    Adt *cofo = adtCreate(maxItens);

    if(cofo == NULL){
        printf("Infelizmente o cofo não pode ser alocado :(\n");
    } else{
        printf("Cofo alocado com sucesso!\n");
    }

    int executando = TRUE;
    int elemento, resultado_da_operacao;
    while(executando){
        int opcao;
        printMenu();
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                printf("Que elemento voce deseja adicionar? ");
                scanf("%d", &elemento);
                printf("\n");

                resultado_da_operacao = adtInsert(cofo, elemento);
                if(resultado_da_operacao){
                    printf("Elemento inserido com sucesso\n\n");
                } else{
                    printf("Erro ao inserir o elemento\n\n");
                }
                break;
            case 2:
                printf("Que elemento voce deseja remover? ");
                scanf("%d", &elemento);
                printf("\n");

                resultado_da_operacao = adtRemove(cofo, elemento);  
                if(resultado_da_operacao){
                    printf("Elemento %d removido com sucesso\n\n", resultado_da_operacao);
                } else{
                    printf("Erro ao remover o elemento\n\n");
                }
                break;
            case 3:
                printf("Qual a posição do elemento que voce deseja remover? ");
                scanf("%d", &elemento);
                printf("\n");

                resultado_da_operacao = adtRemoveNth(cofo, elemento);  
                if(resultado_da_operacao){
                    printf("Elemento %d removido com sucesso\n\n", resultado_da_operacao);
                } else{
                    printf("Erro ao remover o elemento\n\n");
                }
                break;

            case 4:
                printf("Que elemento voce deseja verificar? ");
                scanf("%d", &elemento);
                printf("\n");

                resultado_da_operacao = adtQuery(cofo, elemento);  
                if(resultado_da_operacao){
                    printf("Elemento existente\n\n");
                } else{
                    printf("Elemento inexistente\n\n");
                }
                break;
            case 5:
                printf("Destruindo o cofo, saindo do programa...\n");
                
                resultado_da_operacao = adtDestroy(cofo);
                if(resultado_da_operacao){
                    printf("Cofo destruido com sucesso, finalizando o programa...\n\n");
                    executando = FALSE;
                } else{
                    printf("Erro ao destruir o cofo, talvez ainda tenha itens no cofo\n\n");
                }
                break;
            case 6:
                printAdt(cofo);
                break;
            default:
                printf("Digite uma opção valida\n\n");
                break;
        }
    }
}
