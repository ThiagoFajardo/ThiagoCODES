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

void make_plot_tudomat(){

    auto c7 = new TCanvas("c7","Probabilidade",700,500);
    c7->SetGrid();
    c7->SetLogx();

    auto antigrmu_mat  = new TGraph("../data_files_anti/probability_matter_DUNE_antimu.dat");
    auto antigre_mat  = new TGraph("../data_files_anti/probability_matter_DUNE_antie.dat");
    auto antigrtau_mat  = new TGraph("../data_files_anti/probability_matter_DUNE_antitau.dat");

    auto grmu_mat  = new TGraph("../data_files/probability_matter_DUNE_mu.dat");
    auto gre_mat  = new TGraph("../data_files/probability_matter_DUNE_e.dat");
    auto grtau_mat  = new TGraph("../data_files/probability_matter_DUNE_tau.dat");

    /*estilo da linha materia*/
    antigrmu_mat->SetLineStyle(7);
    antigrtau_mat->SetLineStyle(7);
    antigre_mat->SetLineStyle(7);

    /*estilo da linha vacuo*/
    gre_mat->SetLineStyle(1);
    grmu_mat->SetLineStyle(1);
    grtau_mat->SetLineStyle(1);

    /*Cor e tamanho vacuo*/
    grmu_mat->SetLineColor(6);
    grmu_mat->SetLineWidth(2);
    gre_mat->SetLineColor(9);
    gre_mat->SetLineWidth(2);
    grtau_mat->SetLineColor(kBlack);
    grtau_mat->SetLineWidth(2);

    /*Cor e tamanho mat*/
    antigrmu_mat->SetLineColor(6);
    antigrmu_mat->SetLineWidth(2);
    antigre_mat->SetLineColor(9);
    antigre_mat->SetLineWidth(2);
    antigrtau_mat->SetLineColor(kBlack);
    antigrtau_mat->SetLineWidth(2);

    auto *g = new TMultiGraph();
    
    g->SetTitle(" AntiMuon & Muon (materia);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(antigrmu_mat);
    g->Add(antigrtau_mat);
    g->Add(antigre_mat);
    g->Add(grmu_mat);
    g->Add(grtau_mat); 
    g->Add(gre_mat);
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.9,0.7);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(antigrmu_mat,"AntiMuon->AntiMuon","l");
    legend->AddEntry(antigre_mat,"AntiMuon->AntiEletron","l");
    legend->AddEntry(antigrtau_mat,"AntiMuon->AntiTau","l");
    legend->AddEntry(grmu_mat,"Muon->Muon","l");
    legend->AddEntry(gre_mat,"Muon->Eletron","l");
    legend->AddEntry(grtau_mat,"Muon->Tau","l");
    legend->Draw();

}