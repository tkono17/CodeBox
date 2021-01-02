#ifndef __DoubleArrayT_hxx__
#define __DoubleArrayT_hxx__
/*
  DoubleArrayT.hxx
*/
#include "TROOT.h"

template<unsigned int N>
class DoubleArrayT {
public:
  DoubleArrayT() {}
  DoubleArrayT(const Double_t* values, unsigned int n) {
    if (n > mValues.size()) n = mValues.size();
    for (unsigned int  i=0; i<n; ++i) {
      mValues[i] = values[i];
    }
  }
  DoubleArrayT(Double_t x) {
    if (N == 1) {
      mValues[0] = x;
    }
  }
  DoubleArrayT(Double_t x, Double_t y) {
    if (N == 2) {
      mValues[0] = x;
      mValues[1] = y;
    }
  }
  DoubleArrayT(Double_t x1, Double_t x2, Double_t y) {
    if (N == 3) {
      mValues[0] = x1;
      mValues[1] = x2;
      mValues[2] = y;
    }
  }
  ~DoubleArrayT() {}

  const Double_t* values() const { return mValues; }
  Double_t value(unsigned int i) const { return mValues[i]; }

  void setValues(const Double_t* values, unsigned int n) {
    if (n > mValues.size()) n = mValues.size();
    for (unsigned int  i=0; i<n; ++i) {
      mValues[i] = values[i];
    }
  }
  
protected:
  Double_t mValues[N];
};

typedef DoubleArrayT<1> DoubleArray1;
typedef DoubleArrayT<2> DoubleArray2;
typedef DoubleArrayT<3> DoubleArray3;

#endif // __DoubleArrayT_hxx__
