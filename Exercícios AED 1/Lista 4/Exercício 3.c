/*
    Implementação de uma árvore AVL com números aleatórios
    O programa só pergunta 1 número para o usuário quantos nós (n)
    O programa automaticamente gera n nós em sequência com valor aleatório e vai adicionando na árvore
    Use srand(time(0));
    Ao final, use um código de verificação para validar a árvore e dar ok
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node *add (struct Node *node, int num);
struct Node *rotDireita (struct Node *node);
struct Node *rotEsquerda (struct Node *node);
struct Node *novoNode (int key);
void mostraArvore (struct Node *node);
int max (int a, int b);
int tamanho (struct Node *node);
int FatorB (struct Node *node);
int Verificar (struct Node *node);
void limpNo (struct Node *node);
void limpArvore(struct Node *raiz);
void segCenario();

struct Node{
  int key; 
  struct Node *nóEsq;
  struct Node *nóDir;
  int tamanho;
};


int main(){
    //inicialize a raiz em null
  struct Node *raiz = NULL;
  int resultado, num;

  printf("\nInsira a quantidade de nós que deseja inserir: "); scanf("%d", &resultado);

  srand(time(0));
  for(int i = 0; i < resultado; i++){ //gera nós aleatórios
    num = rand() % 100; //gera números aleatórios
    raiz = add(raiz, num); //insere os números aleatórios
  }
  printf("\n\n");
  mostraArvore(raiz); //imprime a árvore inteira
  printf("\n");

  if(Verificar(raiz) == 0){ //testa a árvore
    printf("Não está ok");
  }
  printf("OK\n\n");

  limpArvore(raiz); //Limpa toda a árvore
  segCenario(); //Roda o segundo cenário

  return 0;
}


struct Node *add(struct Node *node, int num){
  int fb; //Fator de balanceamento

  if(node == NULL){ //simplismente retorna um nó se for o primeiro (raiz) ou alguma folha
    return novoNode(num);
  }

  if(num < node->key){ //insere um nó a esquerda
    node->nóEsq = add(node->nóEsq, num);
  }else{ //ou a direita
    node->nóDir = add(node->nóDir, num);
  }

  node->tamanho = 1 + max(tamanho(node->nóEsq), tamanho(node->nóDir)); //determina o tamanho do novo nó
  
  fb = FatorB(node); //obtem o valor de balanceamento do nó

  if(fb > 1 && num < node->nóEsq->key){ //rotação para a direita
    return rotDireita(node);
  }
  if(fb < -1 && num > node->nóDir->key){ //rotação para a esquerda
    return rotEsquerda(node);
  }
  if(fb > 1 && num > node->nóEsq->key){ //rotação dupla para a adireita 
    node->nóEsq = rotEsquerda(node->nóEsq); //vai dobrar a rotação apenas
    return rotDireita(node);
  }
  if(fb < -1 && num < node->nóDir->key){ //rotação dupla pra esquerda
    node->nóDir = rotDireita(node->nóDir);
    return rotEsquerda(node);
  }

  return node;
}


struct Node *rotDireita(struct Node *node){ //se houver essa situação: (3(2(1)))
  struct Node *auxLeft = node->nóEsq; //então auxLeft = 2
  struct Node *auxRight = auxLeft->nóDir; //e auxRight = NULL

  auxLeft->nóDir = node; //2->nóDir = 3
  node->nóEsq = auxRight; //3->nóEsq = NULL

  //e agora é (2(1)(3))

  node->tamanho = max(tamanho(node->nóEsq), tamanho(node->nóDir)) + 1; //atualiza o tamanho do 3
  auxLeft->tamanho = max(tamanho(auxLeft->nóEsq), tamanho(auxLeft->nóDir)) + 1; //atualiza o tamanho do 2

  return auxLeft; //retorna o 2
}


struct Node *rotEsquerda(struct Node *node){ //se houver essa situação: (3(1(2))) o nó é 1
  struct Node *auxRight = node->nóDir; //então auxRight = 2
  struct Node *auxLeft = auxRight->nóEsq; //e auxLeft = NULL

  auxRight->nóEsq = node; //2->nóEsq = 1
  node->nóDir = auxLeft; //1->nóDir = NULL

  //e agora é (3(2(1)))

  node->tamanho = max(tamanho(node->nóEsq), tamanho(node->nóDir)) + 1; //atualiza o tamanho de 1
  auxRight->tamanho = max(tamanho(auxRight->nóEsq), tamanho(auxRight->nóDir)) + 1; //atualiza o tamanho de 2

  return auxRight; //retorna o 2
}


int Verificar(struct Node *node){
  int fb;

  if(node == NULL){ //se a árvore está vazia, ou é uma folha, então não há nada de errado
    return 1;
    }	
  if(!Verificar(node->nóEsq)){ //checa o nó da esquerda
    return 0;
  }
  if(!Verificar(node->nóDir)){ //checa o nó da direita
    return 0;
  }
  fb = FatorB(node);
  if((fb > 1) || (fb < -1)){ //verifica se está balanceado
    return 0;
  }else{
    return 1;
  } 
}


int tamanho(struct Node *node){ //retorna o tamanho do nó
  if(node == NULL){
    return 0;
  }
  return node->tamanho;
}


int max(int a, int b){
  return (a > b) ? a : b; //se a for maior que b, retorna a. Caso contrário, retorna b
}


int FatorB(struct Node *node){
  if (node == NULL){
    return 0;
  }
  return (tamanho(node->nóEsq) - tamanho(node->nóDir)); //retornar o tamanho do nó esquerdo - tamanho do nó direito
}


struct Node *novoNode(int key){
  struct Node *node = (struct Node *)calloc(1, sizeof(struct Node)); //aloca o nó novo

  node->key = key; 
  node->nóEsq = NULL;
  node->nóDir = NULL;
  node->tamanho = 1;
  return node;
}


void mostraArvore(struct Node *node){ //apenas mostra a árvore
    if(node != NULL){
        printf("(%d", node->key);
        mostraArvore(node->nóEsq);
        mostraArvore(node->nóDir);
        printf(")");
    }
}


void limpNó(struct Node *node){
  if(node != NULL){
    limpNó(node->nóEsq);
    limpNó(node->nóDir);
    free(node); //limpa os nós antes de limpar tudo
  }
}

void limpArvore(struct Node *raiz){ 
  if(raiz != NULL){
    limpNó(raiz);  //limpa a raiz
  }    
}


void segCenario(){
  printf("Primeiro caso:\n");
  struct Node *raiz1 = NULL; 

  raiz1 = add(raiz1, 20);
  raiz1 = add(raiz1, 4);
  raiz1 = add(raiz1, 15);
  mostraArvore(raiz1);
  limpArvore(raiz1);
  
  printf("\nSegundo caso:\n");
  struct Node *raiz2 = NULL;
  
  raiz2 = add(raiz2, 20);
  raiz2 = add(raiz2, 4);
  raiz2 = add(raiz2, 26);
  raiz2 = add(raiz2, 3);
  raiz2 = add(raiz2, 9);
  raiz2 = add(raiz2, 15);
  mostraArvore(raiz2);
  limpArvore(raiz2);

  printf("\n\n");
}