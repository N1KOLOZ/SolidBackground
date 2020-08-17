//
// Created by niko on 11.04.20.
//

#ifndef MuonVisualization_hh
#define MuonVisualization_hh

// Local
#include "include/MuonVisualization.hh"
#include "include/MuonTools.hh"

// ROOT
#include "TH3D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TPolyLine3D.h"

class MuonVisualization {
public:
    MuonVisualization();
    ~MuonVisualization();

    void Visualize(const std::vector<Muon>& muons);

    void Visualize(const Muon &muon, const Points &muonCylinder = Points() );
private:
    // Histos

    // Detector
    TH3D *hist3D;

    // Projections
    TH2D *histProjZY;
    TH2D *histProjZX;
    TH2D *histProjYX;

    // Canvases
    TCanvas *canvDet;
    TCanvas *canvProj;
    TCanvas *canvTmp;

    TPolyLine3D *trackLine3D;

    Int_t offset;
};

#endif //MuonVisualization_hh
