#ifndef ORDER_H
#define ORDER_H
typedef struct infos stats;

struct infos{
	int qtdElements; // Quantidade de Elementos ordenados
	int qtdComp; // Quantidade de comparacoes
	int qtdChan; // Quantidade de trocas 
};



stats selectionSort(int v[], int n);
void insectionSort(int v[], int n);
void bubbleSort(int v[], int n);
void shellSort();
void mergeSort();
void quickSort();
void radixSort();
void printVetor(int v[], int size);
void printStatistics(stats info);
#endif