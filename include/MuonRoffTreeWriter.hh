//
// Created by niko on 12.04.20.
//

#ifndef muonCylinder_hh
#define muonCylinder_hh

// Local
#include "MuonTools.hh"

// System
#include <vector>
#include <string>

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "RtypesCore.h"

struct Roff {
    ULong64_t cycleNum;
    Int_t runNumber;
    Double_t htime;
    ULong64_t time;
    Double_t delt;
    Double_t delr;
    Float_t BiPonisher;
    Int_t topology;
    Double_t EStSpread;

    Double_t dotEM1_EM2;
    Double_t distEM1_EM2;

    Double_t distAC_EM1;
    Int_t nCubesEM1;
    Double_t eEM1_calibrated;

    Double_t distAC_EM2;
    Int_t nCubesEM2;
    Double_t eEM2_calibrated;

    Double_t AC_E_calibrated;
    Double_t ES1_calibrated;
    Double_t ES2_calibrated;
};

class MuonRoffTreeWriter {
public:
    MuonRoffTreeWriter(const std::string& filePath);

    ~MuonRoffTreeWriter();

    void Write();

    void Fill(const Roff &roff);
private:
    TFile *file;
    TTree *fChain;

// Declaration of leaf types
    ULong64_t cycleNum;
    Int_t runNumber;
    Double_t htime;
    ULong64_t time;
    Double_t delt;
    Double_t delr;
    Float_t BiPonisher;
    Int_t topology;
    Double_t EStSpread;

    Double_t dotEM1_EM2;
    Double_t distEM1_EM2;

    Double_t distAC_EM1;
    Int_t nCubesEM1;
    Double_t eEM1_calibrated;

    Double_t distAC_EM2;
    Int_t nCubesEM2;
    Double_t eEM2_calibrated;

    Double_t AC_E_calibrated;
    Double_t ES1_calibrated;
    Double_t ES2_calibrated;

// Methods
    void Clear();
};

#endif //muonCylinder_hh