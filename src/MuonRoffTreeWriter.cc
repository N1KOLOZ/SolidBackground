//
// Created by niko on 12.04.20.
//

// Local
#include "include/MuonRoffTreeWriter.hh"

MuonRoffTreeWriter::MuonRoffTreeWriter(const std::string &filePath) :
        file( new TFile(filePath.c_str(),"CREATE") ),
        fChain( new TTree("nsEsClusCoins","Processed Roff data") )
{
    Clear();
    fChain->Branch("cycleNum", &cycleNum);
    fChain->Branch("runNumber", &runNumber);
    fChain->Branch("htime", &htime);
    fChain->Branch("time", &time);
    fChain->Branch("delt", &delt);
    fChain->Branch("delr", &delr);
    fChain->Branch("BiPonisher", &BiPonisher);
    fChain->Branch("topology", &topology);
    fChain->Branch("EStSpread", &EStSpread);

    fChain->Branch("dotEM1_EM2", &dotEM1_EM2);
    fChain->Branch("distEM1_EM2", &distEM1_EM2);

    fChain->Branch("distAC_EM1", &distAC_EM1);
    fChain->Branch("nCubesEM1", &nCubesEM1);
    fChain->Branch("eEM1_calibrated", &eEM1_calibrated);

    fChain->Branch("distAC_EM2", &distAC_EM2);
    fChain->Branch("nCubesEM2", &nCubesEM2);
    fChain->Branch("eEM2_calibrated", &eEM2_calibrated);

    fChain->Branch("AC_E_calibrated", &AC_E_calibrated);
    fChain->Branch("ES1_calibrated", &ES1_calibrated);
    fChain->Branch("ES2_calibrated", &ES2_calibrated);
}

void MuonRoffTreeWriter::Fill(const Roff &roff) {
    Clear();

    cycleNum = roff.cycleNum;
    runNumber = roff.runNumber;
    htime = roff.htime;
    time = roff.time;
    delt = roff.delt;
    delr = roff.delr;
    BiPonisher = roff.BiPonisher;
    topology = roff.topology;
    EStSpread = roff.EStSpread;

    dotEM1_EM2 = roff.dotEM1_EM2;
    distEM1_EM2 = roff.distEM1_EM2;

    distAC_EM1 = roff.distAC_EM1;
    nCubesEM1 = roff.nCubesEM1;
    eEM1_calibrated = roff.eEM1_calibrated;

    distAC_EM2 = roff.distAC_EM2;
    nCubesEM2 = roff.nCubesEM2;
    eEM2_calibrated = roff.eEM2_calibrated;

    AC_E_calibrated = roff.AC_E_calibrated;
    ES1_calibrated = roff.ES1_calibrated;
    ES2_calibrated = roff.ES2_calibrated;

    fChain->Fill();
}

void MuonRoffTreeWriter::Clear() {
    cycleNum = 0;
    runNumber = 0;
    htime = 0;
    time = 0;
    delt = 0;
    delr = 0;
    BiPonisher = 0;
    topology = 0;
    EStSpread = 0;

    dotEM1_EM2 = 0;
    distEM1_EM2 = 0;

    distAC_EM1 = 0;
    nCubesEM1 = 0;
    eEM1_calibrated = 0;

    distAC_EM2 = 0;
    nCubesEM2 = 0;
    eEM2_calibrated = 0;

    AC_E_calibrated = 0;
    ES1_calibrated = 0;
    ES2_calibrated = 0;
}

void MuonRoffTreeWriter::Write() {
    file->Write("nsEsClusCoins",TObject::kOverwrite);
}

MuonRoffTreeWriter::~MuonRoffTreeWriter() {
    std::cout << "MuonRoffTreeWriter destructor" << std::endl;
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

