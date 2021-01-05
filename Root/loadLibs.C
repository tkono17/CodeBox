void loadLibs() {
  std::vector<std::string> macroLibs =
    {
      "FuncGaus.cxx+",
      "FuncGaus2d.cxx+",
      "Likelihood1d.cxx+",
      "Likelihood2d.cxx+"
    };
  for (auto x: macroLibs) {
    gROOT->LoadMacro(x.c_str());
  }
}
