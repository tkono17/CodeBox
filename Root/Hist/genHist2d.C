/*
  genHist2d.C
*/
#include <string>
#include <iostream>
#include "TFile.h"
#include "TH2.h"
#include "TF2.h"
#include "TRandom3.h"
#include "Func/FuncGaus2d.hxx"

void genHist2d(const std::string& fname="hist2d.root") {
  TFile* fout = TFile::Open(fname.c_str(), "RECREATE");

  TH2* h2 = new TH2F("h2", "2D histogram", 100, -200, 200, 100, -200, 200);
  Double_t pars1[10] = { 1.0, 0.0, 5.0, 0.0, 5.0, 
			 1.0, 0.0, 20.0, 0.0, 20.0 };
  const int n = 1000;

  TF2* func2 = new TF2("func2", funcGaus2d_2, -200, 200, -200, 200, 10);
  func2->SetParameters(pars1);

  TRandom3 random(20201222);
  Double_t x, y;

  for (int i=0; i<n; ++i) {
    func2->GetRandom2(x, y);
    h2->Fill(x, y);
  }
  h2->ProjectionX()->Draw();
}

