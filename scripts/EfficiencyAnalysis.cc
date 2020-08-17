//
// Created by niko on 26.02.20.
//

// System
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


// Local
#include "include/nsEsClusCoins.hh"
#include "include/EfficiencyAnalysis.hh"
#include "include/nikoStyle.hh"

//ROOT
#include "TGraph.h"
#include "TVector.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"

void Start(std::string title, const std::string& units, char sign,
        Double_t est, Double_t range, std::vector<Double_t>& B8, std::vector<Double_t>& BiPo) {

//    SetStyle();

    Int_t nRestB8 = 0;
    Int_t nRejBiPo = 0;
    Int_t nB8 = B8.size();
    Int_t nBiPo = BiPo.size();

    est = est - range;

    Double_t step = 0.01;
    Int_t n = (Int_t) 2 * range / step;

    Double_t sumEff[n];
    Double_t effRestB8[n];
    Double_t effRejBiPo[n];
    Double_t threshold[n];

    for (int i = 0; i <= n; ++i) {

        for (Double_t v : B8) {
            if (sign == '>') {
                if (v > (est + i * step)) ++nRestB8;
            } else {
                if (v < (est + i * step)) ++nRestB8;
            }
        }

        for (Double_t v : BiPo) {
            if (sign == '<') {
                if (v > (est + i * step)) ++nRejBiPo;
            } else {
                if (v < (est + i * step)) ++nRejBiPo;
            }
        }

        effRestB8[i] = (Double_t) nRestB8 / nB8;
        effRejBiPo[i] = (Double_t) nRejBiPo / nBiPo;
        sumEff[i] =  effRestB8[i] + effRejBiPo[i];
        threshold[i] = est + i * step;

        /*std::cout << "nRestB8 " << nRestB8 << std::endl;
        std::cout << "nRejBiPo " << nRejBiPo << std::endl;*/
        nRestB8 = 0;
        nRejBiPo = 0;
    }


    auto *g1 = new TGraph(n, threshold, effRestB8);
    auto *g2 = new TGraph(n, threshold, effRejBiPo);
    auto *g3 = new TGraph(n, threshold, sumEff);

    g1->SetMinimum(0);
    g1->SetMaximum(1.6);

    g1->SetMarkerStyle(0);
    g1->SetLineColor(2);
    g1->SetLineWidth(2);
    g1->SetTitle(title.c_str());
    title = title.substr(0, title.find(' ')) + " [" + units + "]";
    g1->GetXaxis()->SetTitle(title.c_str());
    g1->GetYaxis()->SetTitle("Efficiency");

    g2->SetMarkerStyle(0);
    g2->SetLineColor(3);
    g2->SetLineWidth(2);

    g3->SetMarkerStyle(0);
    g3->SetLineColor(4);
    g3->SetLineWidth(2);



    auto *c1 = new TCanvas(title.c_str(), title.c_str(), 200, 10, 1200, 800);
//    c1->Divide(2, 1);

    c1->cd(1);
    g1->Draw();
    g2->Draw("same");

//    c1->cd(2);
    g3->Draw("same");

    c1->Modified();
    c1->Update();

    auto *legend = new TLegend(0.75, 0.75, 0.95, 0.95);
//    legend->AddEntry(g1, "B8 (efficiency of surviving)");
//    legend->AddEntry(g2, "BiPo (efficiency of killing)");
    legend->AddEntry(g1, "B8");
    legend->AddEntry(g2, "BiPo");
    legend->AddEntry(g3, "Summary");
    legend->Draw();

    std::ostringstream out;
    out << "/home/niko/SOLID/SolidBackground/output/tmp/" << "EFF" << title.substr(0, title.find(' ')) << ".png";
    c1->SaveAs(out.str().c_str());
}

void EfficiencyAnalysis(const std::string& tag) {
    std::string pathB8 = __FILE__;
    pathB8 = pathB8.substr(0, pathB8.find("scripts")) + "isotops/B8/newB8_eCut_90.root";
    std::string pathBiPo = __FILE__;
    pathBiPo = pathBiPo.substr(0, pathBiPo.find("scripts")) + "isotops/BiPo/newBiPo_eCut_90.root";

    auto *treeB8 = new nsEsClusCoins(pathB8.c_str());
    auto *treeBiPo = new nsEsClusCoins(pathBiPo.c_str());

    std::vector<Double_t> B8_AC_E_calibrated;
    std::vector<Double_t> BiPo_AC_E_calibrated;

    std::vector<Double_t> B8_eEM1_calibrated;
    std::vector<Double_t> BiPo_eEM1_calibrated;

    std::vector<Double_t> B8_dotEM1_EM2;;
    std::vector<Double_t> BiPo_dotEM1_EM2;;


    Long64_t nbytes = 0, nb = 0;
    Long64_t nentriesB8 = treeB8->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesB8; jentry++) {
        Long64_t ientry = treeB8->LoadTree(jentry);
        if (ientry < 0) break;
        nb = treeB8->fChain->GetEntry(jentry);
        nbytes += nb;

        if (!tag.empty()) {
            if (tag == "(topo2)" && treeB8->topology != 2)
                continue;

            if (tag == "(topo2 && eAC <= 1.8 MeV)" && (treeB8->topology != 2 || treeB8->AC_E_calibrated > 2))
                continue;
        }

        B8_AC_E_calibrated.push_back(treeB8->AC_E_calibrated);
        B8_eEM1_calibrated.push_back(treeB8->eEM1_calibrated);
        B8_dotEM1_EM2.push_back(treeB8->dotEM1_EM2);


    }

    Long64_t nentriesBiPo = treeBiPo->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesBiPo; jentry++) {
        Long64_t ientry = treeBiPo->LoadTree(jentry);
        if (ientry < 0) break;
        nb = treeBiPo->fChain->GetEntry(jentry);
        nbytes += nb;

        if (!tag.empty()) {
            if (tag == "(topo2)" && treeBiPo->topology != 2)
                continue;

            if (tag == "(topo2 && eAC <= 1.8 MeV)" && (treeBiPo->topology != 2 || treeBiPo->AC_E_calibrated > 2))
                continue;
        }

        BiPo_AC_E_calibrated.push_back(treeBiPo->AC_E_calibrated);
        BiPo_eEM1_calibrated.push_back(treeBiPo->eEM1_calibrated);
        BiPo_dotEM1_EM2.push_back(treeBiPo->dotEM1_EM2);

    }

    delete treeB8;
    delete treeBiPo;

    std::string title;

    title = "AC_E_calibrated " + tag;
    Start(title, "MeV", '>' ,0.90, 1.0, B8_AC_E_calibrated, BiPo_AC_E_calibrated);

    title = "eEM1_calibrated " + tag;
    Start(title, "MeV", '<', 0.50, 0.5, B8_eEM1_calibrated, BiPo_eEM1_calibrated);

    title = "dotEM1_EM2 " + tag;
    Start(title, "", '<', -0.7, 0.3, B8_dotEM1_EM2, BiPo_dotEM1_EM2);

}

void FinalEfficiency(const std::string& tag) {
    std::string pathB8 = __FILE__;
    pathB8 = pathB8.substr(0, pathB8.find("scripts")) + "isotops/B8/B8_eCut_90.root";
    std::string pathBiPo = __FILE__;
    pathBiPo = pathBiPo.substr(0, pathBiPo.find("scripts")) + "isotops/BiPo/BiPo_eCut_90.root";

    Double_t effB8;
    Int_t nSavedB8 = 0;
    Int_t nB8 = 0;

    Double_t effBiPo;
    Int_t nKilledBiPo = 0;
    Int_t nBiPo = 0;

    auto *treeB8 = new nsEsClusCoins(pathB8.c_str());
    auto *treeBiPo = new nsEsClusCoins(pathBiPo.c_str());

    Long64_t nbytes = 0, nb = 0;
    Long64_t nentriesB8 = treeB8->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesB8; jentry++) {
        Long64_t ientry = treeB8->LoadTree(jentry);
        if (ientry < 0) break;
        nb = treeB8->fChain->GetEntry(jentry);
        nbytes += nb;

        if ( tag == "(topo2)" && treeB8->topology == 2 ) {
            ++nB8;
            if ( treeB8->AC_E_calibrated > 0.96 && treeB8->eEM1_calibrated < 0.5 && treeB8->dotEM1_EM2 < -0.8) {
                ++nSavedB8;
            }
        } else if ( tag == "(topo2 && eAC <= 1.8 MeV)" && treeB8->topology == 2 && treeB8->AC_E_calibrated <= 1.8 ) {
            ++nB8;
            if ( treeB8->AC_E_calibrated > 0.96 && treeB8->eEM1_calibrated < 0.5 && treeB8->dotEM1_EM2 < -0.8) {
                ++nSavedB8;
            }
        }
    }

    effB8 = (Double_t) nSavedB8 / nB8;

    Long64_t nentriesBiPo = treeBiPo->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesBiPo; jentry++) {
        Long64_t ientry = treeBiPo->LoadTree(jentry);
        if (ientry < 0) break;
        nb = treeBiPo->fChain->GetEntry(jentry);
        nbytes += nb;

        if (tag == "(topo2)" && treeBiPo->topology == 2) {
            ++nBiPo;
            if ( treeBiPo->AC_E_calibrated < 0.96 && treeBiPo->eEM1_calibrated > 0.5 && treeBiPo->dotEM1_EM2 > -0.8) {
                ++nKilledBiPo;
            }
        } else if ( tag == "(topo2 && eAC <= 1.8 MeV)" && treeBiPo->topology == 2 && treeBiPo->AC_E_calibrated <= 1.8 ) {
            ++nBiPo;
            if ( treeBiPo->AC_E_calibrated < 0.96 && treeBiPo->eEM1_calibrated > 0.5 && treeBiPo->dotEM1_EM2 > -0.8) {
                ++nKilledBiPo;
            }
        }

    }

    effBiPo = (Double_t) nKilledBiPo / nBiPo;

    delete treeB8;
    delete treeBiPo;

    std::cout << "************" << "effB8: " << effB8 << "************" << std::endl;
    std::cout << "************" << "effBiPo: " << effBiPo << "************" << std::endl;


}


