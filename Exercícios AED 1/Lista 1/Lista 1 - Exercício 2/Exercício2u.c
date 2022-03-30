#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* adicionar(char* str);
char* remover(char* str);

int main(){
int opcao;
char *nome = calloc(1,sizeof(char));
       
     for (;;){
            printf("\n");
            printf(" 1 - Adicionar nome\n");
            printf(" 2 - Remover nome\n");
            printf(" 3 - Listar\n");
            printf(" 4 - Sair\n");
            printf("Digite uma opcao: ");
            scanf("%d", &opcao);
            getchar();

    switch (opcao)
    {
    case 1:              
                nome = adicionar(nome);                                               
        break;

    case 2:    
                remover(nome);         
        break;

    case 3:     
                printf("\n*Nomes listados*\n%s\n", nome);               
        break;
    case 4:
            exit(0);
        break;
    }
    
}
return 0;

}
char* adicionar(char* str){
    int buffer_size, str_size;
    char divisao[] = "$", nomealuno[25];
    printf("Insira o nome: ");
    scanf("%s", nomealuno);
    getc(stdin);
    strcat(nomealuno, divisao);                                           
    buffer_size = strlen(nomealuno);
    str_size = strlen(str);
    str = (char*)realloc(str, (buffer_size+str_size)*sizeof(char)+sizeof(char)); 
    strcat(str, nomealuno);
    return str;
}

char* remover(char* str){
    int tamanho, i;
    char removenome[25], divisao[] = "$", *start, *end, *test;

    inicio: 
    printf("Insira o nome a ser removido da lista: ");
    scanf("%s", removenome);
    getc(stdin);
    strcat(removenome, divisao);
    test = strstr(str, removenome);

    if(test !=  NULL){ 
        tamanho = strlen(removenome);
        start = strstr(str, removenome);            
        end = start;                            
            for(i=0; i<tamanho; i++)            
            end++;  
        memmove(start, end, strlen(end)+1);     
        tamanho = strlen(str);
        str = (char*)realloc(str, tamanho*sizeof(char)+sizeof(char)); 
            return str; 
        }
        else{
            printf("Nome nao encontrado digite novamente.\n");
            goto inicio;
       }
}