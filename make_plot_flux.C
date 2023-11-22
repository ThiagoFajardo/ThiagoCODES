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

void make_plot_flux(){

/*Gera a Tela*/
    auto c9 = new TCanvas("c9","Fluxo");
    c9->SetGrid();
    c9->SetLogx();


/*Gera os graficos*/
    auto grmu  = new TGraph("../data_files_flux/spectrum_DUNE_mu.dat");
    auto gre  = new TGraph("../data_files_flux/spectrum_DUNE_e.dat");
    auto grtau  = new TGraph("../data_files_flux/spectrum_DUNE_tau.dat");



/*Estilo da linha*/
    grmu->SetLineStyle(9);
    grtau->SetLineStyle(9);
    gre->SetLineStyle(9);
    
/*Cor e tamanho*/
    grmu->SetLineWidth(2);
    grmu->SetLineColor(kBlue);

    gre->SetLineColor(kRed);
    gre->SetLineWidth(2);

    grtau->SetLineColor(kBlack);
    grtau->SetLineWidth(2);

    string emax = "Max Eletron: " + to_string(TMath::MaxElement(gre->GetN(),gre->GetY()));
    string mumax = "Max Muon: " + to_string(TMath::MaxElement(grmu->GetN(),grmu->GetY()));
    string taumax = "Max Tau: " + to_string(TMath::MaxElement(grtau->GetN(),grtau->GetY()));

/*Gera o grafico multiplo*/
    auto *g = new TMultiGraph();

/*titulo e eixos*/
    g->SetTitle("Fluxos dos Neutrinos;Energia (GeV); Fluxos(Log)");
    

/*coloca limite do grafico*/
    g->GetXaxis()->SetLimits(0.25,10);
    g->GetXaxis()->CenterTitle(true);
    g->GetYaxis()->CenterTitle(true);
    g->GetXaxis()->SetRangeUser(0.25,10);
    g->GetYaxis()->SetRangeUser(-14.5,-10.05);
    
/*adiciona os graficos principais*/
    g->Add(grmu);
    g->Add(grtau); 
    g->Add(gre);

    //printf("MAX e: %f\n", gre->GetYaxis()->GetXmax());

/*Desenha*/ 
    g->Draw("Al");

/*Legendas*/
    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    //legend->SetHeader("","C"); // option "C" allows to center the header
    legend->AddEntry(grmu,"Muon","l");
    legend->AddEntry(gre,"Eletron","l");
    legend->AddEntry(grtau,"Tau","l");
    legend->Draw();

    auto legend2 = new TLegend(0.1,0.1,0.37,0.2);
    legend2->SetHeader("Maximos ","C"); // option "C" allows to center the header
    legend2->AddEntry((TObject*)0,mumax.c_str(),"");
    legend2->AddEntry((TObject*)0,emax.c_str(),"");
    legend2->AddEntry((TObject*)0,taumax.c_str(),"");
    legend2->Draw();

    legend->SetTextSize(0.022);
    legend2->SetTextSize(0.025);

}
