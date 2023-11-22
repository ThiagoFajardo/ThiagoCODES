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

void make_plot_vac(){

/*Gera a Tela*/
    auto c1 = new TCanvas("c1","Probabilidade");
    c1->SetGrid();
    c1->SetLogx();


/*Gera os graficos*/
    auto grmu  = new TGraph("../data_files/probability_vac_DUNE_mu.dat");
    auto gre  = new TGraph("../data_files/probability_vac_DUNE_e.dat");
    auto grtau  = new TGraph("../data_files/probability_vac_DUNE_tau.dat");



/*Estilo da linha*/
    grmu->SetLineStyle(7);
    grtau->SetLineStyle(7);
    gre->SetLineStyle(7);
    
/*Cor e tamanho*/
    grmu->SetLineWidth(2);
    grmu->SetLineColor(kBlue);

    gre->SetLineColor(kRed);
    gre->SetLineWidth(2);

    grtau->SetLineColor(kGreen);
    grtau->SetLineWidth(2);

/*Gera o grafico multiplo*/
    auto *g = new TMultiGraph();

/*titulo e eixos*/
    g->SetTitle("Probabilidade Muon_ALL (vacuo);E (GeV);Probability");

/*coloca limite do grafico*/
    g->GetXaxis()->SetLimits(0.25,10.0);

    g->GetXaxis()->SetRangeUser(0.25,10);
    g->GetYaxis()->SetRangeUser(0,1);
    
/*adiciona os graficos principais*/
    g->Add(grmu);
    g->Add(grtau); 
    g->Add(gre);

/*Desenha*/ 
    g->Draw("Al");
    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(grmu,"Muon->Muon","l");
    legend->AddEntry(gre,"Muon->Eletron","l");
    legend->AddEntry(grtau,"Muon->Tau","l");
    legend->Draw();
}
