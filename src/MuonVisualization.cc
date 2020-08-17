//
// Created by niko on 11.04.20.
//

// Local
#include "include/MuonVisualization.hh"
#include "include/MuonTools.hh"

// System


// ROOT
#include "TLine.h"
#include "TStyle.h"


MuonVisualization::MuonVisualization() :
        hist3D(nullptr),
        histProjZY(nullptr),
        histProjZX(nullptr),
        histProjYX(nullptr),
        canvDet(nullptr),
        canvProj(nullptr),
        trackLine3D( new TPolyLine3D() )
        
{
    canvDet = new TCanvas("canvDet","canvDet", 0, 0,400,2000);
    canvProj = new TCanvas("canvProj", "canvProj", 0, 0, 600, 600);
    
    hist3D = new TH3D("hist3D", "Granular SoLid detector",
                           16, 0, 16,
                           16, 0, 16,
                           50, 0, 50);
    hist3D->GetXaxis()->SetNdivisions(16);
    hist3D->GetYaxis()->SetNdivisions(16);
    hist3D->GetZaxis()->SetNdivisions(50);


    histProjZY = new TH2D("histProjZY", "ZY projection",
                           50, 0, 50,
                           16, 0, 16);
    histProjZY->GetXaxis()->SetNdivisions(50);
    histProjZY->GetYaxis()->SetNdivisions(16);
    histProjZY->SetXTitle("Z plane");
    histProjZY->SetYTitle("Y (cube)");
    
    histProjZX = new TH2D("histProjZX", "ZX projection",
                           50, 0, 50,
                           16, 0, 16);
    histProjZX->GetXaxis()->SetNdivisions(50);
    histProjZX->GetYaxis()->SetNdivisions(16);
    histProjZX->SetXTitle("Z plane");
    histProjZX->SetYTitle("X (cube)");
    
    histProjYX = new TH2D("histProjYX", "YX projection",
                           16, 0, 16,
                           16, 0, 16);
    histProjYX->GetXaxis()->SetNdivisions(16);
    histProjYX->GetYaxis()->SetNdivisions(16);
    histProjYX->SetXTitle("X (cube)");
    histProjYX->SetYTitle("Y (cube)");

    offset = 1;

    gStyle->SetOptStat(0);
}

void MuonVisualization::Visualize(const std::vector<Muon> &muons)
{
    Double_t content = 1;
    Color_t color = 632; // red color

    std::vector<TPolyLine3D> trackLines;
    for (auto muon : muons) {
        trackLines.push_back(TPolyLine3D());

        Int_t zStart = 50;
        Int_t zEnd = -50;

        trackLines.back().SetPoint(0, (muon.mx * zStart + muon.cx), (muon.my * zStart + muon.cy), zStart);
        trackLines.back().SetPoint(1, (muon.mx * zEnd + muon.cx), (muon.my * zEnd + muon.cy), zEnd);
        trackLines.back().SetLineColor(color);
        hist3D->SetBinContent(muon.cubeEnd.x + offset,
                              muon.cubeEnd.y + offset,
                              muon.cubeEnd.z + offset, content);

        hist3D->SetBinContent(muon.cubeStart.x + offset,
                              muon.cubeStart.y + offset,
                              muon.cubeStart.z + offset, content);

        content-= 0.05;
    }

    // Drawing
    gPad->SetGrid();
    hist3D->Draw("LEGO2");
    for (auto trackLine : trackLines) {
        trackLine.Draw();
    }
}

void MuonVisualization::Visualize(const Muon &muon, const Points& muonCylinder)
{
    Double_t content = 1.0;

    for (const auto& cube : muonCylinder) {
        hist3D->SetBinContent(
                cube.x + offset,
                cube.y + offset,
                cube.z + offset, content - 0.3);

        histProjZY->SetBinContent(cube.z + offset,
                                  cube.y + offset, content - 0.3);
        histProjZX->SetBinContent(cube.z + offset,
                                  cube.x + offset, content - 0.3);
        histProjYX->SetBinContent(cube.x + offset,
                                  cube.y + offset, content - 0.3);
    }

    hist3D->SetBinContent(muon.cubeEnd.x + offset,
                          muon.cubeEnd.y + offset,
                          muon.cubeEnd.z + offset, content);
    hist3D->SetBinContent(muon.cubeStart.x + offset,
                          muon.cubeStart.y + offset,
                          muon.cubeStart.z + offset, content);
    histProjZY->SetBinContent(muon.cubeStart.z + offset,
                              muon.cubeStart.y + offset, content);
    histProjZX->SetBinContent(muon.cubeStart.z + offset,
                              muon.cubeStart.x + offset, content);
    histProjYX->SetBinContent(muon.cubeStart.x + offset,
                              muon.cubeStart.y + offset, content);
    histProjZY->SetBinContent(muon.cubeEnd.z + offset,
                              muon.cubeEnd.y + offset, content);
    histProjZX->SetBinContent(muon.cubeEnd.z + offset,
                              muon.cubeEnd.x + offset, content);
    histProjYX->SetBinContent(muon.cubeEnd.x + offset,
                              muon.cubeEnd.y + offset, content);


    // Trajectory lines
    trackLine3D->SetPoint(0, muon.mx * -50 + muon.cx, muon.my * -50 + muon.cy, -50);
    trackLine3D->SetPoint(1, muon.mx * 50 + muon.cx, muon.my * 50 + muon.cy, 50);
    trackLine3D->SetLineColor(EColor::kRed);

    Double_t x1, y1, x2, y2;
    x1 = -muon.cx / muon.mx; x2 = (16.0 - muon.cx) / muon.mx; y1 = 0; y2 = 16;
    auto trackLineZX = new TLine(x1, y1, x2, y2);
    trackLineZX->SetLineWidth(2);
    trackLineZX->SetLineColor(kRed);
    x1 = -muon.cy / muon.my; x2 = (16.0 - muon.cy) / muon.my; y1 = 0; y2 = 16;
    auto trackLineZY = new TLine(x1, y1, x2, y2);
    trackLineZY->SetLineWidth(2);
    trackLineZY->SetLineColor(kRed);
    x1 = muon.cx + 0 * muon.mx; x2 = muon.cx + 50 * muon.mx; y1 = muon.cy + 0 * muon.my; y2 = muon.cy + 50 * muon.my;
    auto trackLineYX = new TLine(x1, y1, x2, y2);
    trackLineYX->SetLineWidth(2);
    trackLineYX->SetLineColor(kRed);

    // Drawing
    canvDet->cd();
    hist3D->Draw("LEGO2");
    trackLine3D->Draw();

    canvProj->cd();
    canvProj->Divide(1, 3);
    
    canvProj->cd(1);
    gPad->SetGrid();
    histProjZY->Draw("COL");
    trackLineZY->Draw();

    canvProj->cd(2);
    gPad->SetGrid();
    histProjZX->Draw("COL");
    trackLineZX->Draw();

    canvTmp = (TCanvas *) canvProj->cd(3);
    canvTmp->Divide(2, 1);
    canvTmp->cd(1);

    gPad->SetGrid();
    histProjYX->Draw("COL");
    trackLineYX->Draw();
}

MuonVisualization::~MuonVisualization() {
    std::cout << "MuonVisualization destructor" << std::endl;

    delete hist3D;
    delete histProjZY;
    delete histProjZX;
    delete histProjYX;
    delete canvDet;
    delete canvProj;
    delete trackLine3D;

    delete canvTmp;
}
