//
// Created by niko on 21.02.20.
//

// Local
#include "include/B8vsBiPoAnalysis.hh"
#include "include/nsEsClusCoins.hh"
#include "include/HistoAnalysis.hh"
#include "include/nikoStyle.hh"

// System
#include <iostream>
#include <string>
#include <sstream>

// ROOT
#include "TH1F.h"



void B8vsBiPoAnalysis(std::string tag) {
    char const *pathB8 = "/home/niko/SOLID/SolidBackground/sources/B8/newB8_eCut_90.root";
    char const *pathBiPo = "/home/niko/SOLID/SolidBackground/sources/BiPo/newBiPo_eCut_90.root";

    auto treeB8 = new nsEsClusCoins(pathB8);
    auto treeBiPo = new nsEsClusCoins(pathBiPo);

    Int_t noTopo2B8 = 0 ;
    Int_t noTopo2BiPo = 0;

    std::vector<Double_t> B8_topo;
    std::vector<Double_t> BiPo_topo;

    std::vector<Double_t> B8_AC_E_calibrated;
    std::vector<Double_t> B8_dotEM1_EM2;
    std::vector<Double_t> B8_distEM1_EM2;
    std::vector<Double_t> B8_distAC_EM1;
    std::vector<Double_t> B8_distAC_EM2;
    std::vector<Double_t> B8_eEM1_calibrated;
    std::vector<Double_t> B8_eEM2_calibrated;
    std::vector<Double_t> B8_promptNCCube;
    //
    std::vector<Double_t> B8_nCubesEM1;
    std::vector<Double_t> B8_nCubesEM2;

    std::vector<Double_t> BiPo_AC_E_calibrated;
    std::vector<Double_t> BiPo_dotEM1_EM2;
    std::vector<Double_t> BiPo_distEM1_EM2;
    std::vector<Double_t> BiPo_distAC_EM1;
    std::vector<Double_t> BiPo_distAC_EM2;
    std::vector<Double_t> BiPo_eEM1_calibrated;
    std::vector<Double_t> BiPo_eEM2_calibrated;
    std::vector<Double_t> BiPo_promptNCCube;
    //
    std::vector<Double_t> BiPo_nCubesEM1;
    std::vector<Double_t> BiPo_nCubesEM2;

    Long64_t nentriesB8 = treeB8->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesB8; jentry++) {
        Long64_t ientry = treeB8->LoadTree(jentry);
        if (ientry < 0) break;
        treeB8->fChain->GetEntry(jentry);

        B8_topo.push_back(treeB8->topology);

        if (tag != "") {
            if (tag == "(topo2)" && treeB8->topology != 2)
                continue;
            if (tag == "(topo2 && eAC <= 2 MeV)" && (treeB8->topology != 2 || treeB8->AC_E_calibrated > 2) )
                continue;
        }

        if (treeB8->topology == 2 ) ++noTopo2B8;

        B8_AC_E_calibrated.push_back(treeB8->AC_E_calibrated);
        B8_dotEM1_EM2.push_back(treeB8->dotEM1_EM2);
        B8_distAC_EM1.push_back(treeB8->distAC_EM1);
        B8_distAC_EM2.push_back(treeB8->distAC_EM2);
        B8_distEM1_EM2.push_back(treeB8->distEM1_EM2);
        B8_eEM1_calibrated.push_back(treeB8->eEM1_calibrated);
        B8_eEM2_calibrated.push_back(treeB8->eEM2_calibrated);
        B8_promptNCCube.push_back(treeB8->promptNCCube);

        B8_nCubesEM1.push_back(treeB8->nCubesEM1);
        B8_nCubesEM2.push_back(treeB8->nCubesEM2);
    }

    Long64_t nentriesBiPo = treeBiPo->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesBiPo; jentry++) {
        Long64_t ientry = treeBiPo->LoadTree(jentry);
        if (ientry < 0) break;
        treeBiPo->fChain->GetEntry(jentry);

        BiPo_topo.push_back(treeBiPo->topology);

        if (tag != "") {
            if (tag == "(topo2)" && treeBiPo->topology != 2)
                continue;
            if (tag == "(topo2 && eAC <= 2 MeV)" && (treeBiPo->topology != 2 || treeBiPo->AC_E_calibrated > 2) )
                continue;
        }

        if (treeBiPo->topology == 2) ++noTopo2BiPo;

        BiPo_AC_E_calibrated.push_back(treeBiPo->AC_E_calibrated);
        BiPo_dotEM1_EM2.push_back(treeBiPo->dotEM1_EM2);

        BiPo_distAC_EM1.push_back(treeBiPo->distAC_EM1);
        BiPo_distAC_EM2.push_back(treeBiPo->distAC_EM2);
        BiPo_distEM1_EM2.push_back(treeBiPo->distEM1_EM2);
        BiPo_eEM1_calibrated.push_back(treeBiPo->eEM1_calibrated);
        BiPo_eEM2_calibrated.push_back(treeBiPo->eEM2_calibrated);
        BiPo_promptNCCube.push_back(treeBiPo->promptNCCube);

        BiPo_nCubesEM1.push_back(treeBiPo->nCubesEM1);
        BiPo_nCubesEM2.push_back(treeBiPo->nCubesEM2);
    }


    delete treeB8;
    delete treeBiPo;

    std::string title;
    title = "AC_E_calibrated " + tag;

    if (tag == "(topo2 && eAC <= 1.8 MeV)") {
        Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), "MeV",30, 0., 2., B8_AC_E_calibrated, BiPo_AC_E_calibrated);
    } else {
        Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), "MeV",100, 0., 14., B8_AC_E_calibrated, BiPo_AC_E_calibrated);
    }

    title = "dotEM1_EM2 " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",10, -1., 0., B8_dotEM1_EM2, BiPo_dotEM1_EM2);

    title = "distEM1_EM2 " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",20, 0., 20., B8_distEM1_EM2, BiPo_distEM1_EM2);
    title = "distAC_EM1 " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",16, 0., 16., B8_distAC_EM1, BiPo_distAC_EM1);
    title = "distAC_EM2 " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",16, 0., 16., B8_distAC_EM2, BiPo_distAC_EM2);

    title = "eEM1_calibrated " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), "MeV", 50, 0., 2.1, B8_eEM1_calibrated, BiPo_eEM1_calibrated);
    title = "eEM2_calibrated " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), "MeV", 100, 0., 2.1, B8_eEM2_calibrated, BiPo_eEM2_calibrated);

    title = "nCubesEM1 " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",12, 0., 12., B8_nCubesEM1, BiPo_nCubesEM1);
    title = "nCubesEM2 " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",12, 0., 12., B8_nCubesEM2, BiPo_nCubesEM2);

    title = "promptNCCube " + tag;
    Plot2NormalizedHistos("MC B8", "MC BiPo", title.c_str(), " ",15, 0., 15., B8_promptNCCube, BiPo_promptNCCube);

    std::cout << "B8vsBiPoAnalysis is successfully finished" << std::endl;
}


// !!! fix normalization topo2 3412 || 1113
// !!! fix normalization topo7 16891||6880
// !!! fix normalization topo10 1683||2400