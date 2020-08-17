//
// Created by niko on 04.03.20.
//

// Local
#include "include/MuonToB8Analysis.hh"

#include "include/nikoStyle.hh"

#include "include/MuonTrackFinder.hh"
#include "include/MuonTools.hh"
#include "include/MuonVisualization.hh"

#include "include/muons.hh"
#include "include/nsEsClusCoinsRoff.hh"
#include "include/MuonRoffTreeWriter.hh"

#include "include/MuonRecoTreeWriter.hh"
#include "include/MuonRecoTreeReader.hh"

// System
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <algorithm>
#include <thread>
#include <chrono>

// ROOT

#include "TH1D.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TPolyLine3D.h"
#include "TLine.h"
#include "TStyle.h"
#include "TSystemDirectory.h"
#include "TFile.h"


// Saves all names of files in the directory with the specified extension
void GetListOfFiles(
        std::vector<std::string>& listOfFiles,
        const std::string &dirPath,
        const std::string &ext)
{
    auto dir = new TSystemDirectory(dirPath.c_str(), dirPath.c_str());
    auto files = dir->GetListOfFiles();

    if (files) {
        for (TIter it = files->begin(); it != files->end(); ++it) {
            TSystemFile *file = (TSystemFile *) *it;
            TString fileName = file->GetName();

            if (!file->IsDirectory() && fileName.EndsWith(ext.c_str())) {
                listOfFiles.emplace_back(fileName.Data());
            }
        }
    }

    std::sort(listOfFiles.begin(), listOfFiles.end());
    delete dir;
}

//    Building a cylinder which encompasses muon track
void BuildCylinder(const Muon& muon, Points& muonCylinder) {
    auto muonTrackFinder = MuonTrackFinder(muon);
    muonCylinder = muonTrackFinder.GetTrack();
}

void MakeMuonReco() {
    std::string RoffDirPath = __FILE__;
    RoffDirPath = RoffDirPath.substr(0, RoffDirPath.find("/scripts")) + "/sources/Roff";

    std::vector<std::string> listOfFiles;
    GetListOfFiles(listOfFiles, RoffDirPath, ".root");
    std::cout << "List of files:" << std::endl;
    for (const auto &fileName : listOfFiles) {
        std::cout << fileName << std::endl;
    }

    for (const auto &fileName : listOfFiles) {
        std::this_thread::sleep_for (std::chrono::seconds(2));
        gROOT->Reset();

        std::string muonRecoName = fileName.substr(0, fileName.find(".root")) + "_Reco.root";
        std::string muonRecoPath = __FILE__;
        muonRecoPath = muonRecoPath.substr(0, muonRecoPath.find("/scripts"))
                + "/output/Roff/" + muonRecoName;
        std::string muonPath = RoffDirPath + "/" + fileName;

        std::cout << muonRecoPath << std::endl;
        std::cout << muonPath << std::endl;

        auto treeMuon = new muons(muonPath);
        auto muonRecoTreeWriter = new MuonRecoTreeWriter(muonRecoPath);

        Long64_t nOfmuons = 0;
        Long64_t nentriesMuons = treeMuon->fChain->GetEntriesFast();
        for (Long64_t jentry = 0; jentry < nentriesMuons; jentry++) {
            std::cout << "MakeMuonReco | MuonRecoTreeWriter " << jentry << std::endl;
//            if (jentry == 1000) break;
            treeMuon->fChain->GetEntry(jentry);

            if (treeMuon->startCube->at(0) != -1) {
                std::cout << fileName << ": " << jentry <<  std::endl;

                auto muon = Muon(
                        treeMuon->startCube->at(0),
                        treeMuon->startCube->at(1),
                        treeMuon->startCube->at(2),
                        treeMuon->endCube->at(0),
                        treeMuon->endCube->at(1),
                        treeMuon->endCube->at(2),
                        treeMuon->htime * 25,
                        treeMuon->mx,
                        treeMuon->my,
                        treeMuon->cx,
                        treeMuon->cy);

                Points muonCylinder;
                try {
                    BuildCylinder(muon, muonCylinder);
                    ++nOfmuons;
                } catch(const std::exception& e) {
                    std::cerr << "Exception is caught: " << e.what() << std::endl;
                }

                muonRecoTreeWriter->Fill(muon, muonCylinder);
            }
        }
        muonRecoTreeWriter->Write();
        delete treeMuon;
        delete muonRecoTreeWriter;
        treeMuon = 0;
        muonRecoTreeWriter = 0;

        std::cout << "Number of muons: " << nOfmuons << std::endl;
        std::cout << "Number of fails: " << nentriesMuons - nOfmuons << std::endl;
    }
}

void ReadMuonReco(const std::string &fileName, std::map<Double_t, Points> &htimeToCylinder) {
    std::string fileMuonRecoName = fileName.substr(0, fileName.find(".root")) + "_Reco.root";

    std::string fileMuonRecoPath = __FILE__;
    fileMuonRecoPath = fileMuonRecoPath.substr(0, fileMuonRecoPath.find("/scripts"))
                       + "/output/Roff/" + fileMuonRecoName;

    std::cout << fileMuonRecoPath << std::endl;

    std::vector<Muon> muons;
    std::vector<Points> cylinders;
    auto muonCylinderTreeReader = new MuonRecoTreeReader(fileMuonRecoPath.c_str());
    Long64_t nentries = muonCylinderTreeReader->fChain->GetEntriesFast();

    Int_t count = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        std::cout << "ReadMuonReco | MuonCylinderTreeReader " << jentry << std::endl;

//            if (count == 10) break;
//            ++count;

        muonCylinderTreeReader->fChain->GetEntry(jentry);

        Points muonCylinder;
        for (int i = 0; i < muonCylinderTreeReader->xCube->size(); ++i) {
            muonCylinder.emplace_back(muonCylinderTreeReader->xCube->at(i),
                                      muonCylinderTreeReader->yCube->at(i),
                                      muonCylinderTreeReader->zCube->at(i));
        }

        htimeToCylinder[muonCylinderTreeReader->htime] = muonCylinder;

        // each cluster 25 ns
        if (count == -1) {
            muons.emplace_back(Muon(
                    muonCylinderTreeReader->startCube->at(0),
                    muonCylinderTreeReader->startCube->at(1),
                    muonCylinderTreeReader->startCube->at(2),
                    muonCylinderTreeReader->endCube->at(0),
                    muonCylinderTreeReader->endCube->at(1),
                    muonCylinderTreeReader->endCube->at(2),
                    muonCylinderTreeReader->htime * 25,
                    muonCylinderTreeReader->mx,
                    muonCylinderTreeReader->my,
                    muonCylinderTreeReader->cx,
                    muonCylinderTreeReader->cy));
            cylinders.push_back(muonCylinder);
        }
    }
    delete muonCylinderTreeReader;
    muonCylinderTreeReader = 0;
//
 /*   auto muonVisualisation = new MuonVisualization();
    muonVisualisation->Visualize(muons[0], cylinders[0]);
    return;*/
}

void SaveIndexes() {
    std::cout << "SaveIndexes started" << std::endl;

    std::string RoffDirPath = __FILE__;
    RoffDirPath = RoffDirPath.substr(0, RoffDirPath.find("/scripts")) + "/sources/Roff";

    std::vector<std::string> listOfFiles;
    GetListOfFiles(listOfFiles, RoffDirPath, ".root");
    std::cout << "List of files:" << std::endl;
    // example "2018_07_13_muons.root"
    for (const auto &fileName : listOfFiles) {
        std::cout << fileName << std::endl;
    }

    for (const auto &fileName : listOfFiles) {
        std::map<Double_t, Points> htimeToCylinder;
        ReadMuonReco(fileName, htimeToCylinder);

        auto hist = new TH1D("hist", "hist", 200, 0.0, 16.0);
        std::vector<Int_t> eventIndexes;

        UInt_t nOfACcubes = 0;
        UInt_t nOfMuons = htimeToCylinder.size();

        std::string RoffPath = RoffDirPath + "/" + fileName;
        auto treeCoins = new nsEsClusCoinsRoff(RoffPath);
        Long64_t nentriesMuons = treeCoins->fChain->GetEntriesFast();
        for (Long64_t jentry = 0; jentry < nentriesMuons; jentry++) {
            treeCoins->fChain->GetEntry(jentry);
            std::cout << "SaveIndexes | nsEsClusCoinsRoff " << jentry << " htime " << treeCoins->htime << std::endl;

            if (treeCoins->delt < 0 && (treeCoins->topology == 2 || treeCoins->topology == 7 || treeCoins->topology == 10) ) {
                Point AC = Point(treeCoins->AC_x, treeCoins->AC_y, treeCoins->AC_z);

                auto itStart = htimeToCylinder.lower_bound(treeCoins->htime - 1000000000); // - 1 sec
                auto itEnd = htimeToCylinder.upper_bound(treeCoins->htime - 100000000); // - 0.1 sec

                bool isBreak = false;
                for (auto it = itStart; it != itEnd; ++it) {
                    for (const auto &point : it->second) {
                        if (Point(point.x, point.y, point.z) == AC) {
                            ++nOfACcubes;
                            eventIndexes.push_back(jentry);
                            hist->Fill(treeCoins->AC_E_calibrated);
                            isBreak = true;
                            break;
                        }
                    }
                    if (isBreak) break;
                }
            }
        }
        delete treeCoins;
        std::cout << "nOfACcubes " << nOfACcubes << std::endl;
        std::cout << "nOfMuons " << nOfMuons << std::endl;

        auto canv = new TCanvas("canv", "canv", 0, 0, 600, 600);
        hist->Draw();
        canv->SaveAs(fileName.c_str());
        delete hist;
        delete canv;

        std::string outputPath = __FILE__;
        outputPath = outputPath.substr(0, outputPath.find("/script"))
                + "/output/Roff/indexes/" + fileName.substr(0, fileName.find(".root")) + "_Topo.txt";

        std::cout << outputPath << std::endl;

        std::ofstream output;
        output.open(outputPath);
        if (output.is_open()) {
            std::cout << "Writing to " << outputPath << std::endl;
            output << eventIndexes.size() << std::endl;

            for (auto i : eventIndexes) {
                output << i << std::endl;
            }
        }
        output.close();
    }
}

void MakeProcessedRoffTree() {
    std::cout << "MakeProcessedRoffTree started" << std::endl;

    std::string indexesDirPath = __FILE__;
    indexesDirPath = indexesDirPath.substr(0, indexesDirPath.find("/scripts")) + "/output/Roff/indexes";

    std::string RoffDirPath = __FILE__;
    RoffDirPath = RoffDirPath.substr(0, RoffDirPath.find("/scripts")) + "/sources/Roff";

    std::string outputDirPath = __FILE__;
    outputDirPath = outputDirPath.substr(0, outputDirPath.find("/scripts")) + "/sources/RoffProcessed";

    std::vector<std::string> listOfFiles;
    GetListOfFiles(listOfFiles, RoffDirPath, ".root");
    std::cout << "List of files:" << std::endl;
    // example "2018_07_13_muons.root"
    for (const auto &fileName : listOfFiles) {
        std::cout << fileName << std::endl;
    }

    std::cout << indexesDirPath << std::endl;
    std::cout << RoffDirPath << std::endl;


    for (const std::string &fileName : listOfFiles) {
        std::string RoffPath = RoffDirPath + "/" + fileName;
        std::string indexesPath = indexesDirPath + "/" + fileName.substr(0, fileName.find(".root")) + "_Topo.txt";
        std::string outputPath = outputDirPath + "/" + fileName;

        std::vector<Int_t> indexes;
        std::ifstream input;
        input.open(indexesPath);
        if (input.is_open()) {
            Int_t N = 0;
            input >> N;
            std::cout << "N = " << N << std::endl;
            Int_t value;
            for (int i = 0; i < N; ++i) {
                input >> value;
                indexes.push_back(value);
            }
        }
        input.close();

        auto nsEsClusCoinsRoffTree = new nsEsClusCoinsRoff(RoffPath);
        auto muonRoffTreeWriter = new MuonRoffTreeWriter(outputPath);
//        muonRoffTreeWriter->Cd();
        for (auto jentry : indexes) {
            nsEsClusCoinsRoffTree->fChain->GetEntry(jentry);
            std::cout << "MakeProcessedRoffTree | nsEsClusCoinsRoff " << jentry  << std::endl;

            Roff roff = {nsEsClusCoinsRoffTree->cycleNum,
                         nsEsClusCoinsRoffTree->runNumber,
                         nsEsClusCoinsRoffTree->htime,
                         nsEsClusCoinsRoffTree->time,
                         nsEsClusCoinsRoffTree->delt,
                         nsEsClusCoinsRoffTree->delr,
                         nsEsClusCoinsRoffTree->BiPonisher,
                         nsEsClusCoinsRoffTree->topology,
                         nsEsClusCoinsRoffTree->EStSpread,
                         nsEsClusCoinsRoffTree->dotEM1_EM2,
                         nsEsClusCoinsRoffTree->distEM1_EM2,
                         nsEsClusCoinsRoffTree->distAC_EM1,
                         nsEsClusCoinsRoffTree->nCubesEM1,
                         nsEsClusCoinsRoffTree->eEM1_calibrated,
                         nsEsClusCoinsRoffTree->distAC_EM2,
                         nsEsClusCoinsRoffTree->nCubesEM2,
                         nsEsClusCoinsRoffTree->eEM2_calibrated,
                         nsEsClusCoinsRoffTree->AC_E_calibrated,
                         nsEsClusCoinsRoffTree->ES1_calibrated,
                         nsEsClusCoinsRoffTree->ES2_calibrated,
                         };

            muonRoffTreeWriter->Fill(roff);
        }
        muonRoffTreeWriter->Write();
        delete nsEsClusCoinsRoffTree;
        delete muonRoffTreeWriter;
        nsEsClusCoinsRoffTree = 0;
        muonRoffTreeWriter = 0;
    }
}


void MergeTxt() {
    std::string indexesDirPath = __FILE__;
    indexesDirPath = indexesDirPath.substr(0, indexesDirPath.find("/scripts")) + "/output/Roff/topo";

    std::string outputDirPath = __FILE__;
    outputDirPath = outputDirPath.substr(0, outputDirPath.find("/scripts")) + "/output/Roff/indexes";

    std::vector<std::string> listOfFiles;
    GetListOfFiles(listOfFiles, indexesDirPath, ".txt");
    std::cout << "List of files:" << std::endl;
    // example "2018_07_13_muons.txt"
    for (const auto &fileName : listOfFiles) {
        std::cout << fileName << std::endl;
    }

    std::set<Int_t> indexes;
    Int_t sum = 0;
    for (const auto &fileName : listOfFiles) {
        std::string filePath = indexesDirPath + "/" + fileName;
        std::cout << filePath << std::endl;
        std::ifstream input;
        input.open(filePath);
        if (input.is_open()) {
            Int_t N = 0;
            input >> N;
            sum += N;
            std::cout << "N = " << N << std::endl;
            Int_t value;
            for (int i = 0; i < N; ++i) {
                input >> value;
                indexes.insert(value);
            }
        }
    }

    std::ofstream output;
    output.open(listOfFiles[0].substr(0, listOfFiles[0].find("_Cylinder")) + "_Topo.txt");

    output << indexes.size() << std::endl;
    for (auto i : indexes) {
        output << i << std::endl;
    }
    output.close();
}


void Check() {
    // just checks if the path is right
    std::string outputPath = __FILE__;
    std::string fileName = "niko.root";
    outputPath = outputPath.substr(0, outputPath.find("/script"))
                 + "/output/Roff/indexes/" + fileName.substr(0, fileName.find(".root")) + "_Topo.txt";

    std::cout << outputPath << std::endl;
}


void InvestigateTopo2() {
    std::string inputPath = __FILE__;
    inputPath = inputPath.substr(0, inputPath.find("/script"))
                + "/sources/RoffProcessed/" + "RoffProcessed.root";

    std::string outputPath = __FILE__;
    outputPath = outputPath.substr(0, outputPath.find("/script"))
                 + "/output/Roff/topo2/" + "output.root";

    Double_t AC_E_min = 0;
    Double_t AC_E_max = 5;
    Double_t BiPonisher_min = 1.0;
    Double_t BiPonisher_max = 3.0;
    Double_t delt_min = -600000.0;
    Double_t delt_max = 0.0;
    auto histAC_E = new TH1D("histAC_E", "AC_E", 50, AC_E_min, AC_E_max);
    auto histBiPo = new TH1D("histBiPo", "BiPonisher", 100, BiPonisher_min, BiPonisher_max);
    auto histdelt = new TH1D("histdelt", "delt", 100, delt_min, delt_max);
    auto histeEM1 = new TH1D("histeEM1", "eEM1", 100, 0, 6);
    auto histedotEM1_EM2 = new TH1D("histedotEM1_EM2", "dotEM1_EM2", 100, -1, 0);
    auto histdelr = new TH1D("histdelr", "delr", 50, 0, 50);

    auto nsEsClusCoinsRoffTree = new nsEsClusCoinsRoff(inputPath);
    Long64_t nentriesMuons = nsEsClusCoinsRoffTree->fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentriesMuons; jentry++) {
        nsEsClusCoinsRoffTree->fChain->GetEntry(jentry);

        if (nsEsClusCoinsRoffTree->topology == 7) {
            histAC_E->Fill(nsEsClusCoinsRoffTree->AC_E_calibrated);
            if (nsEsClusCoinsRoffTree->AC_E_calibrated > AC_E_min && nsEsClusCoinsRoffTree->AC_E_calibrated < AC_E_max) {
                if (nsEsClusCoinsRoffTree->BiPonisher > BiPonisher_min && nsEsClusCoinsRoffTree->BiPonisher < BiPonisher_max) {
                    if (nsEsClusCoinsRoffTree->eEM1_calibrated > 0.0 && nsEsClusCoinsRoffTree->eEM1_calibrated < 0.4) {
                        if (nsEsClusCoinsRoffTree->dotEM1_EM2 > -1.0 && nsEsClusCoinsRoffTree->dotEM1_EM2 < -0.88) {

//                            histBiPo->Fill(nsEsClusCoinsRoffTree->BiPonisher);
//                            histdelt->Fill(nsEsClusCoinsRoffTree->delt);
//                            histeEM1->Fill(nsEsClusCoinsRoffTree->eEM1_calibrated);
//                            histdelr->Fill(nsEsClusCoinsRoffTree->delr);
//                            histedotEM1_EM2->Fill(nsEsClusCoinsRoffTree->dotEM1_EM2);
                        }
                    }

                }
            }

        }
    }

    auto canv = new TCanvas("canv", "canv", 0, 0, 1000, 800);

    gStyle->SetOptStat(0);

    histAC_E->GetYaxis()->SetTitleOffset(1.5);
    histAC_E->SetLineColor(EColor::kBlack);
    histAC_E->SetFillColorAlpha(EColor::kRed, 0.35);
    histAC_E->SetMarkerStyle(8);
    histAC_E->SetMarkerSize(0.5);
    histAC_E->GetXaxis()->SetTitle("AC_E_calibrated [MeV]");
    histAC_E->GetYaxis()->SetTitle("Events");
    histAC_E->Draw("HIST, E");
    canv->Update();
    canv->SaveAs("AC_E.png");

    histBiPo->GetYaxis()->SetTitleOffset(1.5);
    histBiPo->SetLineColor(EColor::kBlack);
    histBiPo->SetFillColorAlpha(EColor::kRed, 0.35);
    histBiPo->SetMarkerStyle(8);
    histBiPo->SetMarkerSize(0.5);
    histBiPo->GetXaxis()->SetTitle("BiPonisher");
    histBiPo->GetYaxis()->SetTitle("Events");
    histBiPo->Draw("HIST, E");
    canv->Update();
    canv->SaveAs("BiPo.png");

    histdelt->GetYaxis()->SetTitleOffset(1.5);
    histdelt->SetLineColor(EColor::kBlack);
    histdelt->SetFillColorAlpha(EColor::kRed, 0.35);
    histdelt->SetMarkerStyle(8);
    histdelt->SetMarkerSize(0.5);
    histdelt->GetXaxis()->SetTitle("delt [ns]");
    histdelt->GetYaxis()->SetTitle("Events");
    histdelt->Draw("HIST, E");
    canv->Update();
    canv->SaveAs("delt.png");

    histeEM1->GetYaxis()->SetTitleOffset(1.5);
    histeEM1->SetLineColor(EColor::kBlack);
    histeEM1->SetFillColorAlpha(EColor::kRed, 0.35);
    histeEM1->SetMarkerStyle(8);
    histeEM1->SetMarkerSize(0.5);
    histeEM1->GetXaxis()->SetTitle("eEM1 [MeV]");
    histeEM1->GetYaxis()->SetTitle("Events");
    histeEM1->Draw("HIST, E");
    canv->Update();
    canv->SaveAs("eEM1.png");

    histedotEM1_EM2->GetYaxis()->SetTitleOffset(1.5);
    histedotEM1_EM2->SetLineColor(EColor::kBlack);
    histedotEM1_EM2->SetFillColorAlpha(EColor::kRed, 0.35);
    histedotEM1_EM2->SetMarkerStyle(8);
    histedotEM1_EM2->SetMarkerSize(0.5);
    histedotEM1_EM2->GetXaxis()->SetTitle("dotEM1_EM2");
    histedotEM1_EM2->GetYaxis()->SetTitle("Events");
    histedotEM1_EM2->Draw("HIST, E");
    canv->Update();
    canv->SaveAs("dotEM1_EM2.png");

    histdelr->GetYaxis()->SetTitleOffset(1.5);
    histdelr->SetLineColor(EColor::kBlack);
    histdelr->SetFillColorAlpha(EColor::kRed, 0.35);
    histdelr->SetMarkerStyle(8);
    histdelr->SetMarkerSize(0.5);
    histdelr->GetXaxis()->SetTitle("delr");
    histdelr->GetYaxis()->SetTitle("Events");
    histdelr->Draw("HIST, E");
    canv->Update();
    canv->SaveAs("delr.png");

    auto outputFile = new TFile(outputPath.c_str(), "RECREATE");
    histAC_E->Write("histACe");
    histBiPo->Write("histBiPo");
    histdelt->Write("histdelt");
    histeEM1->Write("histeEM1");
    histedotEM1_EM2->Write("histedotEM1_EM2");
    outputFile->Write();
    outputFile->Close();
}

void VisualizeTrack(Int_t entry) {
    std::string fileMuonRecoName = "2018_07_11_muons_Cylinder.root";

    std::string fileMuonRecoPath = __FILE__;
    fileMuonRecoPath = fileMuonRecoPath.substr(0, fileMuonRecoPath.find("/scripts"))
                       + "/output/Roff/" + fileMuonRecoName;

    std::cout << fileMuonRecoPath << std::endl;

    auto muonCylinderTreeReader = new MuonRecoTreeReader(fileMuonRecoPath.c_str());
    Long64_t nentries = muonCylinderTreeReader->fChain->GetEntriesFast();

    Int_t count = 0;

    muonCylinderTreeReader->fChain->GetEntry(entry);

    Points cylinder;
    for (int i = 0; i < muonCylinderTreeReader->xCube->size(); ++i) {
        cylinder.emplace_back(muonCylinderTreeReader->xCube->at(i),
                muonCylinderTreeReader->yCube->at(i),
                muonCylinderTreeReader->zCube->at(i));
    }

    Muon muon = Muon(
                    muonCylinderTreeReader->startCube->at(0),
                    muonCylinderTreeReader->startCube->at(1),
                    muonCylinderTreeReader->startCube->at(2),
                    muonCylinderTreeReader->endCube->at(0),
                    muonCylinderTreeReader->endCube->at(1),
                    muonCylinderTreeReader->endCube->at(2),
                    muonCylinderTreeReader->htime * 25,
                    muonCylinderTreeReader->mx,
                    muonCylinderTreeReader->my,
                    muonCylinderTreeReader->cx,
                    muonCylinderTreeReader->cy);

    delete muonCylinderTreeReader;
    muonCylinderTreeReader = 0;

    auto muonVisualisation = new MuonVisualization();
    muonVisualisation->Visualize(muon, cylinder);
    return;
}


