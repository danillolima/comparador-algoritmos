#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "order.h"
/*
	Metodologia: 
		- Incrementar as comparações SE estiver sendo comparado alguma key do vetor
		- Incrementar as trocas se estiver sendo trocado alguma key do vetor
*/
stats selectionSort(int v[], int size){
	stats relSelection;
	int i, j, t, qtdComp = 0, qtdTroca = 0;
	for (i = 0; i < size; i++){
        j = i + 1;
        while(j < size){
			qtdComp++;
			if(v[i] > v[j]){
                qtdTroca++;
                t = v[i];
                v[i] = v[j];
                v[j] = t;
            }
            j++;
        }
    }
	relSelection.qtdElements = size;
	relSelection.qtdComp = qtdComp;
	relSelection.qtdChan = qtdTroca;
	return relSelection;
}

stats insectionSort(int v[], int size){
	int i, j, t, qtdComp = 0, qtdTroca = 0;
	stats relSelection;
	for (i = 1; i < size; i++){
		t = v[i];
		j = i - 1;
		qtdComp++;
			while(j >= 0 && v[j] > t){
				qtdTroca++;
				v[j+1] = v[j];
				j--;				
			}
			qtdTroca++;
		v[j+1] = t;
	}
	relSelection.qtdElements = size;
	relSelection.qtdComp = qtdComp;
	relSelection.qtdChan = qtdTroca;
	return relSelection;
}

stats bubbleSort(int v[], int size){
	int t, i, j, qtdComp = 0, qtdTroca = 0;
	stats relSelection;
	
	for(i = 0; i < size; i++){
		for(j = size-1; j > 0; j--){
			qtdComp++;
			if (v[j] < v[j-1]){
				qtdTroca++;
				t = v[j];
				v[j] = v[j-1];
				v[j-1] = t;
			}
		}
	}
	relSelection.qtdElements = size;
	relSelection.qtdComp = qtdComp;
	relSelection.qtdChan = qtdTroca;
	return relSelection;
}

stats shellSort(int *A, int size){
    int i , j , chave, qtdComp = 0, qtdTroca = 0, h = 1;
	stats relSelection;
    do{
        h = h * 3 + 1;
    }while(h < size);

    do{
        h = h / 3;
        for(i = h + 1; i < size; i++) {
            chave = A[i];
            j = i;
			qtdComp++;
            while (A[j - h] > chave && j >= h) {
                A[j] = A[j - h];
                j = j - h;
				qtdTroca++;
            }
			qtdTroca++;
            A[j] = chave;
        }
    }while(h != 1);
	relSelection.qtdElements = size;
	relSelection.qtdComp = qtdComp;
	relSelection.qtdChan = qtdTroca;
	return relSelection;
}

stats radixSort(int *A, int size) {
    int i, *b, maior = A[0], exp = 1, qtdComp = 0, qtdTroca = 0;
	stats relSelection;
    b = (int *) calloc(size, sizeof(int));

    for (i = 0; i < size; i++) {
		qtdComp++;
        if (A[i] > maior)
    	    maior = A[i];
    }
	
    while (maior/exp > 0) {
		qtdComp++;
        int auxiliar[10] = {0};
    	for (i = 0; i < size; i++)
    	    auxiliar[(A[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    auxiliar[i] += auxiliar[i - 1];
    	for (i = size - 1; i >= 0; i--){
    	    b[--auxiliar[(A[i] / exp) % 10]] = A[i];
			qtdTroca++;
		}
    	for (i = 0; i < size; i++){
    	    A[i] = b[i];
			qtdTroca++;
		}	
    	exp *= 10;
    }
    free(b);
	relSelection.qtdElements = size;
	relSelection.qtdComp = qtdComp;
	relSelection.qtdChan = qtdTroca;
	return relSelection;
}

/* Recursivos */
void mergeSort(int *A, int p, int r, stats *relSelection){
	if(p < r){
       int q = (p + r-1)/2;
       mergeSort(A, p, q, relSelection);
       mergeSort(A, q + 1, r, relSelection);
       merge(A, p, q, r, relSelection);
    }
}

void quickSort(int *A, int l, int r, stats *relSelection){
    int j, k;
    if(l < r){
        j = partition(A, l, r, relSelection);
        quickSort(A, l, j-1, relSelection);
        quickSort(A, j+1, r, relSelection);
    }
}

/* Auxiliaries functions */
int partition(int *A, int l, int r, stats *relSelection){
    int pivot, i, j, t;
    pivot = A[l];
    i = l;
    j = r + 1;
    while(1){
        do{
            ++i;
        } while(A[i] <= pivot && i <= r);
		relSelection->qtdComp++;
        do{
            --j;
        } while(A[j] > pivot);
		relSelection->qtdComp++;
        if(i >= j)
            break;
		
		relSelection->qtdChan++;
        t = A[i];
        A[i] = A[j];
        A[j] = t;
    }
	relSelection->qtdChan++;
    t = A[l];
    A[l] = A[j];
    A[j] = t;
	return j;
}

void merge(int *A, int p, int q, int r, stats *relSelection){
    int n1 = p;
	int n2 = q + 1;
	int i = 0, n = r - p + 1;
	int *vetor = (int*)malloc(n * sizeof(int));
	
    while(n1 <= q && n2 <= r){
		relSelection->qtdComp++;
        if(A[n1] < A[n2]) {
			relSelection->qtdChan++;
            vetor[i] = A[n1];
            n1++;
        } else {
			relSelection->qtdChan++;
            vetor[i] = A[n2];
            n2++;
        }
        i++;
    }

    while(n1 <= q){
		relSelection->qtdChan++;
        vetor[i] = A[n1];
        i++;
        n1++;
    }

    while(n2 <= r) {
		relSelection->qtdChan++;
        vetor[i] = A[n2];
        i++;
        n2++;
    }

    for(i = p; i <= r; i++){
		relSelection->qtdChan++;
        A[i] = vetor[i - p];
    }   
    free(vetor); 
}

void printVetor(int v[], int size){
	int i;
	printf("Vetor: \n");
	for(i = 0; i < size; i++){
		printf("%d ", v[i]);
	} 
}