/*
  Likelihood1d.cxx
*/
#include "Fit/Likelihood1d.hxx"
#include "Base/DoubleArrayT.hxx"

Likelihood1d::Likelihood1d() {
  mFunction = nullptr;
  mHistData = nullptr;
}

Likelihood1d::Likelihood1d(TF1* func, TH1* hist) {
  mFunction = func;
  mHistData = hist;
}

Likelihood1d::~Likelihood1d() {
}

Double_t Likelihood1d::operator()(const Double_t* pars) {
  Double_t out = 0.0;
  mFunction->SetParameter(0, 1.0);
  for (int i=0; i<2; ++i) {
    mFunction->SetParameter(i+1, pars[i]);
  }
  if (mHistData != nullptr) {
    int nbins = mHistData->GetNbinsX();
    double ytot = 0.0;
    for (int i=1; i<=nbins; ++i) {
      Double_t x = mHistData->GetBinCenter(i);
      Double_t y = mHistData->GetBinContent(i);
      if (y != 0.0) {
	// std::cout << "evalutate function at x=" << x << " => "
	// 	  << mFunction->Eval(x) << ", y=" << y
	// 	  << std::endl;
	out += -y*std::log(mFunction->Eval(x));
	ytot += std::fabs(y);
      }
    }
    //    out += std::fabs(ytot - pars[0]);
    //    std::cout << "out = " << out << std::endl;
  } else {
    for (auto p: mPointData) {
      Double_t x = p.value(0);
      out += -1.0*std::log(mFunction->Eval(x));
    }
  }
  return out;
}

void Likelihood1d::addPoint(Double_t x) {
  mPointData.push_back(DoubleArray1(x));
}

void Likelihood1d::addPoint(const DoubleArray1& point) {
  mPointData.push_back(point);
}


