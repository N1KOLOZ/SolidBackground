//
// Created by niko on 20.03.20.
//

// Local
#include "include/nsEsClusCoinsRoff.hh"

// ROOT
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


nsEsClusCoinsRoff::nsEsClusCoinsRoff(const std::string &fileName)
        : fChain(0)
{
    auto f = new TFile(fileName.c_str());
    auto tree = (TTree *) f->Get("nsEsClusCoins");
    Init(tree);
}

nsEsClusCoinsRoff::~nsEsClusCoinsRoff()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t nsEsClusCoinsRoff::GetEntry(Long64_t entry)
{
// Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t nsEsClusCoinsRoff::LoadTree(Long64_t entry)
{
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

void nsEsClusCoinsRoff::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    tRunStart = 0;
    promptChannels = 0;
    promptChanX = 0;
    promptChanY = 0;
    promptChanZ = 0;
    promptChanAmp = 0;
    promptChanTime = 0;
    promptChanTimeReco = 0;
    promptCCubeX = 0;
    promptCCubeY = 0;
    promptCCubeZ = 0;
    promptCCubeE = 0;
    promptCCubeE_calibrated = 0;
    promptCCubeAmp = 0;
    promptCCubeTimeReco = 0;
    ampD = 0;
    intD = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("cycleNum", &cycleNum, &b_cycleNum);
    fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
    fChain->SetBranchAddress("tRunStart", &tRunStart, &b_tRunStart);
    fChain->SetBranchAddress("htime", &htime, &b_htime);
    fChain->SetBranchAddress("time", &time, &b_time);
    fChain->SetBranchAddress("delt", &delt, &b_delt);
    fChain->SetBranchAddress("delx", &delx, &b_delx);
    fChain->SetBranchAddress("dely", &dely, &b_dely);
    fChain->SetBranchAddress("delz", &delz, &b_delz);
    fChain->SetBranchAddress("delr", &delr, &b_delr);
    fChain->SetBranchAddress("delx_ave", &delx_ave, &b_delx_ave);
    fChain->SetBranchAddress("dely_ave", &dely_ave, &b_dely_ave);
    fChain->SetBranchAddress("delz_ave", &delz_ave, &b_delz_ave);
    fChain->SetBranchAddress("delr_ave", &delr_ave, &b_delr_ave);
    fChain->SetBranchAddress("tNearestMuonType0", &tNearestMuonType0, &b_tNearestMuonType0);
    fChain->SetBranchAddress("tNearestMuonType1", &tNearestMuonType1, &b_tNearestMuonType1);
    fChain->SetBranchAddress("tNearestMuonType2", &tNearestMuonType2, &b_tNearestMuonType2);
    fChain->SetBranchAddress("tNearestNS", &tNearestNS, &b_tNearestNS);
    fChain->SetBranchAddress("xP", &xP, &b_xP);
    fChain->SetBranchAddress("yP", &yP, &b_yP);
    fChain->SetBranchAddress("zP", &zP, &b_zP);
    fChain->SetBranchAddress("xP_ave", &xP_ave, &b_xP_ave);
    fChain->SetBranchAddress("yP_ave", &yP_ave, &b_yP_ave);
    fChain->SetBranchAddress("zP_ave", &zP_ave, &b_zP_ave);
    fChain->SetBranchAddress("promptVolume", &promptVolume, &b_promptVolume);
    fChain->SetBranchAddress("promptEnergy", &promptEnergy, &b_promptEnergy);
    fChain->SetBranchAddress("energyDense", &energyDense, &b_energyDense);
    fChain->SetBranchAddress("promptEnergy_calibrated", &promptEnergy_calibrated, &b_promptEnergy_calibrated);
    fChain->SetBranchAddress("promptSCubeEnergyMostEnergetic", &promptSCubeEnergyMostEnergetic, &b_promptSCubeEnergyMostEnergetic);
    fChain->SetBranchAddress("promptCCubeEnergy_calibrated", &promptCCubeEnergy_calibrated, &b_promptCCubeEnergy_calibrated);
    fChain->SetBranchAddress("promptCCubeEnergyMostEnergetic_calibrated", &promptCCubeEnergyMostEnergetic_calibrated, &b_promptCCubeEnergyMostEnergetic_calibrated);
    fChain->SetBranchAddress("promptCCubeEnergyCrown_calibrated", &promptCCubeEnergyCrown_calibrated, &b_promptCCubeEnergyCrown_calibrated);
    fChain->SetBranchAddress("promptCCubeEnergyOutsideCrown_calibrated", &promptCCubeEnergyOutsideCrown_calibrated, &b_promptCCubeEnergyOutsideCrown_calibrated);
    fChain->SetBranchAddress("promptChannels", &promptChannels, &b_promptChannels);
    fChain->SetBranchAddress("promptChanX", &promptChanX, &b_promptChanX);
    fChain->SetBranchAddress("promptChanY", &promptChanY, &b_promptChanY);
    fChain->SetBranchAddress("promptChanZ", &promptChanZ, &b_promptChanZ);
    fChain->SetBranchAddress("promptChanAmp", &promptChanAmp, &b_promptChanAmp);
    fChain->SetBranchAddress("promptChanTime", &promptChanTime, &b_promptChanTime);
    fChain->SetBranchAddress("promptChanTimeReco", &promptChanTimeReco, &b_promptChanTimeReco);
    fChain->SetBranchAddress("promptNCCube", &promptNCCube, &b_promptNCCube);
    fChain->SetBranchAddress("promptCCubeX", &promptCCubeX, &b_promptCCubeX);
    fChain->SetBranchAddress("promptCCubeY", &promptCCubeY, &b_promptCCubeY);
    fChain->SetBranchAddress("promptCCubeZ", &promptCCubeZ, &b_promptCCubeZ);
    fChain->SetBranchAddress("promptCCubeE", &promptCCubeE, &b_promptCCubeE);
    fChain->SetBranchAddress("promptCCubeE_calibrated", &promptCCubeE_calibrated, &b_promptCCubeE_calibrated);
    fChain->SetBranchAddress("promptCCubeAmp", &promptCCubeAmp, &b_promptCCubeAmp);
    fChain->SetBranchAddress("promptCCubeTimeReco", &promptCCubeTimeReco, &b_promptCCubeTimeReco);
    fChain->SetBranchAddress("xD", &xD, &b_xD);
    fChain->SetBranchAddress("yD", &yD, &b_yD);
    fChain->SetBranchAddress("zD", &zD, &b_zD);
    fChain->SetBranchAddress("BiPonisher", &BiPonisher, &b_BiPonisher);
    fChain->SetBranchAddress("ampD", &ampD, &b_ampD);
    fChain->SetBranchAddress("intD", &intD, &b_intD);
    fChain->SetBranchAddress("NSClusTreePos", &NSClusTreePos, &b_NSClusTreePos);
    fChain->SetBranchAddress("NSIDTreePos", &NSIDTreePos, &b_NSIDTreePos);
    fChain->SetBranchAddress("ESClusTreePos", &ESClusTreePos, &b_ESClusTreePos);
    fChain->SetBranchAddress("ESIDTreePos", &ESIDTreePos, &b_ESIDTreePos);
    fChain->SetBranchAddress("inIBDbuffer", &inIBDbuffer, &b_inIBDbuffer);
    fChain->SetBranchAddress("topology", &topology, &b_topology);
    fChain->SetBranchAddress("eCubeAroundAC", &eCubeAroundAC, &b_eCubeAroundAC);
    fChain->SetBranchAddress("eCubeAroundAC_calibrated", &eCubeAroundAC_calibrated, &b_eCubeAroundAC_calibrated);
    fChain->SetBranchAddress("nCubeAroundAC", &nCubeAroundAC, &b_nCubeAroundAC);
    fChain->SetBranchAddress("EStSpread", &EStSpread, &b_EStSpread);
    fChain->SetBranchAddress("dotEM1_EM2", &dotEM1_EM2, &b_dotEM1_EM2);
    fChain->SetBranchAddress("distEM1_EM2", &distEM1_EM2, &b_distEM1_EM2);
    fChain->SetBranchAddress("distAC_EM1", &distAC_EM1, &b_distAC_EM1);
    fChain->SetBranchAddress("nCubesEM1", &nCubesEM1, &b_nCubesEM1);
    fChain->SetBranchAddress("posEM1_x", &posEM1_x, &b_posEM1_x);
    fChain->SetBranchAddress("posEM1_y", &posEM1_y, &b_posEM1_y);
    fChain->SetBranchAddress("posEM1_z", &posEM1_z, &b_posEM1_z);
    fChain->SetBranchAddress("eEM1", &eEM1, &b_eEM1);
    fChain->SetBranchAddress("eEM1_calibrated", &eEM1_calibrated, &b_eEM1_calibrated);
    fChain->SetBranchAddress("distAC_EM2", &distAC_EM2, &b_distAC_EM2);
    fChain->SetBranchAddress("nCubesEM2", &nCubesEM2, &b_nCubesEM2);
    fChain->SetBranchAddress("posEM2_x", &posEM2_x, &b_posEM2_x);
    fChain->SetBranchAddress("posEM2_y", &posEM2_y, &b_posEM2_y);
    fChain->SetBranchAddress("posEM2_z", &posEM2_z, &b_posEM2_z);
    fChain->SetBranchAddress("eEM2", &eEM2, &b_eEM2);
    fChain->SetBranchAddress("eEM2_calibrated", &eEM2_calibrated, &b_eEM2_calibrated);
    fChain->SetBranchAddress("AC_x", &AC_x, &b_AC_x);
    fChain->SetBranchAddress("AC_y", &AC_y, &b_AC_y);
    fChain->SetBranchAddress("AC_z", &AC_z, &b_AC_z);
    fChain->SetBranchAddress("AC_E", &AC_E, &b_AC_E);
    fChain->SetBranchAddress("AC_E_calibrated", &AC_E_calibrated, &b_AC_E_calibrated);
    fChain->SetBranchAddress("S_dotEM1_EM2", &S_dotEM1_EM2, &b_S_dotEM1_EM2);
    fChain->SetBranchAddress("S_eESnoPositron", &S_eESnoPositron, &b_S_eESnoPositron);
    fChain->SetBranchAddress("S_eC1", &S_eC1, &b_S_eC1);
    fChain->SetBranchAddress("S_eC2", &S_eC2, &b_S_eC2);
    fChain->SetBranchAddress("S_ncubeC1", &S_ncubeC1, &b_S_ncubeC1);
    fChain->SetBranchAddress("S_ncubeC2", &S_ncubeC2, &b_S_ncubeC2);
    fChain->SetBranchAddress("S_dotC1_C2", &S_dotC1_C2, &b_S_dotC1_C2);
    fChain->SetBranchAddress("S_distC1_AC", &S_distC1_AC, &b_S_distC1_AC);
    fChain->SetBranchAddress("S_distC2_AC", &S_distC2_AC, &b_S_distC2_AC);
    fChain->SetBranchAddress("CuPID_delw", &CuPID_delw, &b_CuPID_delw);
    fChain->SetBranchAddress("dot_ES1_ES2", &dot_ES1_ES2, &b_dot_ES1_ES2);
    fChain->SetBranchAddress("dot_ES1_NS", &dot_ES1_NS, &b_dot_ES1_NS);
    fChain->SetBranchAddress("dot_ESNS_NS", &dot_ESNS_NS, &b_dot_ESNS_NS);
    fChain->SetBranchAddress("ES1", &ES1, &b_ES1);
    fChain->SetBranchAddress("ES2", &ES2, &b_ES2);
    fChain->SetBranchAddress("ESNS", &ESNS, &b_ESNS);
    fChain->SetBranchAddress("ES1_calibrated", &ES1_calibrated, &b_ES1_calibrated);
    fChain->SetBranchAddress("ES2_calibrated", &ES2_calibrated, &b_ES2_calibrated);
    fChain->SetBranchAddress("ESNS_calibrated", &ESNS_calibrated, &b_ESNS_calibrated);
    Notify();
}

Bool_t nsEsClusCoinsRoff::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void nsEsClusCoinsRoff::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t nsEsClusCoinsRoff::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    return 1;
}

void nsEsClusCoinsRoff::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
