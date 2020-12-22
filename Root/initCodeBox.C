{
  std::string p = gROOT->GetMacroPath();
  p = "../dev/CodeBox/Root/Func:" + p;
  p = "../dev/CodeBox/Root/Hist:" + p;
  gROOT->SetMacroPath(p.c_str());
  //  std::cout << "MacroPath: " << gROOT->GetMacroPath() << std::endl;

  p = gSystem->GetDynamicPath();
  p = "../dev/CodeBox/Root/Func:" + p;
  p = "../dev/CodeBox/Root/Hist:" + p;
  gSystem->SetDynamicPath(p.c_str());
  //  std::cout << "DynamicPath: " << gSystem->GetDynamicPath() << std::endl;

  gROOT->ProcessLine(".include ../dev/CodeBox/Root");
}
