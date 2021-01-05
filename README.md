# CodeBox
A collection of source codes for various problems

## Rootマクロ
RootフォルダにはROOTの主な機能の使い方を示した簡単なマクロをいくつか置いてある。ROOTを起動するディレクトリをanalysisDir、CodeBoxパッケージの場所を相対パスでanalysisDir/../dev/CodeBoxのようにすると

'''
.x ../dev/CodeBox/Root/initCodeBox.C("../dev/CodeBox")
'''

を実行することでCodeBox/Root以下のマクロがMacroPath, DynamicPathに登録される。

### 使い方
空のディレクトリ（mydirとする)にインストールして使う場合、
'''
mkdir mydir
cd mydir
mkdir dev analysis
cd dev
git clone https://github.com/tkono17/CodeBox.git
cd ../analysis
root
'''

rootlogon.Cを作成して中身を以下のようにする。
'''
{
  gROOT->Macro("../dev/CodeBox/Root/initCodeBox.C");
  gROOT->Macro("../dev/CodeBox/Root/loadLibs.C");
}
'''


ROOTを起動後

'''
root[0] .x rootlogon.C
root[1] .x binnedFitGaus2d.C
'''
