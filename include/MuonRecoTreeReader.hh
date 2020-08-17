//
// Created by niko on 13.04.20.
//

#ifndef MuonRecoTreeReader_hh
#define MuonRecoTreeReader_hh


// ROOT
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// System
#include <vector>

class MuonRecoTreeReader {
public :
    TTree *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

    // Declaration of leaf types
    std::vector<int> *xCube;
    std::vector<int> *yCube;
    std::vector<int> *zCube;
    std::vector<int> *startCube;
    std::vector<int> *endCube;
    Double_t mx;
    Double_t cx;
    Double_t my;
    Double_t cy;
    Double_t htime;

    // List of branches
    TBranch *b_xCube;   //!
    TBranch *b_yCube;   //!
    TBranch *b_zCube;   //!
    TBranch *b_startCube;   //!
    TBranch *b_endCube;   //!
    TBranch *b_mx;   //!
    TBranch *b_cx;   //!
    TBranch *b_my;   //!
    TBranch *b_cy;   //!
    TBranch *b_htime;   //!

    MuonRecoTreeReader(const std::string &filePath);

    virtual ~MuonRecoTreeReader();

    virtual Int_t Cut(Long64_t entry);

    virtual Int_t GetEntry(Long64_t entry);

    virtual Long64_t LoadTree(Long64_t entry);

    virtual void Init(TTree *tree);

    virtual Bool_t Notify();

    virtual void Show(Long64_t entry = -1);
};

#endif // MuonRecoTreeReader_hh
