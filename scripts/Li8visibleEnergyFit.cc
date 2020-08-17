/*
//
// Created by niko on 18.02.20.
//

// Local
#include "include/Li8visibleEnergyFit.hh"

// System
#include <string>

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TCanvas.h"

//RooFit
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"

void Li8visibleEnergyFit() {

    // Import TTree into a RooDataSet
    // -----------------------------------------------------------------------------------------------------------------
    std::string s_fileName = "/home/niko/CLionProjects/untitled1/isotops/Li8/topo_Li8_eCut_100.root";
    std::string s_branchName = "visibleEnergy";

    TFile *file = new TFile(s_fileName.c_str());
    TTree *tree = (TTree *) file->Get("topologies/topoTree");

    Double_t maxValue = tree->GetMaximum(s_branchName.c_str());
    Double_t minValue = tree->GetMinimum(s_branchName.c_str());

    RooRealVar x = RooRealVar(s_branchName.c_str(), s_branchName.c_str(), minValue, maxValue);
    RooDataSet data = RooDataSet("data", s_branchName.c_str(), x, RooFit::Import(*tree));

    delete file;

    // Construct pdf  with 3 Gaussians
    // -----------------------------------------------------------------------------------------------------------------
    RooRealVar mean1 = RooRealVar("mean1", "mean1", 2.81, 0., 12.);
    RooRealVar sigma1 = RooRealVar("sigma1", "sigma1", 1.31, 0., 6.);
    RooRealVar mean2 = RooRealVar("mean2", "mean2", 4.71, 0., 12.);
    RooRealVar sigma2 = RooRealVar("sigma2", "sigma2", 1.61, 0., 6.);
    RooRealVar mean3 = RooRealVar("mean3", "mean3", 7.71, 0., 12.);
    RooRealVar sigma3 = RooRealVar("sigma3", "sigma3", 1.41, 0., 6.);

    RooGaussian gaus1 = RooGaussian("gaus1", "gaus1", x, mean1, sigma1);
    RooGaussian gaus2 = RooGaussian("gaus2", "gaus2", x, mean2, sigma2);
    RooGaussian gaus3 = RooGaussian("gaus3", "gaus3", x, mean3, sigma3);

    RooRealVar frac1 = RooRealVar("frac1", "frac1", 0.31, 0.0, 1.0);
    RooRealVar frac2 = RooRealVar("frac2", "frac2", 0.59, 0.0, 1.0);
    RooRealVar frac3 = RooRealVar("frac3", "frac3", 0.4, 0.0, 1.0);

    RooAddPdf Li8PdfVisibleEnergy = RooAddPdf(
            "Li8VisibleEnergy",
            "Gauss1 + Gauss2 + Gauss3",
            RooArgList(gaus1, gaus2, gaus3),
            RooArgList(frac1, frac2)
    );


    // Fit and plot
    // -----------------------------------------------------------------------------------------------------------------

    RooFitResult *r = Li8PdfVisibleEnergy.fitTo(data, RooFit::Save());
    r->Print();

    RooPlot *xframe = x.frame();
    xframe->SetTitle("Li8");
    data.plotOn(xframe);
    Li8PdfVisibleEnergy.plotOn(xframe);

    TCanvas* c = new TCanvas("Li8","Li8",800,400) ;
    c->Divide(2) ;
    c->cd(1);
    gPad->SetLeftMargin(0.15);
//    xframe->GetYaxis().SetTitleOffset(1.4);
    xframe->Draw();
    c->SaveAs("/home/niko/SOLID/SolidBackground/output/Li8/Li8visibleEnergyFit.root");
}

*/
