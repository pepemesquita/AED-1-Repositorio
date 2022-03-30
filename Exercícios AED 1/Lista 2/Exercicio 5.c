#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
   char nome[20]; 
   int idade;
   int altura;
}dados;


void* add (void* nom, int tam){

dados td2, *tmp;

printf("Digite nome da pessoa:");
scanf("%s",&td2.nome);

printf("Digite a altura da pessoa:");
scanf("%d",&td2.altura );

printf("Digite a idade:");
scanf("%d",&td2.idade);

realloc(nom,  (tam*sizeof(dados)+sizeof(dados)));
tmp= nom + (tam*sizeof(dados));
*tmp = td2;
return nom;
}


int listar(void *nom, int tamnom)
{
    setlocale (LC_ALL, "Portuguese");
    dados td2;
    dados *tudo;
    int aux;
    if (tamnom == 0)
    {
        printf("\nNão há nomes cadastrados! \n");
        return (1);
    }

printf("\n Dados das pessoas cadastradas:\n");

for(aux=0;aux<tamnom;aux++){
setlocale (LC_ALL, "Portuguese");
tudo= nom + (aux*sizeof(dados));
td2 = *tudo;    
printf("\n Nome da pessoa: %s \n", td2.nome);
printf("\n Altura: %i cm\n", td2.altura);
printf("\n Idade: %d anos\n", td2.idade);
}
return (0);
}



void* remover(dados* nom, int tam){
    int aux;
    dados td2;
    dados *tudo;
    tudo = nom;
    dados *t2;
   
    printf("Insira o nome a ser removido: ");
        scanf("%s",td2.nome );                      
            for(aux=0; aux<tam; aux++){
                if(strstr(tudo->nome, td2.nome)){
                    t2 = tudo + 1;
                    memmove(tudo, t2, (tam-aux-1)*sizeof(dados));
                    nom = (dados*)realloc(nom, (tam-1)*sizeof(dados)); 
                    printf ("Nome removido!!!\n");
                    goto fim;
                };
                tudo = tudo + 1;
            }
fim:
       
            return nom; 
        }




int tamstr = 0;

int main() 
{
    int opção=1;
    setlocale (LC_ALL, "Portuguese");
    void *pBuffer;
    void *pBuffers = (void *)calloc(1, 1);
    
    
    while(opção != 0)
    {   
        printf("\n***************Menu*****************\n");
        printf("1) Adicionar dados da pessoa \n");
        printf("2) Remover dados\n");
        printf("0) Mostrar pessoas cadastradas e sair\n");
        printf("Digite a opção desejada: ");

        scanf("%d", &opção);
        gets(stdin);

    
        switch (opção)
        {
            case 1:
                pBuffer = add(pBuffers, tamstr);
                tamstr++;
                break;

              

            case 2:
                remover(pBuffers, tamstr);
                tamstr--;
                break;


            case 0:
                printf("Saindo...");
                break;
        }
    }

    listar(pBuffer, tamstr);

    return 0;
}