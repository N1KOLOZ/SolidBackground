//
// Created by niko on 20.03.20.
//

#ifndef nsEsClusCoinsRoff_hh
#define nsEsClusCoinsRoff_hh

// ROOT
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TDatime.h"

// System
#include <vector>

class nsEsClusCoinsRoff {
public :
    TTree *fChain;
    Int_t fCurrent;

    // Declaration of leaf types
    ULong64_t cycleNum;
    Int_t runNumber;
    TDatime *tRunStart;
    Double_t htime;
    ULong64_t time;
    Double_t delt;
    Double_t delx;
    Double_t dely;
    Double_t delz;
    Double_t delr;
    Double_t delx_ave;
    Double_t dely_ave;
    Double_t delz_ave;
    Double_t delr_ave;
    Double_t tNearestMuonType0;
    Double_t tNearestMuonType1;
    Double_t tNearestMuonType2;
    Double_t tNearestNS;
    Double_t xP;
    Double_t yP;
    Double_t zP;
    Double_t xP_ave;
    Double_t yP_ave;
    Double_t zP_ave;
    Double_t promptVolume;
    Double_t promptEnergy;
    Float_t energyDense;
    Double_t promptEnergy_calibrated;
    Double_t promptSCubeEnergyMostEnergetic;
    Double_t promptCCubeEnergy_calibrated;
    Double_t promptCCubeEnergyMostEnergetic_calibrated;
    Double_t promptCCubeEnergyCrown_calibrated;
    Double_t promptCCubeEnergyOutsideCrown_calibrated;
    std::vector<int> *promptChannels;
    std::vector<int> *promptChanX;
    std::vector<int> *promptChanY;
    std::vector<int> *promptChanZ;
    std::vector<float> *promptChanAmp;
    std::vector<float> *promptChanTime;
    std::vector<float> *promptChanTimeReco;
    Int_t promptNCCube;
    std::vector<int> *promptCCubeX;
    std::vector<int> *promptCCubeY;
    std::vector<int> *promptCCubeZ;
    std::vector<float> *promptCCubeE;
    std::vector<float> *promptCCubeE_calibrated;
    std::vector <std::vector<double>> *promptCCubeAmp;
    std::vector <std::vector<double>> *promptCCubeTimeReco;
    Double_t xD;
    Double_t yD;
    Double_t zD;
    Float_t BiPonisher;
    std::vector<float> *ampD;
    std::vector<float> *intD;
    Int_t NSClusTreePos;
    Int_t NSIDTreePos;
    Int_t ESClusTreePos;
    Int_t ESIDTreePos;
    Bool_t inIBDbuffer;
    Int_t topology;
    Double_t eCubeAroundAC;
    Double_t eCubeAroundAC_calibrated;
    Int_t nCubeAroundAC;
    Double_t EStSpread;
    Double_t dotEM1_EM2;
    Double_t distEM1_EM2;
    Double_t distAC_EM1;
    Int_t nCubesEM1;
    Double_t posEM1_x;
    Double_t posEM1_y;
    Double_t posEM1_z;
    Double_t eEM1;
    Double_t eEM1_calibrated;
    Double_t distAC_EM2;
    Int_t nCubesEM2;
    Double_t posEM2_x;
    Double_t posEM2_y;
    Double_t posEM2_z;
    Double_t eEM2;
    Double_t eEM2_calibrated;
    Double_t AC_x;
    Double_t AC_y;
    Double_t AC_z;
    Double_t AC_E;
    Double_t AC_E_calibrated;
    Double_t S_dotEM1_EM2;
    Double_t S_eESnoPositron;
    Double_t S_eC1;
    Double_t S_eC2;
    Double_t S_ncubeC1;
    Double_t S_ncubeC2;
    Double_t S_dotC1_C2;
    Double_t S_distC1_AC;
    Double_t S_distC2_AC;
    Double_t CuPID_delw;
    Double_t dot_ES1_ES2;
    Double_t dot_ES1_NS;
    Double_t dot_ESNS_NS;
    Double_t ES1;
    Double_t ES2;
    Double_t ESNS;
    Double_t ES1_calibrated;
    Double_t ES2_calibrated;
    Double_t ESNS_calibrated;

    // List of branches
    TBranch *b_cycleNum;   //!
    TBranch *b_runNumber;   //!
    TBranch *b_tRunStart;   //!
    TBranch *b_htime;   //!
    TBranch *b_time;   //!
    TBranch *b_delt;   //!
    TBranch *b_delx;   //!
    TBranch *b_dely;   //!
    TBranch *b_delz;   //!
    TBranch *b_delr;   //!
    TBranch *b_delx_ave;   //!
    TBranch *b_dely_ave;   //!
    TBranch *b_delz_ave;   //!
    TBranch *b_delr_ave;   //!
    TBranch *b_tNearestMuonType0;   //!
    TBranch *b_tNearestMuonType1;   //!
    TBranch *b_tNearestMuonType2;   //!
    TBranch *b_tNearestNS;   //!
    TBranch *b_xP;   //!
    TBranch *b_yP;   //!
    TBranch *b_zP;   //!
    TBranch *b_xP_ave;   //!
    TBranch *b_yP_ave;   //!
    TBranch *b_zP_ave;   //!
    TBranch *b_promptVolume;   //!
    TBranch *b_promptEnergy;   //!
    TBranch *b_energyDense;   //!
    TBranch *b_promptEnergy_calibrated;   //!
    TBranch *b_promptSCubeEnergyMostEnergetic;   //!
    TBranch *b_promptCCubeEnergy_calibrated;   //!
    TBranch *b_promptCCubeEnergyMostEnergetic_calibrated;   //!
    TBranch *b_promptCCubeEnergyCrown_calibrated;   //!
    TBranch *b_promptCCubeEnergyOutsideCrown_calibrated;   //!
    TBranch *b_promptChannels;   //!
    TBranch *b_promptChanX;   //!
    TBranch *b_promptChanY;   //!
    TBranch *b_promptChanZ;   //!
    TBranch *b_promptChanAmp;   //!
    TBranch *b_promptChanTime;   //!
    TBranch *b_promptChanTimeReco;   //!
    TBranch *b_promptNCCube;   //!
    TBranch *b_promptCCubeX;   //!
    TBranch *b_promptCCubeY;   //!
    TBranch *b_promptCCubeZ;   //!
    TBranch *b_promptCCubeE;   //!
    TBranch *b_promptCCubeE_calibrated;   //!
    TBranch *b_promptCCubeAmp;   //!
    TBranch *b_promptCCubeTimeReco;   //!
    TBranch *b_xD;   //!
    TBranch *b_yD;   //!
    TBranch *b_zD;   //!
    TBranch *b_BiPonisher;   //!
    TBranch *b_ampD;   //!
    TBranch *b_intD;   //!
    TBranch *b_NSClusTreePos;   //!
    TBranch *b_NSIDTreePos;   //!
    TBranch *b_ESClusTreePos;   //!
    TBranch *b_ESIDTreePos;   //!
    TBranch *b_inIBDbuffer;   //!
    TBranch *b_topology;   //!
    TBranch *b_eCubeAroundAC;   //!
    TBranch *b_eCubeAroundAC_calibrated;   //!
    TBranch *b_nCubeAroundAC;   //!
    TBranch *b_EStSpread;   //!
    TBranch *b_dotEM1_EM2;   //!
    TBranch *b_distEM1_EM2;   //!
    TBranch *b_distAC_EM1;   //!
    TBranch *b_nCubesEM1;   //!
    TBranch *b_posEM1_x;   //!
    TBranch *b_posEM1_y;   //!
    TBranch *b_posEM1_z;   //!
    TBranch *b_eEM1;   //!
    TBranch *b_eEM1_calibrated;   //!
    TBranch *b_distAC_EM2;   //!
    TBranch *b_nCubesEM2;   //!
    TBranch *b_posEM2_x;   //!
    TBranch *b_posEM2_y;   //!
    TBranch *b_posEM2_z;   //!
    TBranch *b_eEM2;   //!
    TBranch *b_eEM2_calibrated;   //!
    TBranch *b_AC_x;   //!
    TBranch *b_AC_y;   //!
    TBranch *b_AC_z;   //!
    TBranch *b_AC_E;   //!
    TBranch *b_AC_E_calibrated;   //!
    TBranch *b_S_dotEM1_EM2;   //!
    TBranch *b_S_eESnoPositron;   //!
    TBranch *b_S_eC1;   //!
    TBranch *b_S_eC2;   //!
    TBranch *b_S_ncubeC1;   //!
    TBranch *b_S_ncubeC2;   //!
    TBranch *b_S_dotC1_C2;   //!
    TBranch *b_S_distC1_AC;   //!
    TBranch *b_S_distC2_AC;   //!
    TBranch *b_CuPID_delw;   //!
    TBranch *b_dot_ES1_ES2;   //!
    TBranch *b_dot_ES1_NS;   //!
    TBranch *b_dot_ESNS_NS;   //!
    TBranch *b_ES1;   //!
    TBranch *b_ES2;   //!
    TBranch *b_ESNS;   //!
    TBranch *b_ES1_calibrated;   //!
    TBranch *b_ES2_calibrated;   //!
    TBranch *b_ESNS_calibrated;   //!

    nsEsClusCoinsRoff(const std::string &fileName);

    virtual ~nsEsClusCoinsRoff();

    virtual Int_t Cut(Long64_t entry);

    virtual Int_t GetEntry(Long64_t entry);

    virtual Long64_t LoadTree(Long64_t entry);

    virtual void Init(TTree *tree);

    virtual void Loop();

    virtual Bool_t Notify();

    virtual void Show(Long64_t entry = -1);
};

#endif // nsEsClusCoinsRoff_hh
