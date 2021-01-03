# CodeBox
A collection of source codes for various problems

## Rootマクロ
RootフォルダにはROOTの主な機能の使い方を示した簡単なマクロをいくつか置いてある。ROOTを起動するディレクトリをanalysisDir、CodeBoxパッケージの場所を相対パスでanalysisDir/../dev/CodeBoxのようにすると

.x ../dev/CodeBox/Root/initCodeBox.C("../dev/CodeBox")

を実行することでCodeBox/Root以下のマクロがMacroPath, DynamicPathに登録される。


