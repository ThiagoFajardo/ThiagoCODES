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

void make_plot(){
    
    auto c3 = new TCanvas("c3","Probabilidade",700,500);
    c3->SetGrid();
    c3->SetLogx();
    
    auto gr  = new TGraph("probability_DUNE.dat");
    auto grBSM  = new TGraph("BSMprobability_cmueDUNE.dat");
    auto grBSM1 = new TGraph("BSMprobability_cmueDUNE1.dat");
    auto grBSM2  = new TGraph("BSMprobability_cmueDUNE2.dat");
    auto grBSM3  = new TGraph("BSMprobability_cmueDUNE3.dat");

    grBSM1->SetLineStyle(2);
    grBSM1->SetLineStyle(2);
    grBSM2->SetLineStyle(2);
    grBSM3->SetLineStyle(2);

    grBSM->SetLineColor(4);
    grBSM1->SetLineColor(2);

    grBSM2->SetLineColor(3);
    grBSM3->SetLineColor(6);

    auto *g = new TMultiGraph();

    g->GetXaxis()->CenterTitle(true);
    g->GetYaxis()->CenterTitle(true);
    //g->GetXaxis()->SetLimits(0.2,10);
    g->GetXaxis()->SetRangeUser(0.25,8.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->SetTitle("Probability of appearance #nu_{#mu} to #nu_{e};E (GeV);P_{#mu e}");
    g->GetXaxis()->CenterTitle();
    g->GetYaxis()->CenterTitle();
    g->GetYaxis()->SetNdivisions(505);

    g->Draw();
    g->Add(grBSM);
    g->Add(grBSM1);
    g->Add(grBSM2);
    g->Add(grBSM3);
    //g->Draw();

    auto legend = new TLegend(0.7,0.9,0.9,0.8);
    legend->SetHeader("Probabilidades Muon->Eletron","C"); // option "C" allows to center the header
    legend->AddEntry(gr,"Std","l");
    legend->AddEntry(grBSM,"LIV","l");
    legend->AddEntry(grBSM1,"LIV + M_PI","l");
    legend->AddEntry(grBSM2,"LIV + M_PI/2","l");
    legend->AddEntry(grBSM3,"LIV + 3*M_PI/2","l");
    legend->Draw();
}
