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

void make_plot_antiALL(){

    auto c4 = new TCanvas("c4","Probabilidade",700,500);
    c4->SetGrid();
    c4->SetLogx();

    auto antigrmu_mat  = new TGraph("../data_files_anti/probability_matter_DUNE_antimu.dat");
    auto antigre_mat  = new TGraph("../data_files_anti/probability_matter_DUNE_antie.dat");
    auto antigrtau_mat  = new TGraph("../data_files_anti/probability_matter_DUNE_antitau.dat");

    auto antigrmu_vac  = new TGraph("../data_files_anti/probability_vac_DUNE_antimu.dat");
    auto antigre_vac  = new TGraph("../data_files_anti/probability_vac_DUNE_antie.dat");
    auto antigrtau_vac  = new TGraph("../data_files_anti/probability_vac_DUNE_antitau.dat");

    /*estilo da linha materia*/
    antigrmu_mat->SetLineStyle(7);
    antigrtau_mat->SetLineStyle(7);
    antigre_mat->SetLineStyle(7);

    /*estilo da linha vacuo*/
    antigre_vac->SetLineStyle(1);
    antigrmu_vac->SetLineStyle(1);
    antigrtau_vac->SetLineStyle(1);

    /*Cor e tamanho vacuo*/
    antigrmu_vac->SetLineWidth(2);
    antigrmu_vac->SetLineColor(kBlue);
    antigre_vac->SetLineColor(kRed);
    antigre_vac->SetLineWidth(2);
    antigrtau_vac->SetLineColor(kGreen);
    antigrtau_vac->SetLineWidth(2);

    /*Cor e tamanho mat*/
    antigrmu_mat->SetLineColor(6);
    antigrmu_mat->SetLineWidth(2);
    antigre_mat->SetLineColor(9);
    antigre_mat->SetLineWidth(2);
    antigrtau_mat->SetLineColor(kBlack);
    antigrtau_mat->SetLineWidth(2);

    auto *g = new TMultiGraph();
    
    g->SetTitle("Probabilidade AntiMuon_ALL (mat_vac);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(antigrmu_mat);
    g->Add(antigrtau_mat);
    g->Add(antigre_mat);
    g->Add(antigrmu_vac);
    g->Add(antigrtau_vac); 
    g->Add(antigre_vac);
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.9,0.7);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(antigrmu_mat,"AntiMuon->AntiMuon(mat)","l");
    legend->AddEntry(antigre_mat,"AntiMuon->AntiEletron(mat)","l");
    legend->AddEntry(antigrtau_mat,"AntiMuon->AntiTau(mat)","l");
    legend->AddEntry(antigrmu_vac,"AntiMuon->AntiMuon(vac)","l");
    legend->AddEntry(antigre_vac,"AntiMuon->AntiEletron(vac)","l");
    legend->AddEntry(antigrtau_vac,"AntiMuon->AntiTau(vac)","l");
    legend->Draw();

}

