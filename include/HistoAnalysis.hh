//
// Created by niko on 15.05.20.
//

#ifndef HistoAnalysis_hh
#define HistoAnalysis_hh

// System
#include <vector>

// ROOT
#include "RtypesCore.h"


void Plot2NormalizedHistos(
        const char *name1, const char *name2, const char* title, const char* units,
                           Int_t nBins, Double_t xMin, Double_t xMax,
                           std::vector<Double_t>& first, std::vector<Double_t>& second);

#endif //HistoAnalysis_hh
