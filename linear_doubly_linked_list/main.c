#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

typedef struct _aluno_{
    char nome[30];
    int idade;
    float media;
} Aluno;

int cmpPorNome(void* _aluno, void* _nome) {
    Aluno* aluno = (Aluno*)_aluno;
    char nome[30];
    strcpy(nome, (char*)_nome);
    if (!strcmp(aluno->nome, nome)) {
        return 1;
    }
    else {
        return 0;
    }
}

int cmpPorIdade(void* _aluno, void* _idade) {
    Aluno* aluno = (Aluno*)_aluno;
    int* idade = (int*)_idade;
    if (aluno->idade == *idade) {
        return 1;
    }
    else {
        return 0;
    }
}

int cmpPorMedia(void* _aluno, void* _media) {
    Aluno* aluno = (Aluno*)_aluno;
    float* media = (float*)_media;
    if (aluno->media == *media) {
        return 1;
    }
    else {
        return 0;
    }
}

void imprimeMenuPrincipal(){
    printf("\tMenu principal\n");
    printf("1. Inserir um aluno na colecao\n");
    printf("2. Remover um aluno da colecao\n");
    printf("3. Consultar um aluno na colecao\n");
    printf("4. Listar os alunos da colecao\n");
    printf("5. Destruir a colecao aluno\n");
    printf("6. Esvaziar a colecao aluno\n");
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
    printf("\t--Sistema de alunos--\n");

    DLList *lista = dllCreate();

    if(lista == NULL){
        printf("Infelizmente a colecao não pode ser alocada :(\n");
    } else{
        printf("Colecao alocado com sucesso!\n");
    }
    
    int rodando = 1;
    while(rodando){
        imprimeMenuPrincipal();
        scanf("%d",&menu);
        Aluno *aluno;
        Aluno* auxC;
        int resultado_da_operacao;
        switch (menu) {
			case 1:
                aluno = (Aluno*)malloc(sizeof(Aluno));
                printf("Informe o nome, idade e media do aluno? ");
                scanf("%s %d %f", aluno->nome, &aluno->idade, &aluno->media);

                if(aluno == NULL){
                    printf("Erro ao cadastrar o aluno");
                } else {
                    if(dllInsertAsFirst(lista, (void*)aluno)){
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
                void* alunoRemov;
                printf("Opção desejada\n");
                scanf("%d", &menuRemov);

                switch(menuRemov){
                    case 1:
                        printf("Nome a remover:\n");
                        scanf("%s", nomeRemov);
                        alunoRemov = dllRemoveSpec(lista, &nomeRemov, cmpPorNome);
                        auxC = (Aluno*)alunoRemov;
                        if(alunoRemov){
                            printf("\nO aluno: %s foi removido\n\n", auxC->nome);
                        } else {
                            printf("\nErro ao remover o aluno\n\n");
                        }
                        break;
                    case 2:
                        printf("Idade a remover\n");
                        scanf("%d", &idadeRemov);
                        alunoRemov = dllRemoveSpec(lista, &idadeRemov, cmpPorIdade);
                        auxC = (Aluno*)alunoRemov;
                        if(alunoRemov){
                            printf("\nO aluno: %s foi removido\n\n", auxC->nome);
                        } else {
                            printf("\nErro ao remover o aluno\n\n");
                        }
                        break;
                    
                    case 3:
                        printf("Media a remover:\n");
                        scanf("%f", &mediaRemov);
                        alunoRemov = dllRemoveSpec(lista, &mediaRemov, cmpPorMedia);
                        auxC = (Aluno*)alunoRemov;
                        if(alunoRemov){
                            printf("\nO aluno: %s foi removido\n\n", auxC->nome);
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
                void* alunoConsult;
                printf("Opção desejada\n");
                scanf("%d", &menuConsult);

                switch(menuConsult){
                    case 1:
                        printf("Consultar nome:\n");
                        scanf("%s", nomeRemov);
                        alunoConsult = dllQuery(lista, &nomeRemov, cmpPorNome);
                        auxC = (Aluno*)alunoConsult;
                        if(alunoConsult){
                            printf("\nO aluno: %s esta na colecao\n\n", auxC->nome);
                        } else {
                            printf("\nO aluno não esta na colecao\n\n");
                        }
                        break;
                    case 2:
                        printf("Consultar idade\n");
                        scanf("%d", &idadeRemov);
                        alunoConsult = dllQuery(lista, &idadeRemov, cmpPorIdade);
                        auxC = (Aluno*)alunoConsult;
                        if(alunoConsult){
                            printf("\nO aluno: %s esta na colecao\n\n", auxC->nome);
                        } else {
                            printf("\nO aluno não esta na colecao\n\n");
                        }
                        break;
                    
                    case 3:
                        printf("Consultar media:\n");
                        scanf("%f", &mediaRemov);
                        alunoConsult = dllQuery(lista, &mediaRemov, cmpPorMedia);
                        auxC = (Aluno*)alunoConsult;
                        if(alunoConsult){
                            printf("\nO aluno: %s esta na colecao\n\n", auxC->nome);
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
                auxC = (Aluno*)dllGetFirst(lista);
                if (auxC == NULL){
                    printf("\nColecao esta vazia\n\n");
                } else {
                    int i = 1;
                    printf("\t--Colecao aluno\n");
                    do{
                        printf("%d.Aluno\nNome: %s\nIdade: %d\nMedia: %.2f\n", i, auxC->nome, auxC->idade, auxC->media);
                        auxC = dllGetNext(lista);
                        i++;
                    } while (auxC != NULL);
                }
                

				break;
            case 5:
                printf("Destruindo a colecao, saindo do programa...\n");
                
                resultado_da_operacao = dllDestroy(lista);
                if(resultado_da_operacao){
                    printf("Colecao destruido com sucesso, finalizando o programa...\n");
                    rodando = 0;
                } else{
                    printf("Erro ao destruir a colecao, talvez ainda tenha itens no cofo\n");
                }
                break;

            case 6:
                printf("Esvaziando a colecao...\n");

                resultado_da_operacao = dllEsvazia(lista);
                if(resultado_da_operacao){
                    printf("Colecao esvaziada com sucessa\n");
                } else{
                    printf("Erro ao esvaziar a colecao\n");
                }
                break;
			default:
				printf("\nOpcao invalida!\n\n");
				break;
			}

    }

    exit(0);

}