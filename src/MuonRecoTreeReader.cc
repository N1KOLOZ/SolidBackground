//
// Created by niko on 13.04.20.
//

// Local
#include "include/MuonRecoTreeReader.hh"

// ROOT
#include <TH2.h>
#include <TStyle.h>

// System
#include <iostream>

MuonRecoTreeReader::MuonRecoTreeReader(const std::string &filePath) :
        fChain(0)
{
    auto f = new TFile(filePath.c_str(), "READ");
    auto tree = (TTree *) f->Get("MuonReco");
    Init(tree);
}

MuonRecoTreeReader::~MuonRecoTreeReader() {
    std::cout << "MuonRecoTreeReader destructor" << std::endl;
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t MuonRecoTreeReader::GetEntry(Long64_t entry) {
// Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t MuonRecoTreeReader::LoadTree(Long64_t entry) {
// Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void MuonRecoTreeReader::Init(TTree *tree) {
    // Set object pointer
    xCube = 0;
    yCube = 0;
    zCube = 0;
    startCube = 0;
    endCube = 0;

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("xCube", &xCube, &b_xCube);
    fChain->SetBranchAddress("yCube", &yCube, &b_yCube);
    fChain->SetBranchAddress("zCube", &zCube, &b_zCube);
    fChain->SetBranchAddress("startCube", &startCube, &b_startCube);
    fChain->SetBranchAddress("endCube", &endCube, &b_endCube);
    fChain->SetBranchAddress("mx", &mx, &b_mx);
    fChain->SetBranchAddress("cx", &cx, &b_cx);
    fChain->SetBranchAddress("my", &my, &b_my);
    fChain->SetBranchAddress("cy", &cy, &b_cy);
    fChain->SetBranchAddress("htime", &htime, &b_htime);
    Notify();
}

Bool_t MuonRecoTreeReader::Notify() {
    return kTRUE;
}

void MuonRecoTreeReader::Show(Long64_t entry) {
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t MuonRecoTreeReader::Cut(Long64_t entry) {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    return 1;
}
