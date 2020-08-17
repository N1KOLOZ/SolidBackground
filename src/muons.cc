// Local
#include "include/muons.hh"

// ROOT
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

// System
#include <iostream>


muons::muons(const std::string &fileName)
        : fChain(0)
{
    auto f = new TFile(fileName.c_str());
    auto tree = (TTree *) f->Get("muons");
    Init(tree);
}

muons::~muons() {
    std::cout << "muons destructor" << std::endl;
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t muons::GetEntry(Long64_t entry) {
// Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t muons::LoadTree(Long64_t entry) {
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

void muons::Init(TTree *tree) {
    // Set object pointer
    startCube = 0;
    endCube = 0;
//    fitVerPos = 0;
//    fitHorPos = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
    fChain->SetBranchAddress("htime", &htime, &b_htime);
    fChain->SetBranchAddress("singlePlane", &singlePlane, &b_singlePlane);
    fChain->SetBranchAddress("type", &type, &b_type);
    fChain->SetBranchAddress("polar", &polar, &b_polar);
    fChain->SetBranchAddress("azimuth", &azimuth, &b_azimuth);
    fChain->SetBranchAddress("mx", &mx, &b_mx);
    fChain->SetBranchAddress("cx", &cx, &b_cx);
    fChain->SetBranchAddress("my", &my, &b_my);
    fChain->SetBranchAddress("cy", &cy, &b_cy);
    fChain->SetBranchAddress("trackLength", &trackLength, &b_trackLength);
    fChain->SetBranchAddress("stopped", &stopped, &b_stopped);
    fChain->SetBranchAddress("startCube", &startCube, &b_startCube);
    fChain->SetBranchAddress("endCube", &endCube, &b_endCube);
//    fChain->SetBranchAddress("fitVerPos", &fitVerPos, &b_fitVerPos);
//    fChain->SetBranchAddress("fitHorPos", &fitHorPos, &b_fitHorPos);
    Notify();
}

Bool_t muons::Notify() {
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void muons::Show(Long64_t entry) {
// Print contents of entry.
// If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t muons::Cut(Long64_t entry) {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    return 1;
}

void muons::Loop() {
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
    }
}
