/*O programa deve armazenar no máximo 10 pessoas.
Todas as variáveis que forem usadas no programa deve ser ponteiros. 
A única exceção é o item 1 que deve ser uma variável global Pessoa pessoas[10].
1.Os ponteiros devem apontar para um buffer chamado pBufferonde os dados devem ser armazenados. 
Por exemplo, um contador para um for deve ser um ponteiro para int e o int vai ficar armazenado dentro de 
pBuffer. 
2.Não pode usar struct dentro do pBuffer*/

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
char nome[10];
int idade;
int celular;
} Pessoa;

Pessoa pessoas[10];

int *add(void *pBuffer);
int listar(void *pBuffer);
int *menu(void *pBuffer);

int *menu(void *pBuffer){
	setlocale(LC_ALL, "Portuguese");
    do {
        printf("\n***********Agenda********\n\n");
		printf("1) Adicionar cadastro\n");
		printf("2) Listar\n");
		printf("3) Sair\n");
        printf("Digite a opção desejada: ");
		scanf("%d", &*(int *)(pBuffer + sizeof(int) + sizeof(char)));
	} while (*(int *)(pBuffer + sizeof(int) + sizeof(char)) <= 0 || *(int *)(pBuffer + sizeof(int) + sizeof(char)) > 3);

	getchar();

	return pBuffer;
}

int main(){
    setlocale (LC_ALL, "Portuguese");
    void *pBuffer = malloc((sizeof(int) * 2) + sizeof(char));
    if (pBuffer == NULL) {
        printf("\nNão foi possível alocar\n");
        return 0;
    }

*(int*)pBuffer = 0; 
*(char*)(pBuffer + sizeof(int)) = '/'; 
*(int*)(pBuffer + sizeof(int) + sizeof(char)) = 0;
    for(;;) {
		pBuffer = menu(pBuffer);
		switch (*(int *)(pBuffer + sizeof(int) + sizeof(char))) 
        {
		    case 1:
			pBuffer = add(pBuffer);
		    break;

            case 2:
			listar(pBuffer);
			break;

		    case 3:
            printf ("Saindo...\n");
            exit (0);
		}
	} 

    free(pBuffer);
	return 0;
}


int *add(void *pBuffer){
    setlocale (LC_ALL, "Portuguese");
    if(*(int *)pBuffer < 10) 
    {
        printf("Digite o nome da pessoa: ");
        scanf("%s", &pessoas[*(int *)pBuffer].nome);

        printf("Digite a idade da pessoa: ");
        scanf("%d", &pessoas[*(int *)pBuffer].idade);

        printf("Digite o celular da pessoa: ");
        scanf("%d", &pessoas[*(int *)pBuffer].celular);
        *(int *)pBuffer = *(int *)pBuffer + 1;

        return pBuffer;
    } else 
    {
        printf("O numero máximo de pessoas cadastrados foi atingido, remova alguma e tente novamente.");
        return NULL;
    }
}

int listar(void *pBuffer){
    setlocale (LC_ALL, "Portuguese");
    if (*(int *)pBuffer != 0)
    {
        printf("*************Lista*************\n");
        for(*(int *)(pBuffer + sizeof(int) + sizeof(char)) = 0; 
            *(int *)(pBuffer + sizeof(int) + sizeof(char)) < *(int *)pBuffer;
            *(int *)(pBuffer + sizeof(int) + sizeof(char)) = *(int *)(pBuffer + sizeof(int) + sizeof(char)) + 1) 
        {
            printf("\nCadastro %d:  Nome: %s - Idade: %d anos - Celular: %d \n", *(int *)(pBuffer + sizeof(int) + sizeof(char)) + 1, 
            pessoas[*(int *)(pBuffer + sizeof(int) + sizeof(char))].nome, 
            pessoas[*(int *)(pBuffer + sizeof(int) + sizeof(char))].idade,
            pessoas[*(int *)(pBuffer + sizeof(int) + sizeof(char))].celular);
        }
    } else 
    {
        printf("\n Nenhuma pessoa cadastrada\n");
        return 0;
    }

    return 0;
}

//Pedro Henrique Lima de Mesquita, 20200862