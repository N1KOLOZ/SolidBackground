//
// Created by niko on 24.02.20.
//

// Local
#include "include/nikoStyle.hh"

// ROOT
#include "TROOT.h"
#include "TStyle.h"
#include "TText.h"
#include "TLatex.h"
#include "TLegend.h"

void SetStyle() {

// define names for colours
    Int_t black = 1;
    Int_t red = 2;
    Int_t green = 3;
    Int_t blue = 4;
    Int_t yellow = 5;
    Int_t magenta = 6;
    Int_t cyan = 7;
    Int_t purple = 9;

// Use times new roman, precision 2
    Int_t nikoFont = 132;  // Old 62;
// Line thickness
    Double_t nikoWidth = 2.00; // Old 3.00;
// Text size
    Double_t nikoTSize = 0.035;

// use plain black on white colors
    gROOT->SetStyle("Plain");

    TStyle *nikoStyle = new TStyle("nikoStyle", "niko plots style");

//    nikoStyle->SetErrorX(0); //  don't suppress the error bar along X

    nikoStyle->SetFillColor(1);
    nikoStyle->SetFillStyle(1001);   // solid
    nikoStyle->SetFrameFillColor(0);
    nikoStyle->SetFrameBorderMode(0);
    nikoStyle->SetPadBorderMode(0);
    nikoStyle->SetPadColor(0);
    nikoStyle->SetCanvasBorderMode(0);
    nikoStyle->SetCanvasColor(0);
    nikoStyle->SetStatColor(0);
    nikoStyle->SetLegendBorderSize(0);

/*// If you want the usual gradient palette (blue -> red)
    nikoStyle->SetPalette(1);
// If you want colors that correspond to gray scale in black and white:
    int colors[8] = {0, 5, 7, 3, 6, 2, 4, 1};
    nikoStyle->SetPalette(8, colors);*/

// set the paper & margin sizes
    nikoStyle->SetPaperSize(20, 26);
    nikoStyle->SetPadTopMargin(0.05);
    nikoStyle->SetPadRightMargin(0.05); // increase for colz plots
    nikoStyle->SetPadBottomMargin(0.10);
    nikoStyle->SetPadLeftMargin(0.08);

// use large fonts
    nikoStyle->SetTextFont(nikoFont);
    nikoStyle->SetTextSize(nikoTSize);
    nikoStyle->SetLabelFont(nikoFont, "x");
    nikoStyle->SetLabelFont(nikoFont, "y");
    nikoStyle->SetLabelFont(nikoFont, "z");
    nikoStyle->SetLabelSize(0.8 * nikoTSize, "x");
    nikoStyle->SetLabelSize(0.8 * nikoTSize, "y");
    nikoStyle->SetLabelSize(0.8 * nikoTSize, "z");
    nikoStyle->SetTitleFont(nikoFont);
    nikoStyle->SetTitleFont(nikoFont, "x");
    nikoStyle->SetTitleFont(nikoFont, "y");
    nikoStyle->SetTitleFont(nikoFont, "z");
    nikoStyle->SetTitleSize(1.0 * nikoTSize, "x");
    nikoStyle->SetTitleSize(1.0 * nikoTSize, "y");
    nikoStyle->SetTitleSize(1.0 * nikoTSize, "z");

// use medium bold lines and thick markers
    nikoStyle->SetLineWidth(1.5 * nikoWidth);
    nikoStyle->SetFrameLineWidth(nikoWidth);
    nikoStyle->SetHistLineWidth(nikoWidth);
    nikoStyle->SetFuncWidth(nikoWidth);
    nikoStyle->SetGridWidth(2.0 * nikoWidth);
    nikoStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes
    nikoStyle->SetMarkerStyle(20);
    nikoStyle->SetMarkerSize(0.5);

// label offsets
    nikoStyle->SetLabelOffset(0.010, "X");
    nikoStyle->SetLabelOffset(0.010, "Y");


// by default, do not display histogram decorations:
    nikoStyle->SetTitleAlign(2);
    nikoStyle->SetOptStat(0);
//    nikoStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
    nikoStyle->SetStatFormat("6.3g"); // specified as c printf options
    nikoStyle->SetOptTitle(1);
    nikoStyle->SetOptFit(0);
//nikoStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters

//titles
    nikoStyle->SetTitleOffset(1.00, "X");
    nikoStyle->SetTitleOffset(1.00, "Y");
    nikoStyle->SetTitleOffset(1.2, "Z");
    nikoStyle->SetTitleFillColor(0);
    nikoStyle->SetTitleStyle(0);
    nikoStyle->SetTitleBorderSize(0);
    nikoStyle->SetTitleFont(nikoFont, "title");
    nikoStyle->SetTitleX(0.0);
    nikoStyle->SetTitleY(0.98);
    nikoStyle->SetTitleW(1.0);
    nikoStyle->SetTitleH(0.05);

// look of the statistics box:
    nikoStyle->SetStatBorderSize(0);
    nikoStyle->SetStatFont(nikoFont);
    nikoStyle->SetStatFontSize(0.05);
    nikoStyle->SetStatX(0.9);
    nikoStyle->SetStatY(0.9);
    nikoStyle->SetStatW(0.25);
    nikoStyle->SetStatH(0.15);

// put tick marks on top and RHS of plots
    nikoStyle->SetPadTickX(1);
    nikoStyle->SetPadTickY(1);

// histogram divisions: only 5 in x to avoid label overlaps
    nikoStyle->SetNdivisions(505, "x");
    nikoStyle->SetNdivisions(510, "y");

    gROOT->SetStyle("nikoStyle");
    gROOT->ForceStyle();


/*
  // add LHCb label
  lhcbName = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                           0.87 - gStyle->GetPadTopMargin(),
                           gStyle->GetPadLeftMargin() + 0.20,
                           0.95 - gStyle->GetPadTopMargin(),
                           "BRNDC");
  lhcbName->AddText("LHCb");
  lhcbName->SetFillColor(0);
  lhcbName->SetTextAlign(12);
  lhcbName->SetBorderSize(0);
*/
    TLegend *nikoLegend = new TLegend();
    nikoLegend->SetTextFont(nikoFont);
    nikoLegend->SetTextColor(1);
    nikoLegend->SetTextSize(2.0 * nikoTSize);
    nikoLegend->SetTextAlign(12);

    TText *nikoLabel = new TText();
    nikoLabel->SetTextFont(nikoFont);
    nikoLabel->SetTextColor(1);
    nikoLabel->SetTextSize(nikoTSize);
    nikoLabel->SetTextAlign(12);

    TLatex *nikoLatex = new TLatex();
    nikoLatex->SetTextFont(nikoFont);
    nikoLatex->SetTextColor(1);
    nikoLatex->SetTextSize(nikoTSize);
    nikoLatex->SetTextAlign(12);


}

void SetStyleSimple() {
    // define names for colours
    Int_t black = 1;
    Int_t red = 2;
    Int_t green = 3;
    Int_t blue = 4;
    Int_t yellow = 5;
    Int_t magenta = 6;
    Int_t cyan = 7;
    Int_t purple = 9;

    // Use times new roman, precision 2
    Int_t nikoFont = 132;  // Old 62;
    // Line thickness
    Double_t nikoWidth = 2.00; // Old 3.00;
    // Text size
    Double_t nikoTextSize = 0.035;

    gROOT->SetStyle("Plain");

    TStyle *nikoStyle = new TStyle("nikoStyle", "niko plots style");

    // use large fonts
    nikoStyle->SetTextFont(nikoFont);
    nikoStyle->SetTextSize(nikoTextSize);

    nikoStyle->SetLabelFont(nikoFont, "x");
    nikoStyle->SetLabelFont(nikoFont, "y");
    nikoStyle->SetLabelFont(nikoFont, "z");
    nikoStyle->SetLabelSize(0.8 * nikoTextSize, "x");
    nikoStyle->SetLabelSize(0.8 * nikoTextSize, "y");
    nikoStyle->SetLabelSize(0.8 * nikoTextSize, "z");

    nikoStyle->SetTitleFont(nikoFont);
    nikoStyle->SetTitleFont(nikoFont, "x");
    nikoStyle->SetTitleFont(nikoFont, "y");
    nikoStyle->SetTitleFont(nikoFont, "z");
    nikoStyle->SetTitleSize(1.0 * nikoTextSize, "x");
    nikoStyle->SetTitleSize(1.0 * nikoTextSize, "y");
    nikoStyle->SetTitleSize(1.0 * nikoTextSize, "z");

    // use medium bold lines and thick markers
    nikoStyle->SetLineWidth(1.5 * nikoWidth);
    nikoStyle->SetFrameLineWidth(nikoWidth);
    nikoStyle->SetHistLineWidth(nikoWidth);
    nikoStyle->SetFuncWidth(nikoWidth);
    nikoStyle->SetGridWidth(1.0 * nikoWidth);
//    nikoStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes
    nikoStyle->SetMarkerStyle(20);
    nikoStyle->SetMarkerSize(0.5);

    //titles
    nikoStyle->SetTitleOffset(1.00, "X");
    nikoStyle->SetTitleOffset(1.00, "Y");
    nikoStyle->SetTitleOffset(1.2, "Z");
    nikoStyle->SetTitleFillColor(0);
    nikoStyle->SetTitleStyle(0);
    nikoStyle->SetTitleBorderSize(0);
    nikoStyle->SetTitleFont(nikoFont, "title");
    nikoStyle->SetTitleX(0.0);
    nikoStyle->SetTitleY(0.98);
    nikoStyle->SetTitleW(1.0);
    nikoStyle->SetTitleH(0.05);

    // look of the statistics box:
    nikoStyle->SetOptStat(0);

//??????????????
//    // histogram divisions: only 5 in x to avoid label overlaps
//    nikoStyle->SetNdivisions(505, "x");
//    nikoStyle->SetNdivisions(510, "y");

    gROOT->SetStyle("nikoStyle");
    gROOT->ForceStyle();
}
