//
// Created by niko on 15.05.20.
//

// Local
#include "include/HistoAnalysis.hh"

// ROOT
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

// System
#include <sstream>

void Plot2NormalizedHistos(
        const char *name1, const char *name2, const char* title, const char* units,
                   Int_t nBins, Double_t xMin, Double_t xMax,
                   std::vector<Double_t>& first, std::vector<Double_t>& second) {

    gStyle->SetOptStat(0);
    if (*units == ' ') {
        units = "---";
    }

    auto histFirst = new TH1F(name1, title, nBins, xMin, xMax);
    auto histSecond = new TH1F(name2, title, nBins, xMin, xMax);

    for(const Double_t& i : first) {
        histFirst->Fill(i);
    }

    for(const Double_t& i : second) {
        histSecond->Fill(i);
    }

//    Double_t norm1 = histFirst->GetEntries();
    Double_t norm1 = 3412;
//    Double_t norm2 = histSecond->GetEntries();
    Double_t norm2 = 6632;

    Double_t yMin = 0.;
    Double_t yMax = histFirst->GetMaximum() / norm1;
    if ( yMax < histSecond->GetMaximum() / norm2 )
        yMax = histSecond->GetMaximum() / norm2;
    yMax = yMax * 1.1;

//    std::cout << histB8->GetMinimum() / histB8->GetEntries() << std::endl;
//    std::cout << histB8->GetMaximum() / histB8->GetEntries() << std::endl;

    // First histo setting
    std::ostringstream yTitle;
    yTitle << "Events / (" << (xMax - xMin) / nBins << ")";
    histFirst->SetYTitle(yTitle.str().c_str());

    std::string xTitle(title);
    xTitle = xTitle.substr(0, xTitle.find(' ')) + " [" + std::string(units) + "]";
    histFirst->SetXTitle(xTitle.c_str());

    histFirst->SetLineColor(EColor::kBlack);
    histFirst->SetFillColorAlpha(EColor::kAzure- 3, 0.50);
    histFirst->SetMarkerSize(0.);


    histFirst->Scale(1. / norm1);

    histFirst->SetMinimum(yMin);
    histFirst->SetMaximum(yMax);

    // Second histo setting
    histSecond->SetLineColor(EColor::kBlack);
    histSecond->SetFillColorAlpha(EColor::kRed, 0.35);
    histSecond->SetMarkerSize(0.);


    histSecond->Scale(1. / norm2);

    histSecond->SetMinimum(yMin);
    histSecond->SetMaximum(yMax);


    TCanvas *c1 = new TCanvas(title, title, 200, 10, 1200, 800);
    c1->Divide(1, 1);
    c1->cd(1);

    histFirst->Draw("HIST, E");
    histSecond->Draw("same, AH, HIST, E");

    c1->Modified();
    c1->Update();


    TLegend *legend = new TLegend(0.8, 0.8, 0.9, 0.9);
    legend->AddEntry(histFirst, name1);
    legend->AddEntry(histSecond, name2);
    legend->Draw();

    std::ostringstream out;
    out << "/home/niko/SOLID/SolidBackground/output/tmp/" << std::string(title) << ".png";
    c1->SaveAs(out.str().c_str());
}
