

/*Exercício:
1- Implementar os algoritmos de ordenação Insertion Sort, Selection Sort, Quick Sort e Merge Sort.
2- O programa deve solicitar o tamanho do vetor de números (n) que será ordenado
3- O programa deve preencher um vetor de tamanho n com números aleatórios. Usar srand(time(NULL)); no inicio do programa.
4- Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto.
5- Calcular quanto tempo cada algoritmo de ordenação levou para terminar*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *array, int size);
void selectionSort(int *array, int size);
void quickSort(int *array, int primeiro, int ultimo);
void mergeSort(int *array, int começo, int fim);
void verificar(int *array, int size);
void printArray(int *array, int size);
void troca(int *a, int *b);
double tempo(struct timeval começo, struct timeval fim);


int main(){

	int *arrayInsertion, *arraySelection, *arrayQuick, *arrayMerge, size; //é necessário criar vários arrays, caso contrário, irá sobrescrever
    struct timeval começo, fim; //usado para medir o tempo

	printf("\nInsira o tamanho do array: "); scanf("%d", &size);
	arrayInsertion = (int *)calloc(size, sizeof(int)); //aloca memo pra cada array
    arraySelection = (int *)calloc(size, sizeof(int));
    arrayQuick = (int *)calloc(size, sizeof(int));
    arrayMerge = (int *)calloc(size, sizeof(int));

	srand(time(NULL));
	for (int i = 0; i < size; i++){ //gera os números aleatórios
		arrayInsertion[i] = rand() % 100;
        arraySelection[i] = arrayInsertion[i];
        arrayQuick[i] = arrayInsertion[i];
        arrayMerge[i] = arrayInsertion[i];
	}

	printf("\nArray inicial: "); 
    printArray(arrayInsertion, size); //mostra na tela o array gerado aleatoriamente
    verificar(arrayInsertion, size); //verifica o array criado

    printf("\n\n\nInsertion Sort: ");
    gettimeofday(&começo, 0); //obtem a hora do inicio do insertion
	insertionSort(arrayInsertion, size); //sort
    gettimeofday(&fim, 0); //obtem a hora do fim do insertion
    printArray(arrayInsertion, size);
    verificar(arrayInsertion, size);
    printf("\nTempo de execução: %.6f", tempo(começo, fim)); //mostra na tela o tempo que levou para ser executado 
    free(arrayInsertion); //libera memo do array

    printf("\n\nSelection Sort: "); 
    gettimeofday(&começo, 0);
	selectionSort(arraySelection, size);
    gettimeofday(&fim, 0);
    printArray(arraySelection, size);
    verificar(arraySelection, size);
    printf("\nTempo de execução: %.6f", tempo(começo, fim));
    free(arraySelection);

    printf("\n\nQuick Sort: "); 
    gettimeofday(&começo, 0);
	quickSort(arrayQuick, 0, size-1);
    gettimeofday(&fim, 0);
    printArray(arrayQuick, size);
    verificar(arrayQuick, size);
    printf("\nTempo de execução %.6f", tempo(começo, fim));
    free(arrayQuick);

    printf("\n\nMerge Sort: "); 
    gettimeofday(&começo, 0);
	mergeSort(arrayMerge, 0, size-1);
    gettimeofday(&fim, 0);
    printArray(arrayMerge, size);
    verificar(arrayMerge, size);
    printf("\nTempo de execução: %.6f", tempo(começo, fim));
    free(arrayMerge);

    printf("\n\n");
	return 0;
}


void verificar(int *array, int size){ //passa pelos arrays verificando se estão ordenados
	if(size > 1){
        for(int i = 1; i < size; i++){
            if(array[i-1] > array[i]){ //compara o elemento atual com o próximo elemento
                printf("\nNão está em ordem.");
                return;
            }
        }
    }
    printf("\nEstá em ordem.");
}


void printArray(int *array, int size){
    for(int i= 0; i < size; i++){
        printf("%d ", array[i]); //mostra na tela todos os números gerados
    }      
}


void troca(int *a, int *b){ // troca o "a" com o "b", usado no selection sort e quick sort
    int temp = *a;
    *a = *b;
    *b = temp;
}


double tempo(struct timeval começo, struct timeval fim){ //obtém o tempo total de execução com time.h e gettimeofday
	long seconds = fim.tv_sec - começo.tv_sec;
	long microseconds = fim.tv_usec - começo.tv_usec;
	return seconds + microseconds * 1e-6;
}


void insertionSort(int *array, int size){ // pior caso: O(n^2) / no melhor caso: O(n)
	int aux, j;

	for(int i = 1; i < size; i++){ //suponha que o conteúdo do array é 2 3 1 na primeira iteração
		aux = array[i]; //obtém o número 3 na primeira iteração, e então o número 1 na segunda iteração
        j = i - 1; //obtém o número 2 na primeira iteração, e o número 3 na segunda iteração
        
        while((j >= 0) && (aux < array[j])){ //primeira iteração 3 < 2 == false, segunda iteração 1 < 3 == true, terceira iteração 1 < 2 == true
            array[j+1] = array[j]; //o 3 passa pra frente, e agora fica 2 3 3, na segunda iteração o 2 passa pra frente, então fica 2 2 3
            j--; //agora aponta para o elemento anterior, o número 2, e na segunda iteração não vai apontar para ninguém
        }
        array[j+1] = aux; //agora o array recebe o número que estava no aux e assim o array ficará como 1 2 3
	}
}


void selectionSort(int *array, int size){ //pior caso: O(n^2)      melhor caso: O(n^2)
    //sempre precisa ir até o final do vetor para ter certeza que o elemento que está sendo analisado é o menor
	int minIndice, j;

    for(int i = 0; i < size-1; i++){ //vamos supor que o conteúdo do array é 2 3 1
        minIndice = i; //minIndice = 2, minIndice = 3
        for(j = i+1; j < size; j++){ //j = 3, j = 1 / j = 2
            if(array[j] < array[minIndice]){ //3 < 2 == false, 1 < 2 == true / 2 < 3 == true
                minIndice = j; //atualiza o minIndice com o menor elemento encontrado
            }
        }
        troca(&array[minIndice], &array[i]); //1 e 2 trocam as posições, fica 1 3 2 / trocam as posições 2 e 3, e fica 1 2 3
    }
}


void quickSort(int *array, int primeiro, int ultimo){ 
    //pior caso: O(n^2) - o pivô é sempre menor ou maior que todos os outros
    //melhor caso: O(n log(n)) - o pivô sempre estrá no centro

    if(primeiro < ultimo){ //vamos supor que o conteúdo do array é 2 4 1 3, 0 < 3 == true / 2 < 3 == true
        int pivo = primeiro; //o pivô vai ser o primeiro elemento, e nesse caso, o número 2 
        int i = primeiro; 
        int j = ultimo;

        while(i < j){ //0 < 3 == true / 1 < 2 == true / 2 < 3 == true
            while(array[i] <= array[pivo] && i < ultimo){ //2 <= 2 == true, 4 <= 2 == false / 1 <= 2 == true, 4 <= 2 == false / 4 <= 4 AND 2 < 3, 3 < 3
                i++;
            }
            while(array[j] > array[pivo]){ //3 > 2 == true, 1 > 2 == false / 4 > 2 == true, 1 > 2 == false / 3 > 4 == false
                j--;
            }
            if(i < j){ //1 < 2 == true / 2 < 1 == false / 3 < 3 == false
                troca(&array[i], &array[j]); //troca o 4 e 1, e então o array fica 2 1 4 3
            }
        }
        troca(&array[pivo], &array[j]); //troca o 2 e 1, e então o array fica 1 2 4 3 / troca o 4 e 3, e o array fica 1 2 3 4
        quickSort(array, primeiro, j-1); 
        quickSort(array, j+1, ultimo); 
    }
}


void mergeSort(int *array, int começo, int fim){ 
    
    if(começo < fim){ 
        int meio = começo + (fim - começo) / 2; 
        
        mergeSort(array, começo, meio); 
        mergeSort(array, meio + 1, fim); 
        
        merge(array, começo, meio, fim); 
    }
}


void merge(int *array, int começo, int meio, int fim){ 
    int i, j, k;
    
    int quantia1 = meio - começo + 1; 
    int quantia2 = fim - meio; 
    int metade1[quantia1], metade2[quantia2]; 

    for(int i = 0; i < quantia1; i++)
        metade1[i] = array[começo+i]; 
    for(int j = 0; j < quantia2; j++)
        metade2[j] = array[meio+1+j]; 

   
    i = 0;
    j = 0;
    k = começo;

    while(i < quantia1 && j < quantia2){ 
        if(metade1[i] <= metade2[j]){ 
            array[k] = metade1[i]; 
            i++;
        }else{
            array[k] = metade2[j]; 
            j++;
        }
        k++; 
    }

    while(i < quantia1){ 
        array[k] = metade1[i]; 
        i++; k++;
    }
    while(j < quantia2){ 
        array[k] = metade2[j];
        j++; k++;
    }
}