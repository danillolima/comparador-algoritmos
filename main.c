#include <stdlib.h>
#include <stdio.h>
#include <iup.h>
#include "order.h"

int main(int argc, char **argv){


  int v[] = {2000, 30, 5, 6, 8, 4, 34, 45, 5, 45, 453};
  //selectionSort(v, 11);
  //insectionSort(v, 11);
  bubbleSort(v, 11);
  //shellSort(v, 11);
  //mergeSort(v, 11);
  //quickSort(v, 11);
  //radixSort(v, 11);
  printVetor(v, 11);

  
	Ihandle *dlg, *multitext, *hbox, *checkb[7], *label, *fill;
  
	IupOpen(&argc, &argv);
	IupSetLanguage("PORTUGUESE");
	IupSetGlobal("UTF8MODE", "yes");
	
	checkb[0] = IupToggle("Insection Sort", NULL);
	checkb[1] = IupToggle("Bubble Sort", NULL);
	checkb[2] = IupToggle("Shell Sort", NULL);
	checkb[3] = IupToggle("Merge Sort", NULL);
	checkb[4] = IupToggle("Quick Sort", NULL);
	checkb[5] = IupToggle("Radix Sort", NULL);
	checkb[6] = IupToggle("Selection Sort", NULL);
	multitext = IupText(NULL);
	label = IupLabel("Selecione os algoritmos: ");
	fill = IupFill();
	hbox = IupHbox(fill,
				   label,
				   checkb[0],
				   checkb[1],
				   checkb[2],
				   checkb[3],
				   checkb[4],
				   checkb[5],
				   checkb[6],
				   fill,
				   NULL);
	IupSetAttribute(hbox, "EXPANDCHILDREN", "yes"); 
	
	IupSetAttribute(multitext, "MULTILINE", "YES");
	IupSetAttribute(multitext, "EXPAND", "NO");
	dlg = IupDialog(hbox);
	
	IupSetAttribute(dlg, "TITLE", "Comparador de Algoritmos de ordenação" );
	IupSetAttribute(dlg, "SIZE", "HALFxHALF");
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
	
    IupSetAttribute(dlg, "USERSIZE", NULL);
    IupMainLoop();
	IupClose();
	return EXIT_SUCCESS;
}
