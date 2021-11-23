/*
  calcCorrection.C
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TGraph.h"

double calcCorrection(double dtheta, 
		    const std::string& fname="gen1M.root") {
  TFile* fin = TFile::Open(fname.c_str(), "READ");
  TTree* t = dynamic_cast<TTree*>(fin->Get("t"));
  const double pi = 3.1415;

  char cut1[200];
  char cut2[200];
  std::sprintf(cut1, "fabs(theta)<%f", dtheta);
  std::sprintf(cut2, "hit");
  TH1* h1 = new TH1F("h1", "", 100, 0, pi);
  TH1* h2 = new TH1F("h2", "", 100, 0, pi);
  t->Draw("theta>>h1", cut1);
  t->Draw("theta>>h2", cut2);

  int n_true = h1->GetEntries();
  int n_sim = h2->GetEntries();
  double C = static_cast<double>(n_true)/n_sim;

  std::cout << "DeltaTheta=" << dtheta
	    << " N(true)=" << n_true 
	    << " N(sim)=" << n_sim 
	    << " Correction=" << C
	    << std::endl;
  return C;
}


void calcCorrection() {
  float x[50];
  float y[50];

  int n=50;

  for (int i=0; i<n; ++i) {
    double dtheta = 0.01*(i+1);
    x[i] = dtheta;
    y[i] = calcCorrection(dtheta);
  }

  TGraph* g = new TGraph(n, x, y);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.5);
  g->Draw("ap");
}
