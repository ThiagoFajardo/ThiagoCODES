#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TF2.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TLatex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

void histo_chi2(){


/*Cria a Tela*/
TCanvas *c10 = new TCanvas("Chi2","Chi2",600,500);

/*cria o grafico do chi2*/
TGraph2D *graph = new TGraph2D("../betachi2.dat");

/*Cria o histograma com o grafico do chi2*/
TH2D *hist = graph->GetHistogram();


/*Puxa os dados*/
fstream infile;
infile.open("../betachi2.dat",ios::in);

double x,y;
int res;

for(int i = 0; i < 1100; i++)
  {
    infile >> x >> y >> res;
    /*Filtra valures para o histograma*/
    hist->Fill(x,y,res);
    /*Força a parada*/
    if(infile.eof()) break;
  }
  
/*fecha o arquivo*/
infile.close();

/*divide em dois graficos* */
c10->Divide(1,2);

/*inicio primeiro gráfico*/
c10->cd(1);
//hist->SetLogx();

hist->SetStats(true);
//int binWithMax = hist->GetMaximumBin();
//double xValueWithMax = hist->GetXaxis()->GetBinCenter(binWithMax);
//double yValueWithMax = hist->GetBinContent(binWithMax);
  
/*Titulos*/
hist->GetXaxis()->CenterTitle();
hist->GetYaxis()->CenterTitle();
hist->GetZaxis()->CenterTitle();
hist->GetXaxis()->SetTitle("log sin^{2} (2#theta_{13})");
hist->GetYaxis()->SetTitle("#delta_{CP} (graus)");
hist->GetZaxis()->SetTitle("#Delta #chi^{2}");

/*Contornos*/
double contornos[3] = {2.30,6.18,14.16};
hist->SetContour(3,contornos);

/*Define a paleta de cores para o histograma*/
int colors[3] = {kRed,kOrange,kYellow};
gStyle->SetPalette(3,colors);


/*Plota o histograma*/
hist->Draw("cont1z");

/*inicio do segundo grafico*/
c10->cd(2);

graph->Draw("SURF1 LIST");



}
    
