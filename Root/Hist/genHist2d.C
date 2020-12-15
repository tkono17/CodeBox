/*
  genHist2d.C
*/

void genHist2d(const std::string& fname="hist2d.root") {
  TFile* fout = TFile::Open(fname.c_str(), "RECREATE");

  TH2* h2 = new TH2F("h2", "2D histogram", 50, 0, 200, 50, 0, 100);
  float pars1[3] = { 0.3, 100.0, 5.0};
  float pars2[3] = { 0.7, 100.0, 30.0};
  const int n = 1000;

  TRandom3 random(20201215);

  float rcut = pars1[0]/(pars1[0]+pars2[0]);

  for (int i=0; i<n; ++i) {
    float r = random.Uniform(0.0, 1.0);
    float x=0;
    float y=0;
    if (r < rcut) {
      x = random.Gaus(pars1[1], pars1[2]);
      y = random.Gaus(pars1[1], pars1[2]);
    } else {
      x = random.Gaus(pars2[1], pars2[2]);
      y = random.Gaus(pars2[1], pars2[2]);
    }
    h2->Fill(x, y);
  }
  h2->ProjectionX()->Draw();
}

