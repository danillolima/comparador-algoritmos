#ifndef ORDER_H
#define ORDER_H
typedef struct infos stats;

struct infos{
	int qtdElements; // Quantidade de Elementos ordenados
	long long int qtdComp; // Quantidade de comparacoes
	long long int qtdChan; // Quantidade de trocas  
	long time;
};

typedef struct v array;
struct v{
	int *v;
	int n;
};

stats selectionSort(int *, int);
stats insectionSort(int *, int);
stats bubbleSort(int *, int);
stats shellSort(int *, int);
stats radixSort(int *, int);
void mergeSort(int *, int p, int r, stats *);
void quickSort(int *, int l, int r, stats *);
int partition(int *, int, int, stats *);
void merge(int *, int, int, int, stats *);
void printVetor(int *, int);
void printStatistics(stats info);
/* fazer */
int * randomNumbers(int);

#endif