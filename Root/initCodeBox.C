
void initCodeBox(const std::string& CBDir="../dev/CodeBox") {
  std::vector<std::string> packs = { "Base", "Hist", "Func", "Fit" };
  char s[2000], s1[2000];

  std::sprintf(s, "%s", gROOT->GetMacroPath());
  for (auto x: packs) {
    std::strcpy(s1, s);
    std::sprintf(s, "%s/Root/%s:%s", CBDir.c_str(), x.c_str(), s1);
  }
  gROOT->SetMacroPath(s);

  std::sprintf(s, "%s", gSystem->GetDynamicPath());
  for (auto x: packs) {
    std::strcpy(s1, s);
    std::sprintf(s, "%s/Root/%s:%s", CBDir.c_str(), x.c_str(), s1);
  }
  gSystem->SetDynamicPath(s);

  std::sprintf(s, ".include %s/Root", CBDir.c_str());
  gROOT->ProcessLine(s);
  
  std::cout << "Initial settings for CodeBox (Macro|Dynamic|Include path) done" << std::endl;
  //std::cout << "MacroPath: " << gROOT->GetMacroPath() << std::endl;
  //std::cout << "DynamicPath: " << gSystem->GetDynamicPath() << std::endl;

}
