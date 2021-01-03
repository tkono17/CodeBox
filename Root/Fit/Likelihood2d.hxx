#ifndef __Likelihood2d_hxx__
#define __Likelihood2d_hxx__
/*
  Likelihood2d.hxx
*/
#include <vector>
#include "Base/DoubleArrayT.hxx"
#include "Math/Functor.h"

#include "TF2.h"
#include "TH2.h"

class Likelihood2d : public ROOT::Math::Functor {
public:
  Likelihood2d();
  Likelihood2d(TF2* func, TH2* hist=nullptr);
  ~Likelihood2d();

  Double_t operator()(const Double_t* pars);

  void setFunction(TF2* f) { mFunction = f; }
  void setUsePoisson(bool x) { mUsePoisson = x; }
  
  void setHistData(const TH2* h) { mHistData = h; }

  void setPointData(const std::vector<DoubleArray2>& data) {
    mPointData = data;
  }
  void addPoint(Double_t x, Double_t y);
  void addPoint(const DoubleArray2& point);
  
protected:
  TF2* mFunction;
  bool mUsePoisson;
  //
  const TH2* mHistData;
  std::vector<DoubleArray2> mPointData;
};

#endif // __Likelihood2d_hxx__

