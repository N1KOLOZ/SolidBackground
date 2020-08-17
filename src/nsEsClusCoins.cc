//Local
#include "include/nsEsClusCoins.hh"

// ROOT
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>

nsEsClusCoins::nsEsClusCoins(const char *fileName)
        : fChain(0)
{
    auto f = new TFile(fileName);
    auto tree = (TTree *) f->Get("DefaultReconstruction/nsEsClusCoins");

    Init(tree);
}

nsEsClusCoins::~nsEsClusCoins() {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t nsEsClusCoins::GetEntry(Long64_t entry) {
// Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t nsEsClusCoins::LoadTree(Long64_t entry) {
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

void nsEsClusCoins::Init(TTree *tree) {
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    promptCCubeX = 0;
    promptCCubeY = 0;
    promptCCubeZ = 0;
    promptCCubeE_calibrated = 0;
    eEM1X = 0;
    eEM1Y = 0;
    eEM1Z = 0;
    eEM1E_calibrated = 0;
    eEM2X = 0;
    eEM2Y = 0;
    eEM2Z = 0;
    eEM2E_calibrated = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("AC_x", &AC_x, &b_AC_x);
    fChain->SetBranchAddress("AC_y", &AC_y, &b_AC_y);
    fChain->SetBranchAddress("AC_z", &AC_z, &b_AC_z);
    fChain->SetBranchAddress("delt", &delt, &b_delt);
    fChain->SetBranchAddress("htime", &htime, &b_htime);
    fChain->SetBranchAddress("BiPonisher", &BiPonisher, &b_BiPonisher);
    fChain->SetBranchAddress("promptCCubeEnergyOutsideCrown_calibrated", &promptCCubeEnergyOutsideCrown_calibrated,
                             &b_promptCCubeEnergyOutsideCrown_calibrated);
    fChain->SetBranchAddress("promptCCubeEnergyInsideCrown_calibrated", &promptCCubeEnergyInsideCrown_calibrated,
                             &b_promptCCubeEnergyInsideCrown_calibrated);
    fChain->SetBranchAddress("promptNCCube", &promptNCCube, &b_promptNCCube);
    fChain->SetBranchAddress("topology", &topology, &b_topology);
    fChain->SetBranchAddress("EStSpread", &EStSpread, &b_EStSpread);
    fChain->SetBranchAddress("dotEM1_EM2", &dotEM1_EM2, &b_dotEM1_EM2);
    fChain->SetBranchAddress("dot_topo6_EM1_EM2", &dot_topo6_EM1_EM2, &b_dot_topo6_EM1_EM2);
    fChain->SetBranchAddress("distEM1_EM2", &distEM1_EM2, &b_distEM1_EM2);
    fChain->SetBranchAddress("distAC_EM1", &distAC_EM1, &b_distAC_EM1);
    fChain->SetBranchAddress("nCubesEM1", &nCubesEM1, &b_nCubesEM1);
    fChain->SetBranchAddress("posEM1_x", &posEM1_x, &b_posEM1_x);
    fChain->SetBranchAddress("posEM1_y", &posEM1_y, &b_posEM1_y);
    fChain->SetBranchAddress("posEM1_z", &posEM1_z, &b_posEM1_z);
    fChain->SetBranchAddress("eEM1_calibrated", &eEM1_calibrated, &b_eEM1_calibrated);
    fChain->SetBranchAddress("distAC_EM2", &distAC_EM2, &b_distAC_EM2);
    fChain->SetBranchAddress("nCubesEM2", &nCubesEM2, &b_nCubesEM2);
    fChain->SetBranchAddress("eEM2_calibrated", &eEM2_calibrated, &b_eEM2_calibrated);
    fChain->SetBranchAddress("AC_E_calibrated", &AC_E_calibrated, &b_AC_E_calibrated);
    fChain->SetBranchAddress("pair", &pair, &b_pair);
    fChain->SetBranchAddress("promptCCubeX", &promptCCubeX, &b_promptCCubeX);
    fChain->SetBranchAddress("promptCCubeY", &promptCCubeY, &b_promptCCubeY);
    fChain->SetBranchAddress("promptCCubeZ", &promptCCubeZ, &b_promptCCubeZ);
    fChain->SetBranchAddress("promptCCubeE_calibrated", &promptCCubeE_calibrated, &b_promptCCubeE_calibrated);
    fChain->SetBranchAddress("eEM1X", &eEM1X, &b_eEM1X);
    fChain->SetBranchAddress("eEM1Y", &eEM1Y, &b_eEM1Y);
    fChain->SetBranchAddress("eEM1Z", &eEM1Z, &b_eEM1Z);
    fChain->SetBranchAddress("eEM1E_calibrated", &eEM1E_calibrated, &b_eEM1E_calibrated);
    fChain->SetBranchAddress("eEM2X", &eEM2X, &b_eEM2X);
    fChain->SetBranchAddress("eEM2Y", &eEM2Y, &b_eEM2Y);
    fChain->SetBranchAddress("eEM2Z", &eEM2Z, &b_eEM2Z);
    fChain->SetBranchAddress("eEM2E_calibrated", &eEM2E_calibrated, &b_eEM2E_calibrated);
    fChain->SetBranchAddress("cycleNum", &cycleNum, &b_cycleNum);
    Notify();
}

Bool_t nsEsClusCoins::Notify() {
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void nsEsClusCoins::Show(Long64_t entry) {
// Print contents of entry.
// If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t nsEsClusCoins::Cut(Long64_t entry) {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    return 1;
}

void nsEsClusCoins::Loop() {
//   In a ROOT session, you can do:
//      root> .L nsEsClusCoins.C
//      root> nsEsClusCoins t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
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
