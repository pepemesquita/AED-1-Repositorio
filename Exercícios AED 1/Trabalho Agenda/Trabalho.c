/*Trabalho e implementação da agenda em C(continuação do exercício 3)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void menu(void *pBuffer);
void add(void *pSentinela, void *pBuffer);
void remover(void *pSentinela, void *pBuffer);
void procurar(void *pSentinela, void *pBuffer);
void tudo(void *pSentinela, void *pBuffer);

//defines para tornar o código mais legível
#define PESSOA_TAM (sizeof(char)*20+sizeof(int)+sizeof(long int)+sizeof(void **)*2) //PESSOA_TAM = nome[20] + idade + telefone + endereço anterior + próximo endereço
#define PROX (sizeof(char)*20+sizeof(int)+sizeof(long int)+sizeof(void **))
#define ANTES (sizeof(char)*20+sizeof(int)+sizeof(long int))
#define PRIMEIRO (sizeof(int)+sizeof(void **))
#define ULTIMO (sizeof(int))
#define NOME (sizeof(void **)+sizeof(int))


int main(){
    setlocale (LC_ALL, "Portuguese"); //Letras e acentos
    void *pBuffer, *pSentinela;
    pSentinela = (void *)calloc(1, (sizeof(int) + sizeof(void **)*2)); //pSentinela = tamanho + último endereço + primeiro endereço
    pBuffer = (void *)calloc(1, sizeof(void **) + sizeof(int)); //pBuffer = ponteiro a ponteiro + escolha

    if(!pSentinela || !pBuffer){
        printf("Erro, não foi possível alocar memória!\n");
        return -1;
    }

    *(int *)pSentinela = 0; //Tamanho = 0
    *(void **)(pSentinela+sizeof(int)) = NULL; //Ultimo endereço = NULL
    *(void **)(pSentinela+PRIMEIRO) = NULL; //Primeiro endereço = NULL
    *(void **)pBuffer = NULL; //Ponteiro pra ponteiro = NULL

    for(;;){
        menu(pBuffer);
        switch(*(int *)(pBuffer+sizeof(void **))){
            case 1:
                add(pSentinela, pBuffer);
                break;
            case 2:
                remover(pSentinela, pBuffer);
                break;
            case 3:
                procurar(pSentinela, pBuffer);
                break;
            case 4:
                tudo(pSentinela, pBuffer);
                break;
            case 5:
                if(*(int *)pSentinela != 0){
                    void *pAux = *(void **)(pSentinela+ULTIMO); //aux = última pessoa
                    do{
                        if(*(int *)pSentinela == 1){
                            free(pAux); //"free" primeira pessoa
                            *(int *)pSentinela -= 1; //tamanho--
                        }else{
                            pAux = *(void **)(pAux+ANTES); //aux = pessoa anterior
                            void *pAux2 = *(void **)(pAux+PROX); //aux2 = próxima pessoa
                            free(pAux2); //"free" a próxima pessoa pra lista continuar
                            
                            *(int *)pSentinela -= 1; //tamanho--
                        }
                    }while(*(int *)pSentinela != 0);
                }//saída do menu
                free(pBuffer);
                free(pSentinela);
                printf ("Saindo...\n");
                exit(0);
                break;
		}
    }
    return 0;
}


void add(void *pSentinela, void *pBuffer){
    void *aux;
    void *pPerson = (void *)malloc(PESSOA_TAM);

    if (!pPerson){
        printf("Erro, não foi possivel alocar memória!\n");
        return;
    }

    //Lê os dados da pessoa
    printf("\n-Endereço da pessoa: %p", pPerson);
    printf("\n-Adicionar nome: "); scanf("%19[^\n]c", (char *)pPerson); getchar();
    printf("-Adicionar idade: "); scanf("%d", &*(int *)(pPerson+sizeof(char)*20));
    printf("-Adicionar telefone: "); scanf("%ld", &*(long int *)(pPerson+sizeof(char)*20+sizeof(int)));

    *(void **)(pPerson+PROX) = NULL; //Próximo endereço da pessoa = NULL;
    *(void **)(pPerson+ANTES) = NULL; //Endereço anterior da pessoa = NULL;

    if(*(int *)pSentinela == 0){
        //Se esta for a primeira pessoa a ser adicionada, o pSentinela receberá o primeiro endereço e o último endereço
        *(void **)(pSentinela+ULTIMO) = pPerson;
        *(void **)(pSentinela+PRIMEIRO) = pPerson;
        
        *(int *)pSentinela += 1; //tamanho++
        return;
    }

    pBuffer = *(void **)(pSentinela+PRIMEIRO); //pBuffer recebe o primeiro endereço
    do{
        if(strcmp((char *)pPerson, (char *)pBuffer) < 0){
            
            *(void **)(pPerson+ANTES) = *(void **)(pBuffer+ANTES); //pessoa atual(anterior) = pessoa anterior
            *(void **)(pPerson+PROX) = pBuffer; //pessoa atual(próxima) = próxima pessoa

            //No caso de a pessoa ser adicionada ao início
            if(*(int *)pSentinela > 1 && *(void **)(pBuffer+ANTES) != NULL){
                aux = *(void **)(pBuffer+ANTES);
                *(void **)(aux+PROX) = pPerson; //pessoa anterior(prox) = pessoa atual
            }
            *(void **)(pBuffer+ANTES) = pPerson; //próxima pessoa(antes) = pessoa atual

            //atualiza o novo primeiro endereço, se necessário
            if(*(void **)(pPerson+ANTES) == NULL){
                *(void **)(pSentinela+PRIMEIRO) = pPerson; //pSentinel recebe o primeiro endereço
            }

            *(int *)pSentinela += 1; //tamanho++
            return;
        }

        //precisa disso, caso contrário haverá falha de segmentação posteriormente
        if(*(void **)(pBuffer+PROX) == NULL){
            break;
        }
        pBuffer = *(void **)(pBuffer+PROX); //recebe o próximo endereço
    }while(pBuffer != NULL);

    //no caso da pessoa está sendo adicionada ao final
    *(void **)(pPerson+ANTES) = pBuffer;
    *(void **)(pBuffer+PROX) = pPerson;
    *(void **)(pSentinela+ULTIMO) = pPerson;

    *(int *)pSentinela += 1; //tamanho++
    return;
}


void remover(void *pSentinela, void *pBuffer){
    void *aux;
    void *auxName = calloc(1, sizeof(char)*20); //aux para ler o nome a ser removido

    //Se não tiver ainda
    if(*(int *)pSentinela == 0){
        printf("\nSem dados ainda!\n");
        return;
    }

    printf("\nNome para remover: "); scanf("%19[^\n]c", (char *)auxName); getchar(); //nome a remover

    pBuffer = *(void **)(pSentinela+PRIMEIRO); 
    do{
        //se encontrar a pessoa certa para remover
        if(strcmp((char *)pBuffer, (char *)auxName) == 0){

            if(*(void **)(pBuffer+ANTES) != NULL){
                aux = *(void **)(pBuffer+ANTES); //aux = pessoa anterior
                *(void **)(aux+PROX) = *(void **)(pBuffer+PROX); //pessoa anterior(prox) = próxima pessoa
            }else{
                *(void **)(pSentinela+PRIMEIRO) = *(void **)(pBuffer+PROX); //atualiza o primeiro endereço se a primeira pessoa estiver sendo removida
            }
            
            if(*(void **)(pBuffer+PROX) != NULL){
                aux = *(void **)(pBuffer+PROX); //aux = próxima pessoa
                *(void **)(aux+ANTES) = *(void **)(pBuffer+ANTES); //próxima pessoa(ANTES) = pessoa anterior
            }else{
                *(void **)(pSentinela+ULTIMO) = *(void **)(pBuffer+ANTES); //atualiza o último endereço se a última pessoa estiver sendo removida
            }
   
            *(int *)pSentinela -= 1; //tamanho--
            free(pBuffer);
            free(auxName);
            return;
        } 
        
        pBuffer = *(void **)(pBuffer+PROX); //recebe o próximo endereço
    }while(pBuffer != NULL);

    printf("\nNome não encontrado!\n");
    free(auxName);
}


void procurar(void *pSentinela, void *pBuffer){
    void *auxName = calloc(1, sizeof(char)*20); //aux para ler o nome da pessoa que está sendo procurada
    if(*(int *)pSentinela == 0){
        printf("\nSem dados ainda!\n");
        return;
    }

    printf("\nNome para buscar: "); scanf("%19[^\n]c", (char *)auxName); getchar(); //lê o nome para procurar

    pBuffer = *(void **)(pSentinela+PRIMEIRO); 
    do{
        if(strcmp((char *)pBuffer, (char *)auxName) == 0){
            //se achar a pessoa certa, lança na tela
            printf("\n> Endereço da pessoa: %p\n", pBuffer);
            printf("--Pessoa: %s, Idade: %d, TElefone: %ld, Próximo endereço: %p, Endereço anterior: %p\n", (char *)pBuffer, *(int *)(pBuffer+sizeof(char)*20), *(long int *)(pBuffer+sizeof(char)*20+sizeof(int)), *(void **)(pBuffer+ANTES), *(void **)(pBuffer+PROX));
            free(auxName);
            return;
        } 
        pBuffer = *(void **)(pBuffer+PROX); //recebe o próximo endereço
    }while(pBuffer != NULL);

    printf("\nNome não encontrado!\n");
    free(auxName);
}


void tudo(void *pSentinela, void *pBuffer){
    //informa que não há ninguém cadastrado caso não haja
    if(*(int *)pSentinela == 0){
        printf("\nLista vazia!\n");
        return;
    }

    //lança na tela todas as pessoas cadastradas
    printf("\nTamanho: %d\n", *(int *)pSentinela);
    pBuffer = *(void **)(pSentinela+PRIMEIRO);
    do{
        printf("\n> Endereço da pessoa: %p\n", pBuffer);
        printf("-Pessoa: %s, Idade: %d, Telefone: %ld, Próximo endereço: %p, Endereço anterior: %p\n", (char *)pBuffer, *(int *)(pBuffer+sizeof(char)*20), *(long int *)(pBuffer+sizeof(char)*20+sizeof(int)), *(void **)(pBuffer+ANTES), *(void **)(pBuffer+PROX));

        pBuffer = *(void **)(pBuffer+PROX); //recebe o próximo endereço
    }while(pBuffer != NULL);
}


void menu(void *pBuffer){
    // O menuzão
    do{
        printf("\n-------------------Menu-------------------\n");
		printf("1) Adicionar pessoa\n");
        printf("2) Remover pessoa\n");
		printf("3) Procurar pessoa\n");
        printf("4) Listar tudo\n");
		printf("5) Sair\n");
		printf("\nEscolha uma opção: "); scanf("%d", &*(int *)(pBuffer+sizeof(void **)));
        printf("-------------------------------------------\n");
	}while(*(int *)(pBuffer+sizeof(void **)) < 1 || *(int *)(pBuffer+sizeof(void **)) > 5);
    getchar();
}