#include "order.h"
#include <stdio.h>

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

void insectionSort(int v[], int size){
	int i, j, t, qtdComp = 0, qtdTroca = 0;
	for (i = 1; i < size; i++){
		t = v[i];
		j = i - 1;
			while(j >= 0 && v[j] > t){
				v[j+1] = v[j];
				j--;				
			}
		v[j+1] = t;
	}
}



void bubbleSort(int v[], int size){
	int t, i, j;
	for(i = 0; i < size; i++){
		for(j = size-1; j > 0; j--){
			if (v[j] < v[j-1]){
				t = v[j];
				v[j] = v[j-1];
				v[j-1] = t;
			}
		}
	}
}

void shellSort(){
}
void mergeSort(){

}
void quikSort(){

}

void radixSort(){

}

void printVetor(int v[], int size){
	int i;
	printf("Vetor: \n");
	for(i = 0; i < size; i++){
		printf("%d ", v[i]);
	} 
		
}