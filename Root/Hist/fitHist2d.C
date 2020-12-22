/*
  fitHist2d.C
*/
#include "TMath.h"

void fitHist2d(const std::string& fname, const std::string& hname) {
  TFile* fin = TFile::Open(fname.c_str(), "READ");
  if (!fin->IsOpen()) {
    std::cout << "Cannot open file: " << fname << std::endl;
    return;
  }
  TH2* h2 = dynamic_cast<TH2*>(fin->Get(hname.c_str()) );



}
