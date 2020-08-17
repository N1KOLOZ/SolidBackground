//
// Created by niko on 12.04.20.
//

#ifndef MuonRecoTreeWriter_hh
#define MuonRecoTreeWriter_hh

// Local
#include "MuonTools.hh"

// System
#include <vector>
#include <string>

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "RtypesCore.h"

class MuonRecoTreeWriter {
public:
    MuonRecoTreeWriter(const std::string& filePath);

    ~MuonRecoTreeWriter();

    void Write();

    void Fill(const Muon &muon, const Points &muonCylinder);

private:
    TFile *file;
    TTree *fChain;

// Declaration of leaf types
    std::vector<Int_t> xCube;
    std::vector<Int_t> yCube;
    std::vector<Int_t> zCube;
    std::vector<Int_t> startCube;
    std::vector<Int_t> endCube;

    Double_t mx;
    Double_t cx;
    Double_t my;
    Double_t cy;
    Double_t htime;

// Methods
    void Clear();
};

#endif //MuonRecoTreeWriter_hh