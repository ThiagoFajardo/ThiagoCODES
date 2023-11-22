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

void make_plot_mat(){

    auto c2 = new TCanvas("c2","Probabilidade",700,500);
    c2->SetGrid();
    c2->SetLogx();

    auto grmu  = new TGraph("../data_files/probability_matter_DUNE_mu.dat");
    auto gre  = new TGraph("../data_files/probability_matter_DUNE_e.dat");
    auto grtau  = new TGraph("../data_files/probability_matter_DUNE_tau.dat");


    grmu->SetLineStyle(7);
    grtau->SetLineStyle(7);
    gre->SetLineStyle(7);
    
    grmu->SetLineColor(kBlue);
    grmu->SetLineWidth(2);

    gre->SetLineColor(kRed);
    gre->SetLineWidth(2);
    grtau->SetLineColor(kGreen);
    grtau->SetLineWidth(2);

    double emax = TMath::MaxElement(gre->GetN(),gre->GetY());
    double mumax = TMath::MaxElement(grmu->GetN(),grmu->GetY());
    double taumax = TMath::MaxElement(grtau->GetN(),grtau->GetY());
    printf("MAX e: %f\n", emax);
    printf("MAX mu: %f\n", mumax);
    printf("MAX tau: %f\n", taumax);

    auto *g = new TMultiGraph();
    
    g->SetTitle("Probabilidae Muon_ALL (materia);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(grmu);
    g->Add(grtau);
    g->Add(gre);
    
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    legend->SetHeader("Probabilidades ","C"); // option "C" allows to center the header
    legend->AddEntry(grmu,"Muon->Muon","l");
    legend->AddEntry(gre,"Muon->Eletron","l");
    legend->AddEntry(grtau,"Muon->Tau","l");
    legend->Draw();

}
