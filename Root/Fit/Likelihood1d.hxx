#ifndef __Likelihood1d_hxx__
#define __Likelihood1d_hxx__
/*
  Likelihood1d.hxx
*/
#include <vector>
#include "Base/DoubleArrayT.hxx"
#include "Math/Functor.h"

#include "TF1.h"
#include "TH1.h"

class Likelihood1d : public ROOT::Math::Functor {
public:
  Likelihood1d();
  Likelihood1d(TF1* func, TH1* hist=nullptr);
  ~Likelihood1d();

  Double_t operator()(const Double_t* pars);

  void setFunction(TF1* f) { mFunction = f; }
  void setHistData(const TH1* h) { mHistData = h; }

  void addPoint(Double_t x);
  void addPoint(const DoubleArray1& point);
  
protected:
  TF1* mFunction;
  //
  const TH1* mHistData;
  std::vector<DoubleArray1> mPointData;
};

#endif // __Likelihood1d_hxx__

