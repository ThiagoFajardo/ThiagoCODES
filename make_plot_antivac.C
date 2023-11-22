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

void make_plot_antivac(){

/*Gera a Tela*/
    auto c6 = new TCanvas("c6","Probabilidade");
    c6->SetGrid();
    c6->SetLogx();


/*Gera os graficos*/
    auto antigrmu  = new TGraph("../data_files_anti/probability_vac_DUNE_antimu.dat");
    auto antigre  = new TGraph("../data_files_anti/probability_vac_DUNE_antie.dat");
    auto antigrtau  = new TGraph("../data_files_anti/probability_vac_DUNE_antitau.dat");



/*Estilo da linha*/
    antigrmu->SetLineStyle(7);
    antigrtau->SetLineStyle(7);
    antigre->SetLineStyle(7);
    
/*Cor e tamanho*/
    antigrmu->SetLineWidth(2);
    antigrmu->SetLineColor(kBlue);

    antigre->SetLineColor(kRed);
    antigre->SetLineWidth(2);

    antigrtau->SetLineColor(kGreen);
    antigrtau->SetLineWidth(2);

/*Gera o grafico multiplo*/
    auto *g = new TMultiGraph();

/*titulo e eixos*/
    g->SetTitle("Probabilidade AntiMuon_ALL (vacuo);E (GeV);Probability");

/*coloca limite do grafico*/
    g->GetXaxis()->SetLimits(0.25,10.0);

    g->GetXaxis()->SetRangeUser(0.25,10);
    g->GetYaxis()->SetRangeUser(0,1);
    
/*adiciona os graficos principais*/
    g->Add(antigrmu);
    g->Add(antigrtau); 
    g->Add(antigre);

/*Desenha*/ 
    g->Draw("Al");
    auto legend = new TLegend(0.7,0.9,0.9,0.8);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(antigrmu,"AntiMuon->AntiMuon","l");
    legend->AddEntry(antigre,"AntiMuon->AntiEletron","l");
    legend->AddEntry(antigrtau,"AntiMuon->AntiTau","l");
    legend->Draw();
}
