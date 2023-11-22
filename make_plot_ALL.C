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

void make_plot_ALL(){

    auto c3 = new TCanvas("c3","Probabilidade",700,500);
    c3->SetGrid();
    c3->SetLogx();

    auto grmu_mat  = new TGraph("../data_files/probability_matter_DUNE_mu.dat");
    auto gre_mat  = new TGraph("../data_files/probability_matter_DUNE_e.dat");
    auto grtau_mat  = new TGraph("../data_files/probability_matter_DUNE_tau.dat");

    auto grmu_vac  = new TGraph("../data_files/probability_vac_DUNE_mu.dat");
    auto gre_vac  = new TGraph("../data_files/probability_vac_DUNE_e.dat");
    auto grtau_vac  = new TGraph("../data_files/probability_vac_DUNE_tau.dat");

    /*estilo da linha materia*/
    grmu_mat->SetLineStyle(7);
    grtau_mat->SetLineStyle(7);
    gre_mat->SetLineStyle(7);

    /*estilo da linha vacuo*/
    gre_vac->SetLineStyle(1);
    grmu_vac->SetLineStyle(1);
    grtau_vac->SetLineStyle(1);

    /*Cor e tamanho vacuo*/
    grmu_vac->SetLineWidth(2);
    grmu_vac->SetLineColor(kBlue);
    gre_vac->SetLineColor(kRed);
    gre_vac->SetLineWidth(2);
    grtau_vac->SetLineColor(kGreen);
    grtau_vac->SetLineWidth(2);

    /*Cor e tamanho mat*/
    grmu_mat->SetLineColor(6);
    grmu_mat->SetLineWidth(2);
    gre_mat->SetLineColor(9);
    gre_mat->SetLineWidth(2);
    grtau_mat->SetLineColor(kBlack);
    grtau_mat->SetLineWidth(2);

    

    auto *g = new TMultiGraph();
    
    g->SetTitle("Probabilidae Muon_ALL (mat_vac);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(grmu_mat);
    g->Add(grtau_mat);
    g->Add(gre_mat);
    g->Add(grmu_vac);
    g->Add(grtau_vac); 
    g->Add(gre_vac);
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.85,0.7);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(grmu_mat,"Muon->Muon(mat)","l");
    legend->AddEntry(gre_mat,"Muon->Eletron(mat)","l");
    legend->AddEntry(grtau_mat,"Muon->Tau(mat)","l");
    legend->AddEntry(grmu_vac,"Muon->Muon(vac)","l");
    legend->AddEntry(gre_vac,"Muon->Eletron(vac)","l");
    legend->AddEntry(grtau_vac,"Muon->Tau(vac)","l");
    legend->Draw();

}

