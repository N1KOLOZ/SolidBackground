//
// Created by niko on 21.02.20.
//

#ifndef nsEsClusCoins_hh
#define nsEsClusCoins_hh

// System
#include <vector>

// ROOT
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class nsEsClusCoins {
public :
    TTree *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

// Declaration of leaf types
    Int_t AC_x;
    Int_t AC_y;
    Int_t AC_z;
    Float_t BiPonisher;
    Double_t delt;
    Double_t htime;
    Double_t promptCCubeEnergyOutsideCrown_calibrated;
    Double_t promptCCubeEnergyInsideCrown_calibrated;
    Int_t promptNCCube;
    Int_t topology;
    Double_t EStSpread;
    Double_t dotEM1_EM2;
    Double_t dot_topo6_EM1_EM2;
    Double_t distEM1_EM2;
    Double_t distAC_EM1;
    Int_t nCubesEM1;
    Double_t posEM1_x;
    Double_t posEM1_y;
    Double_t posEM1_z;
    Double_t eEM1_calibrated;
    Double_t distAC_EM2;
    Int_t nCubesEM2;
    Double_t eEM2_calibrated;
    Double_t AC_E_calibrated;
    Int_t pair;
    std::vector<int> *promptCCubeX;
    std::vector<int> *promptCCubeY;
    std::vector<int> *promptCCubeZ;
    std::vector<float> *promptCCubeE_calibrated;
    std::vector<int> *eEM1X;
    std::vector<int> *eEM1Y;
    std::vector<int> *eEM1Z;
    std::vector<double> *eEM1E_calibrated;
    std::vector<int> *eEM2X;
    std::vector<int> *eEM2Y;
    std::vector<int> *eEM2Z;
    std::vector<double> *eEM2E_calibrated;
    ULong64_t cycleNum;

    // List of branches
    TBranch *b_AC_x; //!
    TBranch *b_AC_y; //!
    TBranch *b_AC_z; //!
    TBranch *b_delt;   //!
    TBranch *b_htime;   //!
    TBranch *b_BiPonisher;   //!
    TBranch *b_promptCCubeEnergyOutsideCrown_calibrated;   //!
    TBranch *b_promptCCubeEnergyInsideCrown_calibrated;   //!
    TBranch *b_promptNCCube;   //!
    TBranch *b_topology;   //!
    TBranch *b_EStSpread;   //!
    TBranch *b_dotEM1_EM2;   //!
    TBranch *b_dot_topo6_EM1_EM2;   //!
    TBranch *b_distEM1_EM2;   //!
    TBranch *b_distAC_EM1;   //!
    TBranch *b_nCubesEM1;   //!
    TBranch *b_posEM1_x;   //!
    TBranch *b_posEM1_y;   //!
    TBranch *b_posEM1_z;   //!
    TBranch *b_eEM1_calibrated;   //!
    TBranch *b_distAC_EM2;   //!
    TBranch *b_nCubesEM2;   //!
    TBranch *b_eEM2_calibrated;   //!
    TBranch *b_AC_E_calibrated;   //!
    TBranch *b_pair;   //!
    TBranch *b_promptCCubeX;   //!
    TBranch *b_promptCCubeY;   //!
    TBranch *b_promptCCubeZ;   //!
    TBranch *b_promptCCubeE_calibrated;   //!
    TBranch *b_eEM1X;   //!
    TBranch *b_eEM1Y;   //!
    TBranch *b_eEM1Z;   //!
    TBranch *b_eEM1E_calibrated;   //!
    TBranch *b_eEM2X;   //!
    TBranch *b_eEM2Y;   //!
    TBranch *b_eEM2Z;   //!
    TBranch *b_eEM2E_calibrated;   //!
    TBranch *b_cycleNum;   //!

    nsEsClusCoins(const char *fileName);

    virtual ~nsEsClusCoins();

    virtual Int_t Cut(Long64_t entry);

    virtual Int_t GetEntry(Long64_t entry);

    virtual Long64_t LoadTree(Long64_t entry);

    virtual void Init(TTree *tree);

    virtual void Loop();

    virtual Bool_t Notify();

    virtual void Show(Long64_t entry = -1);
};

#endif //nsEsClusCoins_hh