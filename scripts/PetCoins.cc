/*

#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"

#include "TSystemDirectory.h"
#include "TGraphErrors.h"


#include <string>
#include <algorithm>
#include <iostream>

std::vector<std::string> ListFiles(const char *dirname = "/home/katerina/CEA-LAL/PWO_sim/output", const char *ext = ".root") {

    std::vector<std::string> output;

    TSystemDirectory dir(dirname, dirname);

    TList *files = dir.GetListOfFiles();

    if (files) {

        TSystemFile *file;

        TString fileName;

        TIter it = files->begin();

        while (file = (TSystemFile *) *it) {
        	++it;

            fileName = file->GetName();

            if (!file->IsDirectory() && fileName.EndsWith(ext)) {

                std::string tmpFileName = fileName.Data();
                output.push_back(tmpFileName);

            }
        }

        delete file;
    }

    delete files;
    return output;
}

void PetCoins() {
	std::vector<std::string> files = ListFiles();
	std::sort(files.begin(), files.end());

	std::vector<Double_t> x;
	std::vector<Double_t> y1;
	std::vector<Double_t> y2;
	std::vector<Double_t> y3;

	std::vector<Double_t> y1_er;
	std::vector<Double_t> y2_er;
	std::vector<Double_t> y3_er;
	std::vector<Double_t > x_er(x.size(),0);

	std::vector<TTree* > trees;

	for (const std::string& file : files) {
		TFile* tFile = new TFile(file.c_str());
		
		trees.push_back( (TTree*) tFile->Get("Coincidences") );

		x.push_back( std::stoi( file.substr(9, 11) ) );
	}




*/
/*
	for (auto it = trees.begin(); it != trees.end(); ++it) {
		std::cout << it->GetName() << std::endl;
	}*//*


*/
/*	for (int i = 0; i < trees.size(); ++i) {
		std::cout << trees[i]->GetName() << std::endl;
	}*//*


	

	

	for (int i = 0; i < trees.size(); ++i) {
		Int_t num = 0;
		Int_t num1 = 0;
		Int_t num3 = 0;
		Int_t eventID1 = 0;
    	Int_t eventID2 = 0;
		Int_t compton1 = 0;
		Int_t compton2 = 0;
		trees[i]->SetBranchAddress("eventID1", &eventID1);
		trees[i]->SetBranchAddress("eventID2", &eventID2);
		trees[i]->SetBranchAddress("comptonPhantom2", &compton2);
		trees[i]->SetBranchAddress("comptonPhantom1", &compton1);

		Long_t nEn = trees[i]->GetEntries();

		for (long j =0; j<nEn; ++j) {
			trees[i]->GetEntry(j);

			if (eventID1 != eventID2) {
				num++; 
			} else {
				if (compton1 >0 || compton2 >0) {
					num3++;
				}
			}

			if (compton1 ==0 && compton2 ==0 && eventID1 == eventID2) {
				num1++;
			}

		}

	//	for (auto tree : trees) {
    //   	 delete trees.at(i);
    //}

		y1.push_back(num);
		y2.push_back(num1);
		y3.push_back(num3);




	}

	TGraphErrors *g1 = new TGraphErrors(x.size(), x.data(), y1.data(),x_er.data(), y1_er.data());
	TGraphErrors *g2 = new TGraphErrors(x.size(), x.data(), y1.data(), x_er.data(), y2_er.data());
	TGraphErrors *g3 = new TGraphErrors(x.size(), x.data(), y1.data(), x_er.data(), y3_er.data());
//	TGraph *g2 = new TGraph(x.size(), x.data(), y2.data());
//	TGraph *g3 = new TGraph(x.size(), x.data(), y3.data());

	

	g1->SetLineColor(1);
	g2->SetLineColor(2);
	g3->SetLineColor(3);
	

	g1->Draw("AC*");
	g2->Draw("same");
	g3->Draw("same");


}
	
*/
