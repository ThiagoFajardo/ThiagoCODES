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

void test_graf(){

/*Gera a Tela*/
    auto t2 = new TCanvas("t2","Probabilidade");
    t2->SetGrid();
    t2->SetLogx();

/*Gera o grafico*/
    auto grmu  = new TGraph("../data_test1.dat");


/*Estilo da linha*/
    grmu->SetLineStyle(7);

/*Cor e tamanho*/
    grmu->SetLineWidth(2);
    grmu->SetLineColor(kBlue);
    grmu->GetYaxis()->SetLimits(0,2);

/*titulo e eixos*/
    grmu->SetTitle("Probabilidade Muon (vacuo);E (GeV);Probability");

/*coloca limite do grafico*/
    grmu->GetXaxis()->SetLimits(0.25,10.0);
    grmu->GetXaxis()->SetRangeUser(0.25,10);
    grmu->GetYaxis()->SetRangeUser(0,1);
    string mumaxY = "Max Muon: " + to_string(TMath::MaxElement(grmu->GetN(),grmu->GetY()));
    string mumaxX = "Max Muon: " + to_string(TMath::MaxElement(grmu->GetN(),grmu->GetX()));

/*Desenha*/ 
    grmu->Draw("Al");

    auto legend2 = new TLegend(0.1,0.1,0.37,0.2);
    legend2->SetHeader("Maximo Y ","C"); // option "C" allows to center the header
    legend2->AddEntry((TObject*)0,mumaxY.c_str(),"");
    legend2->AddEntry((TObject*)0,mumaxX.c_str(),"");
    legend2->Draw();

/*Legenda*/
    auto legend = new TLegend(0.7,0.9,0.9,0.8);
    legend->SetHeader("Probabilidades","C"); // option "C" allows to center the header
    legend->AddEntry(grmu,"Muon->Muon","l");
    legend->Draw();

    legend->SetTextSize(0.022);
    legend2->SetTextSize(0.025);
}
