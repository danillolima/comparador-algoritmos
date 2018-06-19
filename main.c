#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include <iup.h>
#include "iupcontrols.h"
#include "iup_plot.h"

#include <cd.h>
#include <cdiup.h>

#include "order.h"


array getNumbers(Ihandle *multitext);
static int start(Ihandle *self);
void addPoints(Ihandle** plot, stats infos, char* type);
void copyKeys(int a[], int b[], int start, int end);
int * copyVetor(int v[], int size);

int main(int argc, char **argv){
	//int v[] = {2000, 30, 5, 6, 8, 4, 34, 45, 5, 45, 453};
	//selectionSort(v, 11);
	//insectionSort(v, 11);
	//bubbleSort(v, 11);
	//shellSort(v, 11);
	//mergeSort(v, 11);
	//quickSort(v, 11);
	//radixSort(v, 11);
	//printVetor(v, 11);
	Ihandle *dlg, *multitext, *hbox, *checkb[7], *label, *fill, *f1, *f2, *options, *right, *buttons, *radio, *tempText, *exec, *dados;
	IupOpen(&argc, &argv);
	IupControlsOpen();
	IupPlotOpen();
	IupSetLanguage("PORTUGUESE");
	IupSetGlobal("UTF8MODE", "ON");
	checkb[0] = IupToggle("Insection Sort", NULL);
	checkb[1] = IupToggle("Bubble Sort", NULL);
	checkb[2] = IupToggle("Shell Sort", NULL);
	checkb[3] = IupToggle("Merge Sort", NULL);
	checkb[4] = IupToggle("Quick Sort", NULL);
	checkb[5] = IupToggle("Radix Sort", NULL);
	checkb[6] = IupToggle("Selection Sort", NULL);
	multitext = IupText(NULL);
	IupSetHandle("insec", checkb[0]);
	IupSetHandle("bubbl", checkb[1]);
	IupSetHandle("shell", checkb[2]);
	IupSetHandle("merge", checkb[3]);
	IupSetHandle("quick", checkb[4]);
	IupSetHandle("radix", checkb[5]);
	IupSetHandle("selec", checkb[6]);
	IupSetHandle("texto", multitext);
	fill = IupFill();
	buttons = IupFrame(IupHbox(
								IupButton("Gerar numeros", NULL),
								exec = IupButton("Executar", NULL),
								NULL
								));											
	IupSetCallback(exec, "ACTION", (Icallback)start);
	radio =  IupRadio(IupVbox(
				IupToggle("Ordenados", NULL),
				IupToggle("Semi ordenados", NULL),
				IupToggle("Aleatórios", NULL), NULL
				));
	tempText = IupText(NULL);
	IupSetAttribute(tempText, "MASK", "[0-9]*");
	IupSetAttribute(tempText, "SPIN", "ON");
	options = IupVbox(
				   IupLabel("Selecione os algoritmos: "),
				   checkb[0],
				   checkb[1],
				   checkb[2],
				   checkb[3],
				   checkb[4],
				   checkb[5],
				   checkb[6],	   
				   IupLabel("Gerar números(opcional):"),
				   tempText,
				   radio,
				   IupFill(),
				   buttons, NULL);
	IupSetAttribute(options, "BORDER", "NO");	
	IupSetAttribute(multitext, "MULTILINE", "YES");
	IupSetAttribute(multitext, "EXPAND", "YES");
	right = IupVbox(IupLabel("Números inteiros separados por espaço ou virgula:"), multitext,  NULL);
	IupSetAttribute(right, "TABTITLE", "Entrada");
	right = IupTabs(right, NULL);
	IupSetHandle("tabsR", right);
    //IupSetCallback(multitext, "ACTION", (Icallback)getNumbers);
	f1 = IupFrame(options);
	f2 = IupFrame(right);
	hbox = IupHbox(f1, f2, NULL);
	dlg = IupDialog(IupVbox(IupBackgroundBox(IupFrame(hbox)), NULL));	
	IupSetAttribute(dlg, "TITLE", "Comparador de Algoritmos de Ordenação" );
	IupSetAttribute(dlg, "SIZE", "HALFxHALF");
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupSetAttribute(dlg, "USERSIZE", NULL);
    IupMainLoop();
	IupClose();
	return EXIT_SUCCESS;
}

static int start(Ihandle *self){
	Ihandle *checkb[7], *texto, *tabs, *aux, *grafico[3], *vboxG[3], *tabsI;
	array numeros;
	int *nAux;
	clock_t start, end;
	/*
		Ponteiro para gráfico
		- grafico[0] -> Ponteiro com número de comparaçoes
		- grafico[1] -> Ponteiro com número de trocas
	*/
	
	grafico[0] = IupPlot(); 
	grafico[1] = IupPlot();
	grafico[2] = IupPlot();
	
	
	IupSetAttribute(grafico[0], "TITLE", "Resultado: Comparações por algortimo");
	IupSetAttribute(grafico[0], "FONT", "Helvetica, 10");
	IupSetAttribute(grafico[0], "LEGENDSHOW", "YES");
	IupSetAttribute(grafico[0], "AXS_XLABEL", "Tamanho da entrada(N)");
	IupSetAttribute(grafico[0], "AXS_YLABEL", "Quantidade de Comparações");
	IupSetAttribute(grafico[0], "AXS_XCROSSORIGIN", "Yes");
	IupSetAttribute(grafico[0], "AXS_YCROSSORIGIN", "Yes");
	IupSetAttribute(grafico[0], "MARGINTOP", "40");
    IupSetAttribute(grafico[0], "MARGINLEFT", "100");
    IupSetAttribute(grafico[0], "MARGINBOTTOM", "50");
    IupSetAttribute(grafico[0], "TITLEFONTSIZE", "16");
	
	IupSetAttribute(grafico[1], "TITLE", "Resultado: Trocas por algortimo");
	IupSetAttribute(grafico[1], "FONT", "Helvetica, 10");
	IupSetAttribute(grafico[1], "LEGENDSHOW", "YES");
	IupSetAttribute(grafico[1], "AXS_XLABEL", "Tamanho da entrada(N)");
	IupSetAttribute(grafico[1], "AXS_YLABEL", "Quantidade de Trocas");
	IupSetAttribute(grafico[1], "AXS_XCROSSORIGIN", "Yes");
	IupSetAttribute(grafico[1], "AXS_YCROSSORIGIN", "Yes");
	IupSetAttribute(grafico[1], "MARGINTOP", "40");
    IupSetAttribute(grafico[1], "MARGINLEFT", "100");
    IupSetAttribute(grafico[1], "MARGINBOTTOM", "50");
    IupSetAttribute(grafico[1], "TITLEFONTSIZE", "16");
	
	IupSetAttribute(grafico[2], "TITLE", "Resultado: Tempo por algoritimo");
	IupSetAttribute(grafico[2], "FONT", "Helvetica, 9");
	IupSetAttribute(grafico[2], "LEGENDSHOW", "YES");
	IupSetAttribute(grafico[2], "AXS_XLABEL", "Tamanho da entrada(N)");
	IupSetAttribute(grafico[2], "AXS_YLABEL", "Tempo de máquina");
	IupSetAttribute(grafico[2], "AXS_XCROSSORIGIN", "Yes");
	IupSetAttribute(grafico[2], "AXS_YCROSSORIGIN", "Yes");
	IupSetAttribute(grafico[2], "MARGINTOP", "40");
    IupSetAttribute(grafico[2], "MARGINLEFT", "100");
    IupSetAttribute(grafico[2], "MARGINBOTTOM", "50");
    IupSetAttribute(grafico[2], "TITLEFONTSIZE", "16");
	
	tabs = IupGetHandle("tabsR");
	texto = IupGetHandle("texto");
	/* 
		Pego o Ihandle* de cada checkbox, acho que isso pode ser mais custoso. 
	*/
	checkb[0] = IupGetHandle("insec");
	checkb[1] = IupGetHandle("bubbl");
	checkb[2] = IupGetHandle("shell");
	checkb[3] = IupGetHandle("merge");
	checkb[4] = IupGetHandle("quick");
	checkb[5] = IupGetHandle("radix");
	checkb[6] = IupGetHandle("selec");
	
	numeros = getNumbers(texto);
	nAux = copyVetor(numeros.v, numeros.n);
	/*
		Esses if`s verificarão se o metódo foi selecionado e adicionara os pontos deles no gráfico
	*/
	if(strcmp(IupGetAttribute(checkb[0], "VALUE"), "ON") == 0){
		stats infosInsection;
		start = clock();
		infosInsection  = insectionSort(nAux, numeros.n);
		end = clock();
		infosInsection.time = ((double) (end - start)) / CLK_TCK;
		addPoints(grafico, infosInsection, "Insection Sort");
		copyKeys(numeros.v, nAux, 0, numeros.n);
	}
	if(strcmp(IupGetAttribute(checkb[1], "VALUE"), "ON")  == 0){
		stats infosBubble;
		start = clock();
		infosBubble = bubbleSort(nAux, numeros.n);
		end = clock();
		infosBubble.time = ((double) (end - start)) / CLK_TCK;
		addPoints(grafico, infosBubble, "Bubble Sort");
		copyKeys(numeros.v, nAux, 0, numeros.n);	
	}
	if(strcmp(IupGetAttribute(checkb[2], "VALUE"), "ON") == 0){
		stats infosShell;
		start = clock();
		infosShell = shellSort(nAux, numeros.n);
		end = clock();
		infosShell.time = ((double) (end - start)) / CLK_TCK;
		addPoints(grafico, infosShell, "Shell Sort");
		copyKeys(numeros.v, nAux, 0, numeros.n);	
	}
	if(strcmp(IupGetAttribute(checkb[3], "VALUE"), "ON") == 0){
		stats infosMerge;
		infosMerge.qtdChan = 0;
		infosMerge.qtdComp = 0;
		infosMerge.qtdElements = numeros.n;
		start = clock();
		mergeSort(nAux, 0, numeros.n-1, &infosMerge);
		end = clock();
		infosMerge.time = ((double) (end - start)) / CLK_TCK;;
		addPoints(grafico, infosMerge, "Merge Sort");
		copyKeys(numeros.v, nAux, 0, numeros.n);	
	}
	if(strcmp(IupGetAttribute(checkb[4], "VALUE"), "ON") == 0){
		stats infosQuick;
		infosQuick.qtdChan = 0;
		infosQuick.qtdComp = 0;
		infosQuick.qtdElements = numeros.n;
		start = clock();
		quickSort(nAux, 0, numeros.n-1, &infosQuick);
		end = clock();
		infosQuick.time = ((double) (end - start)) / CLK_TCK;
		addPoints(grafico, infosQuick, "Quick Sort");
		copyKeys(numeros.v, nAux, 0, numeros.n);	
	}
	if(strcmp(IupGetAttribute(checkb[5], "VALUE"), "ON") == 0){
		stats infosRadix;
		start = clock();
		infosRadix = radixSort(nAux, numeros.n);
		end = clock();
		infosRadix.time = ((double) (end - start)) / CLK_TCK;
		addPoints(grafico, infosRadix, "Radix Sort");
		copyKeys(numeros.v, nAux, 0, numeros.n);
	}
	if(strcmp(IupGetAttribute(checkb[6], "VALUE"), "ON") == 0){
		stats infosSelection;
		start = clock();
		infosSelection = selectionSort(nAux, numeros.n);
		end = clock();
		infosSelection.time = ((double) (end - start)) / CLK_TCK;
		addPoints(grafico, infosSelection, "Selection Sort");
	}	
	
	free(numeros.v);
	free(nAux);
	
	/*
		Crio uma Vbox que vai ser a aba contendo outro menu de tabsR
	*/
	
	vboxG[0] = IupVbox(grafico[0], NULL);
	vboxG[1] = IupVbox(grafico[1], NULL);
	vboxG[2] = IupVbox(grafico[2], NULL);
	
	IupSetAttribute(vboxG[0], "TABTITLE", "Gráfico de Comparações");
	IupSetAttribute(vboxG[1], "TABTITLE", "Gráfico de Trocas");
	IupSetAttribute(vboxG[2], "TABTITLE", "Gráfico de Tempo");
	tabsI = IupTabs(vboxG[0], vboxG[1], vboxG[2], NULL);

	aux = IupHbox(tabsI, NULL);
	IupSetAttribute(aux, "TABTITLE", "Resultado");
	IupSetAttribute(aux, "MARGIN", "4x4");
	IupSetAttribute(aux, "GAP", "10");
	
	IupAppend(tabs, aux);
	IupMap(aux);
	IupRefresh(aux);
	return IUP_DEFAULT;
}

array getNumbers(Ihandle *multitext){
	char * i;
	array infos;
	int qtd = 0, j = 0, *numbers;
	i = IupGetAttribute(multitext, "VALUE");
	while(*i){
		if (isdigit(*i)){
			int numero = (int)strtol(i, &i, 10);
			qtd++;
		}
		else{
			i++;
		}
	}
	numbers = malloc(qtd * sizeof(int));
	i = IupGetAttribute(multitext, "VALUE");
	while(*i && j < qtd){
		if (isdigit(*i)){
			numbers[j] = (int)strtol(i, &i, 10);
			j++;
		}
		else{
			i++;
		}
	}
	//printVetor(numbers, qtd);
	infos.v = numbers;
	infos.n = qtd;
	return infos;
}

void addPoints(Ihandle** plot, stats infos, char* type){
	int x, y;
	x = infos.qtdElements;
	
	y = infos.qtdComp;
	IupPlotBegin(plot[0], 0);
		IupPlotAdd(plot[0], 0, 0);
		IupPlotAdd(plot[0], x, y);
	IupPlotEnd(plot[0]);
	IupSetAttribute(plot[0], "DS_LEGEND", type);
	IupSetAttribute(plot[0], "DS_LINEWIDTH", "1");	
	
	y = infos.qtdChan;
	IupPlotBegin(plot[1], 0);
		IupPlotAdd(plot[1], 0, 0);
		IupPlotAdd(plot[1], x, y);
	IupPlotEnd(plot[1]);
	IupSetAttribute(plot[1], "DS_LEGEND", type);
	IupSetAttribute(plot[1], "DS_LINEWIDTH", "1");	
	
	
	y = infos.time;
	IupPlotBegin(plot[2], 0);
		IupPlotAdd(plot[2], 0, 0);
		IupPlotAdd(plot[2], x, y);
	IupPlotEnd(plot[2]);
	IupSetAttribute(plot[2], "DS_LEGEND", type);
	IupSetAttribute(plot[2], "DS_LINEWIDTH", "1");
}

int * copyVetor(int v[], int size){
	int * copy;
	int i;
	copy = malloc(size * sizeof(int));
	for(i=0;i<size;i++)
		copy[i] = v[i];
	return copy;
}
void copyKeys(int a[], int b[], int start, int end){
	int i = start;
	while(i<end){
		b[i] = a[i];
		i++;
	}
}