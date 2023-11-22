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

void make_plot_chi2(){

/*Gera a Tela*/
    auto c9 = new TCanvas("c9","Fluxo");
    c9->SetGrid();

/*Gera os graficos*/
    auto grmu  = new TGraph2D("chi2.dat");

/*Estilo da linha*/
    grmu->SetLineStyle(9);

    
/*Cor e tamanho*/
    grmu->SetLineWidth(2);
    grmu->SetLineColor(kBlue);

/*titulo e eixos*/
    grmu->SetTitle("Chi2 teste1; theta13; deltacp");
    

/*coloca limite do grafico*/
    grmu->GetXaxis()->SetLimits(1,100);
    grmu->GetXaxis()->CenterTitle(true);
    grmu->GetYaxis()->CenterTitle(true);
    grmu->GetXaxis()->SetRangeUser(4000,10);
    grmu->GetYaxis()->SetRangeUser(4000,-10.05);

/*Desenha*/ 
    grmu->Draw("surf1");


}
