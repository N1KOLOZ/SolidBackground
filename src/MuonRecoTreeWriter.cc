//
// Created by niko on 12.04.20.
//

// Local
#include "include/MuonRecoTreeWriter.hh"

MuonRecoTreeWriter::MuonRecoTreeWriter(const std::string &filePath) :
        file( new TFile(filePath.c_str(),"CREATE") ),
        fChain( new TTree("MuonReco","Reconstructed muon track") )
{
    Clear();
    fChain->Branch("xCube", &xCube);
    fChain->Branch("yCube", &yCube);
    fChain->Branch("zCube", &zCube);
    fChain->Branch("startCube", &startCube);
    fChain->Branch("endCube", &endCube);
    fChain->Branch("mx", &mx,"mx/D");
    fChain->Branch("cx", &cx,"cx/D");
    fChain->Branch("my", &my,"my/D");
    fChain->Branch("cy", &cy,"cy/D");
    fChain->Branch("htime", &htime,"htime/D");
}

void MuonRecoTreeWriter::Fill(const Muon &muon, const Points &muonCylinder) {
    Clear();

    // Cylinder
    for (const auto& cube : muonCylinder) {
        xCube.push_back(cube.x);
        yCube.push_back(cube.y);
        zCube.push_back(cube.z);
    }

    // Standard muon variables
    startCube.push_back( muon.cubeStart.x );
    startCube.push_back( muon.cubeStart.y );
    startCube.push_back( muon.cubeStart.z );
    endCube.push_back( muon.cubeEnd.x );
    endCube.push_back( muon.cubeEnd.y );
    endCube.push_back( muon.cubeEnd.z );
    htime = muon.htime;
    mx = muon.mx;
    my = muon.my;
    cx = muon.cx;
    cy = muon.cy;

    fChain->Fill();
}

void MuonRecoTreeWriter::Clear() {
    startCube.clear();
    endCube.clear();
    xCube.clear();
    yCube.clear();
    zCube.clear();
    htime = 0;
    mx = 0;
    my = 0;
    cx = 0;
    cy = 0;
}

void MuonRecoTreeWriter::Write() {
    file->Write("MuonReco",TObject::kOverwrite);
}

MuonRecoTreeWriter::~MuonRecoTreeWriter() {
    std::cout << "MuonRecoTreeWriter destructor" << std::endl;
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

