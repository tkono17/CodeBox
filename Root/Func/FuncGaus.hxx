#ifndef __FuncGaus2d_hxx__
#define __FuncGaus2d_hxx__
/*
  FuncGaus.hxx
*/

Double_t funcGaus1(Double_t* x, Double_t* p) {
  Double_t N = p[0];
  Double_t muX = p[1];
  Double_t sigmaX = p[2];
  Double_t muY = p[3];
  Double_t sigmaY = p[4];
  if (sigmaX == 0.0) {
    sigmaX = 1.0E-10;
  }
  if (sigmaY == 0.0) {
    sigmaY = 1.0E-10;
  }
  Double_t twopi = TMath::TwoPi();
  Double_t z1 = (x[0] - muX)/sigmaX;
  Double_t z2 = (x[1] - muY)/sigmaY;
  Double_t y = N/(twopi*sigmaX*sigmaY)*std::exp(-(z1*z1 + z2*z2)/2.0);
  return y;
}

Double_t funcGaus2(Double_t* x, Double_t* p) {
  Double_t y1 = funcGaus1(x, p);
  Double_t y2 = funcGaus1(x, p+5);
}

#endif // __FuncGaus2d_hxx__
