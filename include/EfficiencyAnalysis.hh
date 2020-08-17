//
// Created by niko on 26.02.20.
//

#ifndef EfficiencyAnalysis_hh
#define EfficiencyAnalysis_hh

#pragma once

void Start(std::string title, const std::string& units, char sign,
        Double_t threshold, Double_t range, std::vector<Double_t>& B8, std::vector<Double_t>& BiPo);

void EfficiencyAnalysis(const std::string& tag);

void FinalEfficiency(const std::string& tag);


#endif //Efficiency Analysis_hh
