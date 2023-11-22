
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TF2.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom2.h"
#include "TROOT.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

void test_histo()

{
    TCanvas *n1 = new TCanvas(); 
    TRandom2 *rand = new TRandom2(3);
    auto *hist = new TH1D("hist","gaus(0)*expo(3)",100,0,100);

    fstream infile;
    infile.open("data.txt",ios::in);

    for (int i = 0; i < 1000; i++)
    {
        /*Gera numeros aleatórios*/
        double r = rand->Gaus(50,1);
        infile << r << endl;
        hist->Fill(r);
    }

    infile.close();

    infile.open("data.txt",ios::in);
    double values;

    while (1)
    {
        infile >> values;
        hist->Fill(values);
        if(infile.eof()) break;
    }
    
    infile.close();

    /*Estilização tanto em X quanto em Y*/
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetTitle("Distribution");
    hist->GetYaxis()->SetTitle("Entries");

    TF1 *fit = new TF1("fit", "gaus",0,10);

    fit->SetParameters(1,0.40);

    /*Arruma o histograma, neste caso para uma gaussiana*/
    hist->Fit("gaus");
    
    /*Desenha o grafico*/
    hist->Draw("CONT1");

}

