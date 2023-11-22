#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

void histo_thiago(){

/*Cria a Tela*/
TCanvas *c11 = new TCanvas("Gaus");

/*Cria o histograma*/
TH2D *hist = new TH2D("hist", "Gaus",100,0,0.3,100,0,4);

/*Le todas as linhas do arquivo */
for (int ij = 1;ij < 10000; ij++)
{
  double x = gRandom->Gaus(5,2);
  //hist->Fill(gRandom->Gaus(5,2));

}

  /*Zera os status do histograma*/
  hist->SetStats(0);

  /*Titulos*/
  hist->GetXaxis()->SetTitle("");
  hist->GetYaxis()->SetTitle("");

  c11->Update();

  hist->Draw("cont1");

}

