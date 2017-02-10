#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void muon()
{	
int	 i=0;
double  c=0 ;
// number of all lines
string brn, energy[9]={"1","5","10","50","100","500","1000","5000","10000"},file_name,pic_name;
ifstream  infile;

TFile f("muon.root","recreate");
TTree *tree = new TTree("T","Data for muon at different energies");
TH1D * Hist[9];
for(int i=0;i<9;i++)
{

brn = "muon"+energy[i]+"MeV";
tree->Branch(brn.c_str(),&c,"c/D");
file_name="muon"+energy[i]+"MeV.txt";
Hist[i] = new TH1D(to_string(i).c_str(),file_name.c_str(),1000,-.2,40);
infile.open(file_name.c_str());
//				TCanvas *c1 = new TCanvas;
//TH1D * h1 = new TH1D("h1",energy[i].c_str(), 1000, -0.2,10);
while(!infile.eof())
    {
      infile >> c;
      Hist[i]->Fill(c);
      tree->Fill();
	
}
/*
h1 -> Draw();
pic_name=energy[i]+".png";
c1->SaveAs(pic_name.c_str());
*/
infile.close();
//delete h1;
//delete c1;
//break;

}
f.Write();

}
