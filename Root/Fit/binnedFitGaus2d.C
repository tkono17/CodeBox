/*
  binnedFitGaus2d.C
*/
#include "Func/FuncGaus2d.hxx"

TF2* getFunction() {
  Double_t xmin=0.0;
  Double_t xmax=100.0;
  Double_t ymin=0.0;
  Double_t ymax=100.0;
  Double_t pars[10] = { 1.0, 50.0, 5.0, 50.0, 5.0, 0.7, 50.0, 20.0, 50.0, 20.0};
  TF2* func = new TF2("f_gaus2", funcGaus2dx2, xmin, xmax, ymin, ymax, 10);
  func->SetParameters(pars);
  func->SetNpx(100);
  func->SetNpy(100);
  std::cout << "func: " << func << std::endl;
  return func;
}

TH2* generateHist(TF2* func, unsigned int n) {
  TRandom3 random(20210102);
  gRandom = &random;
  float xmin = func->GetXmin();
  float xmax = func->GetXmax();
  float ymin = func->GetYmin();
  float ymax = func->GetYmax();

  TH2* h = new TH2F("h_data", "", 100, xmin, xmax, 100, ymin, ymax);
  for (auto i=0; i<n; ++i) {
    Double_t x=0.0, y=0.0;
    func->GetRandom2(x, y);
    h->Fill(x, y);
  }
  return h;
}

void binnedFitGaus2d() {
  TF2* modelFunc = getFunction();
  TH2* h = generateHist(modelFunc, 100);
  h->Draw();
  h->Fit(modelFunc, "L");
  //
  h->SetMarkerStyle(20);
  h->SetMarkerSize(0.5);
  h->SetMarkerColor(kBlack);
  modelFunc->Draw("colz");
  h->Draw("hist same");
}

