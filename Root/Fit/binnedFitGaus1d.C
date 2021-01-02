/*
  binnedFitGaus1d.C
*/
#include "Func/FuncGaus.hxx"
#include "Fit/Likelihood1d.hxx"

#include "Math/Minimizer.h"
#include "Math/Functor.h"
#include "Math/Factory.h"


Double_t xmin = 0.0;
Double_t xmax = 100.0;

TF1* getFunction() {
  Double_t pars[3] = { 1.0, 50.0, 5.0 };
  TF1* func = new TF1("f_gaus1", funcGaus1, xmin, xmax, 3);
  func->SetParameters(pars);
  return func;
}

TH1* generateHist(TF1* func, unsigned int n) {
  TRandom3 random(20210102);
  float xmin = func->GetXmin();
  float xmax = func->GetXmax();

  TH1* h = new TH1F("h_data", "", 100, xmin, xmax);
  for (auto i=0; i<n; ++i) {
    auto x = func->GetRandom(xmin, xmax);
    h->Fill(x);
  }
  return h;
}

void binnedFitGaus1d() {
  TF1* modelFunc = getFunction();
  TH1* h = generateHist(modelFunc, 100);
  h->Draw();
  //  h->Fit(modelFunc, "L");

  Likelihood1d lh(modelFunc, h);

  std::string minName = "Minuit2";
  //  minName = "GSLMultiMin";
  std::string minAlgo = "";
  ROOT::Math::Minimizer* minimizer =
    ROOT::Math::Factory::CreateMinimizer(minName.c_str(), minAlgo.c_str());
  minimizer->SetMaxFunctionCalls(1000000);
  minimizer->SetMaxIterations(10000);
  minimizer->SetTolerance(1.0E-4);
  minimizer->SetPrintLevel(1);

  ROOT::Math::Functor lhFunc(lh, 2);
  double steps[3] = { 0.01, 0.01, 0.01};
  minimizer->SetFunction(lhFunc);
  minimizer->SetVariable(0, "N", 10.0, steps[0]);
  minimizer->SetVariable(1, "mu", 50.0, steps[1]);
  minimizer->SetVariable(2, "sigma", 5.0, steps[2]);
  minimizer->Minimize();

  const double* xs = minimizer->X();
  char s[100];
  std::sprintf(s, "L(%10.5f, %10.5f, %10.5f) => %10.5f",
	       xs[0], xs[1], xs[2], minimizer->MinValue());
  std::cout << s << std::endl;

  modelFunc->Draw("same");
  h->Fit(modelFunc);
}
