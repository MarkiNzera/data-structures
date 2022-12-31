#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gadt.h"

#define TRUE 1
#define FALSE 0

typedef struct _aluno_{
    char nome[30];
    int idade;
    float media;
} Aluno;

int cmpPorNome(void* _aluno ,void* _nome){
    Aluno *aluno = (Aluno*)_aluno;
    char nome[30];
    strcpy(nome, (char*)_nome);
    if (!strcmp(aluno->nome, _nome)){
        return TRUE;
    } else {
        return FALSE;
    }
}

int cmpPorIdade(void* _aluno, void* _idade){
    Aluno *aluno = (Aluno*)_aluno;
    int *idade = (int*) _idade;
    if (aluno->idade == *idade){
        return TRUE;
    } else {
        return FALSE;
    }
}

int cmpPorMedia(void* _aluno, void* _media){
    Aluno *aluno = (Aluno*)_aluno;
    float *media = (float*) _media;
    if (aluno->idade == *media){
        return TRUE;
    } else {
        return FALSE;
    }
}

void imprimeMenuPrincipal(){
    printf("\tMenu principal\n");
    printf("1. Inserir um aluno na colecao\n");
    printf("2. Remover um aluno da colecao\n");
    printf("3. Consultar um aluno na colecao\n");
    printf("4. Listar os alunos da colecao\n");
    printf("5. Destruir a colecao aluno\n");
}

void imprimeMenuRemover(){
    printf("\tMenu remover\n");
    printf("1. Remover por nome\n");
    printf("2. Remover por idade\n");
    printf("3. Remover por media\n");
}

void imprimeMenuConsultar(){
    printf("\tMenu Consultar\n");
    printf("1. Consultar por nome\n");
    printf("2. Consultar por idade\n");
    printf("3. Consultar por media\n");
}

void main(){
    int menu;
    int maxItens;
    printf("\t--Sistema de alunos--\n");
    printf("Quantos lugares o seu cofo precisa?\n");
    scanf("%d", &maxItens);
    while (maxItens < 1){
        printf("Valor inválido!");
        scanf("%d",&maxItens);
    }

    gAdt *cofo = gadtCreate(maxItens);

    if(cofo == NULL){
        printf("Infelizmente o cofo não pode ser alocado :(\n");
    } else{
        printf("Cofo alocado com sucesso!\n");
    }
    
    int rodando = TRUE;
    while(rodando){
        imprimeMenuPrincipal();
        scanf("%d",&menu);
        Aluno *aluno;
        Aluno *auxC;
        switch (menu) {
			case 1:
                aluno = (Aluno*)malloc(sizeof(Aluno));
                printf("Informe o nome, idade e media do aluno? ");
                scanf("%s %d %f", aluno->nome, &aluno->idade, &aluno->media);

                if(aluno == NULL){
                    printf("Erro ao cadastrar o aluno");
                } else {
                    if(gadtInsert(cofo, (void*)aluno)){
                        printf("\nAluno %s inserido com sucesso\n\n", aluno->nome);
                    } else {
                        printf("\nErro ao inserir o aluno\n\n");
                    }
                }

				break;
			case 2:
                imprimeMenuRemover();
                int menuRemov;
                char nomeRemov[30];
                int idadeRemov;
                float mediaRemov;
                Aluno *alunoRemov;
                printf("Opção desejada\n");
                scanf("%d", &menuRemov);

                switch(menuRemov){
                    case 1:
                        printf("Nome a remover:\n");
                        scanf("%s", nomeRemov);
                        alunoRemov = gadtRemove(cofo, &nomeRemov, cmpPorNome);
                        if(alunoRemov){
                            printf("\nO aluno: %s foi removido\n\n", alunoRemov->nome);
                        } else {
                            printf("\nErro ao remover o aluno\n\n");
                        }
                        break;
                    case 2:
                        printf("Idade a remover\n");
                        scanf("%d", &idadeRemov);
                        alunoRemov = gadtRemove(cofo, &idadeRemov, cmpPorIdade);
                        if(alunoRemov){
                            printf("\nO aluno: %s foi removido\n\n", alunoRemov->nome);
                        } else {
                            printf("\nErro ao remover o aluno\n\n");
                        }
                        break;
                    
                    case 3:
                        printf("Media a remover:\n");
                        scanf("%f", &mediaRemov);
                        alunoRemov = gadtRemove(cofo, &mediaRemov, cmpPorMedia);
                        if(alunoRemov){
                            printf("\nO aluno: %s foi removido\n\n", alunoRemov->nome);
                        } else {
                            printf("\nErro ao remover o aluno\n\n");
                        }
                        break;
                    default:
                        printf("\nOpcao invalida\n\n");
                        break;
                }
                
                break;
			case 3:
                imprimeMenuConsultar();
                int menuConsult;
                char nomeConsult[30];
                int idadeConsult;
                float mediaConsult;
                Aluno *alunoConsult;
                printf("Opção desejada\n");
                scanf("%d", &menuConsult);

                switch(menuConsult){
                    case 1:
                        printf("Consultar nome:\n");
                        scanf("%s", nomeRemov);
                        alunoConsult = gadtQuery(cofo, &nomeRemov, cmpPorNome);
                        if(alunoConsult){
                            printf("\nO aluno: %s esta no cofo\n\n", alunoConsult->nome);
                        } else {
                            printf("\nO aluno não esta na colecao\n\n");
                        }
                        break;
                    case 2:
                        printf("Consultar idade\n");
                        scanf("%d", &idadeRemov);
                        alunoConsult = gadtQuery(cofo, &idadeRemov, cmpPorIdade);
                        if(alunoConsult){
                            printf("\nO aluno: %s esta no cofo\n\n", alunoConsult->nome);
                        } else {
                            printf("\nO aluno não esta na colecao\n\n");
                        }
                        break;
                    
                    case 3:
                        printf("Consultar media:\n");
                        scanf("%f", &mediaRemov);
                        alunoConsult = gadtQuery(cofo, &mediaRemov, cmpPorMedia);
                        if(alunoConsult){
                            printf("\nO aluno: %s esta no cofo\n\n", alunoConsult->nome);
                        } else {
                            printf("\nO aluno não esta na colecao\n\n");
                        }
                        break;
                    default:
                        printf("\nOpcao invalida\n\n");
                        break;
                }
				break;
			case 4:
                auxC = gadtGetFirst(cofo);
                if (auxC == NULL){
                    printf("\nColecao esta vazia\n\n");
                } else {
                    int i = 1;
                    printf("\t--Colecao aluno\n");
                    do{
                        printf("%d.Aluno\nNome: %s\nIdade: %d\nMedia: %.2f\n", i, auxC->nome, auxC->idade, auxC->media);
                        auxC = gadtGetNext(cofo);
                        i++;
                    } while (auxC != NULL);
                }
                

				break;
            case 5:
                printf("Destruindo o colecao, saindo do programa...\n");
                
                int resultado_da_operacao = gadtDestroy(cofo);
                if(resultado_da_operacao){
                    printf("Colecao destruido com sucesso, finalizando o programa...\n");
                    rodando = FALSE;
                } else{
                    printf("Erro ao destruir a colecao, talvez ainda tenha itens no cofo\n");
                }
                break;
			default:
				printf("\nOpcao invalida!\n\n");
				break;
			}

    }

    exit(0);

}
