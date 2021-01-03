/*
  Likelihood1d.cxx
*/
#include "Fit/Likelihood1d.hxx"
#include "Base/DoubleArrayT.hxx"

Likelihood1d::Likelihood1d() {
  mFunction = nullptr;
  mUsePoisson = false;
  mHistData = nullptr;
}

Likelihood1d::Likelihood1d(TF1* func, TH1* hist) {
  mFunction = func;
  mUsePoisson = false;
  mHistData = hist;
}

Likelihood1d::~Likelihood1d() {
}

Double_t Likelihood1d::operator()(const Double_t* pars) {
  Double_t out = 0.0;
  Double_t fval=0.0;
  mFunction->SetParameters(pars);

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
	fval = mFunction->Eval(x);
	if (mUsePoisson) {
	  out += fval - y*std::log(fval);
	} else {
	  out += -y*std::log(fval);
	}
	ytot += std::fabs(y);
      }
    }
    //    out += std::fabs(ytot - pars[0]);
    //std::cout << "out = " << out << std::endl;
  } else {
    for (auto p: mPointData) {
      Double_t x = p.value(0);
      fval = mFunction->Eval(x);
      out += -1.0*std::log(fval);
    }
    //  std::cout << "out(points) = " << out << std::endl;
  }
  return out;
}

void Likelihood1d::addPoint(Double_t x) {
  mPointData.push_back(DoubleArray1(x));
}

void Likelihood1d::addPoint(const DoubleArray1& point) {
  mPointData.push_back(point);
}


