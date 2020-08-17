//
// Created by niko on 03.03.20.
//

#ifndef muons_hh
#define muons_hh

// ROOT
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// System
#include <vector>
#include <string>

class muons {
public :
    TTree *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    Int_t runNumber;
    Double_t htime;
    Bool_t singlePlane;
    Int_t type;
    Double_t polar;
    Double_t azimuth;
    Double_t mx;
    Double_t cx;
    Double_t my;
    Double_t cy;
    Double_t trackLength;
    Bool_t stopped;
    std::vector<int> *startCube;
    std::vector<int> *endCube;
//    std::vector<std::vector<double> > *fitVerPos;
//    std::vector<std::vector<double> > *fitHorPos;

    // List of branches
    TBranch *b_runNumber;   //!
    TBranch *b_htime;   //!
    TBranch *b_singlePlane;   //!
    TBranch *b_type;   //!
    TBranch *b_polar;   //!
    TBranch *b_azimuth;   //!
    TBranch *b_mx;   //!
    TBranch *b_cx;   //!
    TBranch *b_my;   //!
    TBranch *b_cy;   //!
    TBranch *b_trackLength;   //!
    TBranch *b_stopped;   //!
    TBranch *b_startCube;   //!
    TBranch *b_endCube;   //!
//    TBranch *b_fitVerPos;   //!
//    TBranch *b_fitHorPos;   //!

    muons(const std::string &fileName);

    virtual ~muons();

    virtual Int_t Cut(Long64_t entry);

    virtual Int_t GetEntry(Long64_t entry);

    virtual Long64_t LoadTree(Long64_t entry);

    virtual void Init(TTree *tree);

    virtual void Loop();

    virtual Bool_t Notify();

    virtual void Show(Long64_t entry = -1);
};

#endif //muons_hh