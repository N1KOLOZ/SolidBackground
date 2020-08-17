//
// Created by niko on 04.03.20.
//

#ifndef MuonToB8Analysis_hh
#define MuonToB8Analysis_hh

// ROOT
#include <RtypesCore.h>

// System
#include <memory>
#include <string>
#include <vector>
#include <map>

// Local
#include "include/MuonTools.hh"

void GetListOfFiles(std::vector<std::string>& listOfFiles, const std::string &dirPath, const std::string &ext);

void BuildCylinder(const Muon &muon, Points &muonCylinder);

void MakeMuonReco();
void ReadMuonReco(const std::string& fileName);

void SaveIndexes();
void MakeProcessedRoffTree();

void InvestigateTopo2();

void MergeTxt();
void Check();

void VisualizeTrack(Int_t entry);

#endif //MuonToB8Analysis_hh