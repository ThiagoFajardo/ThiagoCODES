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

void make_plot_antimat(){

    auto c5 = new TCanvas("c5","Probabilidade",700,500);
    c5->SetGrid();
    c5->SetLogx();

    auto antigrmu  = new TGraph("../data_files_anti/probability_matter_DUNE_antimu.dat");
    auto antigre  = new TGraph("../data_files_anti/probability_matter_DUNE_antie.dat");
    auto antigrtau  = new TGraph("../data_files_anti/probability_matter_DUNE_antitau.dat");


    antigrmu->SetLineStyle(7);
    antigrtau->SetLineStyle(7);
    antigre->SetLineStyle(7);
    
    antigrmu->SetLineColor(kBlue);
    antigrmu->SetLineWidth(2);

    antigre->SetLineColor(kRed);
    antigre->SetLineWidth(2);
    antigrtau->SetLineColor(kGreen);
    antigrtau->SetLineWidth(2);

    auto *g = new TMultiGraph();
    
    g->SetTitle("Probabilidae AntiMuon_ALL (materia);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(antigrmu);
    g->Add(antigrtau);
    g->Add(antigre);
    
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.9,0.8);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(antigrmu,"AntiMuon->AntiMuon","l");
    legend->AddEntry(antigre,"AntiMuon->AntiEletron","l");
    legend->AddEntry(antigrtau,"AntiMuon->AntiTau","l");
    legend->Draw();

}
