/*
  FuncGaus.cxx
*/
#include <cmath>
#include "TMath.h"

#include "Func/FuncGaus.hxx"

Double_t funcGaus1(Double_t* x, Double_t* p) {
  Double_t N = p[0];
  Double_t muX = p[1];
  Double_t sigmaX = p[2];
  if (sigmaX == 0.0) {
    sigmaX = 1.0E-10;
  }
  Double_t twopi = TMath::TwoPi();
  Double_t z1 = (x[0] - muX)/sigmaX;
  Double_t y = N/(std::sqrt(twopi)*sigmaX)*std::exp(-(z1*z1)/2.0);
  return y;
}

Double_t funcGaus2(Double_t* x, Double_t* p) {
  Double_t y1 = funcGaus1(x, p);
  Double_t y2 = funcGaus1(x, p+3);
  return y1+y2;
}

