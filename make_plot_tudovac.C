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

void make_plot_tudovac(){

    auto c8 = new TCanvas("c8","Probabilidade",700,500);
    c8->SetGrid();
    c8->SetLogx();

    auto antigrmu_vac  = new TGraph("../data_files_anti/probability_vac_DUNE_antimu.dat");
    auto antigre_vac  = new TGraph("../data_files_anti/probability_vac_DUNE_antie.dat");
    auto antigrtau_vac  = new TGraph("../data_files_anti/probability_vac_DUNE_antitau.dat");

    auto grmu_vac  = new TGraph("../data_files/probability_vac_DUNE_mu.dat");
    auto gre_vac  = new TGraph("../data_files/probability_vac_DUNE_e.dat");
    auto grtau_vac  = new TGraph("../data_files/probability_vac_DUNE_tau.dat");

    /*estilo da linha materia*/
    antigrmu_vac->SetLineStyle(7);
    antigrtau_vac->SetLineStyle(7);
    antigre_vac->SetLineStyle(7);

    /*estilo da linha vacuo*/
    gre_vac->SetLineStyle(1);
    grmu_vac->SetLineStyle(1);
    grtau_vac->SetLineStyle(1);

    /*Cor e tamanho vacuo*/
    grmu_vac->SetLineColor(kBlue);
    grmu_vac->SetLineWidth(2);
    gre_vac->SetLineColor(kRed);
    gre_vac->SetLineWidth(2);
    grtau_vac->SetLineColor(kBlack);
    grtau_vac->SetLineWidth(2);

    /*Cor e tamanho mat*/
    antigrmu_vac->SetLineColor(kBlue);
    antigrmu_vac->SetLineWidth(2);
    antigre_vac->SetLineColor(kRed);
    antigre_vac->SetLineWidth(2);
    antigrtau_vac->SetLineColor(kBlack);
    antigrtau_vac->SetLineWidth(2);

    auto *g = new TMultiGraph();
    
    g->SetTitle(" AntiMuon & Muon (vacuo);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(antigrmu_vac);
    g->Add(antigrtau_vac);
    g->Add(antigre_vac);
    g->Add(grmu_vac);
    g->Add(grtau_vac); 
    g->Add(gre_vac);
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.9,0.7);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(antigrmu_vac,"AntiMuon->AntiMuon","l");
    legend->AddEntry(antigre_vac,"AntiMuon->AntiEletron","l");
    legend->AddEntry(antigrtau_vac,"AntiMuon->AntiTau","l");
    legend->AddEntry(grmu_vac,"Muon->Muon","l");
    legend->AddEntry(gre_vac,"Muon->Eletron","l");
    legend->AddEntry(grtau_vac,"Muon->Tau","l");
    legend->Draw();

}