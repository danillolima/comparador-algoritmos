#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "iup.h"
#include "iupcontrols.h"
#include "iup_plot.h"

#include <cd.h>
#include <cdiup.h>




int main(int argc, char* argv[]){
	Ihandle *plot, *box, *hbox, *dlg;
	IupOpen(&argc, &argv);
	IupControlsOpen();
	
	IupPlotOpen();
	
	IupSetGlobal("UTF8MODE", "yes");

	plot = IupPlot();
	
	IupSetAttribute(plot, "TITLE", "Resultado: Comparações por algortimo");
	IupSetAttribute(plot, "FONT", "Helvetica, 10");
	IupSetAttribute(plot, "LEGENDSHOW", "YES");
	IupSetAttribute(plot, "AXS_XLABEL", "Tamanho da entrada(N)");
	IupSetAttribute(plot, "AXS_YLABEL", "Quantidade de Comparações");
	IupSetAttribute(plot, "AXS_XCROSSORIGIN", "Yes");
	IupSetAttribute(plot, "AXS_YCROSSORIGIN", "Yes");
	IupSetAttribute(plot, "MARGINTOP", "40");
    IupSetAttribute(plot, "MARGINLEFT", "100");
    IupSetAttribute(plot, "MARGINBOTTOM", "50");
    IupSetAttribute(plot, "TITLEFONTSIZE", "16");
	
	IupPlotBegin(plot, 0);
	int theFac, theI, x, y;
	for (theI=1; theI <= 100; theI++){
		x = theI;
		y = theI * theI;
		IupPlotAdd(plot, x, y);
	}
	
	
	IupPlotEnd(plot);
	
	IupSetAttribute(plot, "DS_LEGEND", "Selection Sort");
	IupSetAttribute(plot, "DS_LINEWIDTH", "1");	

	
	IupPlotBegin(plot, 0);
	theFac = 2.0/100;
	for (theI=1; theI<100; theI++) 
	{
		x = theI+2;
		y = theI*theI;
		IupPlotAdd(plot, x, y);
	}
	IupPlotEnd(plot);
	
   IupSetAttribute(plot, "DS_LEGEND", "Merger Sort");
   
	
	

	hbox = IupHbox(plot, NULL);
	IupSetAttribute(hbox, "MARGIN", "4x4");
	IupSetAttribute(hbox, "GAP", "10");
	dlg = IupDialog(hbox);
	IupSetAttribute(dlg, "TITLE", "IupPlot Example");
	IupSetAttribute(dlg, "SIZE", "400x300");
	IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupSetAttribute(dlg, "SIZE", NULL);
	
	IupMainLoop();
	IupClose();
	return EXIT_SUCCESS;
	
}