/*
  unbinnedFitGaus1d.C
*/
#include "Func/FuncGaus.hxx"
#include "Fit/Likelihood1d.hxx"
#include "Base/DoubleArrayT.hxx"

#include "Math/Minimizer.h"
#include "Math/Functor.h"
#include "Math/Factory.h"


Double_t xmin = 0.0;
Double_t xmax = 100.0;

TF1* getFunction() {
  Double_t pars[3] = { 1.0, 50.0, 5.0 };
  TF1* func = new TF1("f_gaus1", funcGaus1, xmin, xmax, 3);
  func->SetParameters(pars);
  func->SetNpx(10000);
  return func;
}

void generateData(TF1* func, unsigned int n, std::vector<DoubleArray1>& data) {
  TRandom3 random(20210102);
  float xmin = func->GetXmin();
  float xmax = func->GetXmax();

  data.clear();
  TH1* h = new TH1F("h_data", "", 100, xmin, xmax);
  for (auto i=0; i<n; ++i) {
    auto x = func->GetRandom(xmin, xmax);
    data.push_back(x);
  }
}

void unbinnedFitGaus1d() {
  TF1* modelFunc = getFunction();
  std::vector<DoubleArray1> data;
  generateData(modelFunc, 100, data);
  TH1* h = new TH1F("h", "", 100, modelFunc->GetXmin(), modelFunc->GetXmax());
  for (auto x: data) {
    h->Fill(x.value(0));
  }
  h->Draw();
  //  h->Fit(modelFunc, "L");

  Likelihood1d lh(modelFunc);
  lh.setPointData(data);

  char s[100];
  const double* xs = nullptr;
  std::string minName = "Minuit2";
  //  minName = "GSLMultiMin";
  std::string minAlgo = "";
  ROOT::Math::Minimizer* minimizer =
    ROOT::Math::Factory::CreateMinimizer(minName.c_str(), minAlgo.c_str());
  minimizer->SetMaxFunctionCalls(1000000);
  minimizer->SetMaxIterations(10000);
  minimizer->SetTolerance(1.0E-6);
  minimizer->SetPrintLevel(1);

  ROOT::Math::Functor lhFunc(lh, 2);
  double steps[3] = { 0.01, 0.01, 0.001};
  minimizer->SetFunction(lhFunc);
  minimizer->SetVariable(0, "N", 1.0, steps[0]);
  minimizer->SetVariable(1, "mu", 50.0, steps[1]);
  minimizer->SetVariable(2, "sigma", 5.0, steps[2]);
  minimizer->FixVariable(0);
  minimizer->Minimize();
  std::cout << "Minimize done" << std::endl;
  minimizer->PrintResults();
  
  xs = minimizer->X();
  std::sprintf(s, "L(%10.5f, %10.5f, %10.5f) => %10.5f",
	       xs[0], xs[1], xs[2], minimizer->MinValue());
  std::cout << s << std::endl;

  float xmin = modelFunc->GetXmin();
  float xmax = modelFunc->GetXmax();
  TF1* f2 = new TF1("f2", funcGaus1, xmin, xmax, 3);
  for (int i=0; i<3; ++i) {
    f2->SetParameter(i, xs[i]);
    std::cout << "par " << i << " " << xs[i] << std::endl;
  }
  f2->SetLineColor(kGreen);
  f2->SetNpx(10000);

  modelFunc->Draw("same");
  h->Fit(modelFunc);
  f2->Draw("same");
}

