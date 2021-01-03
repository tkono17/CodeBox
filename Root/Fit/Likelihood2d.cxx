/*
  Likelihood2d.cxx
*/
#include "Fit/Likelihood2d.hxx"
#include "Base/DoubleArrayT.hxx"

#include "TAxis.h"

Likelihood2d::Likelihood2d() {
  mFunction = nullptr;
  mUsePoisson = false;
  mHistData = nullptr;
}

Likelihood2d::Likelihood2d(TF2* func, TH2* hist) {
  mFunction = func;
  mUsePoisson = false;
  mHistData = hist;
}

Likelihood2d::~Likelihood2d() {
}

Double_t Likelihood2d::operator()(const Double_t* pars) {
  Double_t out = 0.0;
  Double_t fval=0.0;
  Double_t x[2];
  Double_t y = 0.0;
  mFunction->SetParameters(pars);

  if (mHistData != nullptr) {
    int nbinsX = mHistData->GetNbinsX();
    int nbinsY = mHistData->GetNbinsY();
    double ytot = 0.0;
    const TAxis* xaxis = mHistData->GetXaxis();
    const TAxis* yaxis = mHistData->GetYaxis();
    for (int i=1; i<=nbinsX; ++i) {
      for (int j=1; j<=nbinsX; ++j) {
	x[0] = xaxis->GetBinCenter(i);
	x[1] = yaxis->GetBinCenter(i);
	y = mHistData->GetBinContent(i, j);
	if (y != 0.0) {
	  fval = mFunction->Eval(x[0], x[1]);
	  if (mUsePoisson) {
	    out += fval - y*std::log(fval);
	  } else {
	    out += -y*std::log(fval);
	  }
	  ytot += std::fabs(y);
	}
      }
    }
    //    out += std::fabs(ytot - pars[0]);
    //std::cout << "out = " << out << std::endl;
  } else {
    for (auto p: mPointData) {
      x[0] = p.value(0);
      x[1] = p.value(1);
      fval = mFunction->Eval(x[0], x[1]);
      out += -1.0*std::log(fval);
    }
    //  std::cout << "out(points) = " << out << std::endl;
  }
  return out;
}

void Likelihood2d::addPoint(Double_t x, Double_t y) {
  mPointData.push_back(DoubleArray2(x, y));
}

void Likelihood2d::addPoint(const DoubleArray2& point) {
  mPointData.push_back(point);
}


