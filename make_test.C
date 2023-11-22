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


void make_test(){

    auto gr  = new TGraph();
    auto gr1  = new TGraph();

    fstream file;
    file.open("chi2.dat",ios::in);

    double x,y;
    int k = 0;

    while(k <= 50)
    {
        file >> x >> y;
        gr->SetPoint(k,x,y);
        k++;
        if(file.eof()) break;
    }

    while(k <= 100)
    {
        if(file.eof()) break;
        file >> x >> y;
        gr1->SetPoint(k,x,y);
        k++;
    }
    
    file.close();

    TGraph2D *T13T23 = new TGraph2D("chi2.dat");
    TH2 *HistoT13T23 = T13T23->GetHistogram();

    gStyle->SetPadLeftMargin(0.23);
    gStyle->SetPadBottomMargin(0.23);
    gStyle->SetPadRightMargin(0.03);
    gStyle->SetPadTopMargin(0.03);
    gStyle->SetLineWidth(3);
    gStyle->SetTextFont(132);

    HistoT13T23->SetLineWidth(4);
    HistoT13T23->SetMaximum(4488.0);
    HistoT13T23->SetTitle("");
    HistoT13T23->GetXaxis()->CenterTitle();
    HistoT13T23->GetYaxis()->CenterTitle();
    HistoT13T23->GetZaxis()->CenterTitle();
    HistoT13T23->GetXaxis()->SetTitle("log sin^{2} (2#theta_{13})");
    HistoT13T23->GetYaxis()->SetTitle("#delta_{CP} (degrees)");
    HistoT13T23->GetZaxis()->SetTitle("#Delta #chi^{2}");
    HistoT13T23->GetXaxis()->SetTitleOffset(1.5);
    HistoT13T23->GetYaxis()->SetTitleOffset(1.7);
    HistoT13T23->GetZaxis()->SetTitleOffset(1.0);
    HistoT13T23->GetXaxis()->SetTitleSize(0.05);
    HistoT13T23->GetYaxis()->SetTitleSize(0.05);
    HistoT13T23->GetZaxis()->SetTitleSize(0.05);
    HistoT13T23->GetXaxis()->SetLabelSize(0.05);
    HistoT13T23->GetYaxis()->SetLabelSize(0.05);
    HistoT13T23->GetZaxis()->SetLabelSize(0.05);
    HistoT13T23->GetXaxis()->SetTickLength(0.04);
    HistoT13T23->GetYaxis()->SetTickLength(0.04);
    HistoT13T23->GetZaxis()->SetTickLength(0.04);
    HistoT13T23->SetNdivisions(1005, "X"); 
    HistoT13T23->SetNdivisions(1005, "Y"); 
    HistoT13T23->SetNdivisions(1005, "Z"); 
    HistoT13T23->GetXaxis()->SetDecimals();
    HistoT13T23->GetYaxis()->SetDecimals();
    HistoT13T23->GetXaxis()->SetNoExponent();
    HistoT13T23->GetYaxis()->SetNoExponent();

    Double_t contornos[3];
    contornos[0] = 2.30;
    contornos[1] = 6.18;
    contornos[2] = 14.16;
    HistoT13T23->SetContour(3, contornos);

    Int_t palette[3];
     palette[0] = 2;
     palette[1] = 3;
     palette[2] = 4;
    gStyle->SetPalette(3,palette);


 TCanvas *plot3 = new TCanvas("plot3","plot3",600,500);
    plot3->SetTickx(1);
    plot3->SetTicky(1);

    HistoT13T23->Draw("Z CJUST");
    plot3->Update();

    gr->SetMarkerColor(kBlue);
    gr->SetMarkerStyle(kFullCircle);

    gr1->SetMarkerColor(kRed);
    gr1->SetMarkerStyle(kFullCircle);

   // gr->Draw("P");
    
  //  gr1->Draw("P");

    
//    HistoT13T23->SetLineColorAlpha(kWhite, 0.00);
//    HistoT13T23->Draw("SAME CONT2 LIST");
//    plot3->SaveAs("T13T23.png");


    HistoT13T23->SetLineWidth(1);

    TCanvas *plot4 = new TCanvas("plot4","plot4") ;  
    HistoT13T23->Draw("surf1");


}
