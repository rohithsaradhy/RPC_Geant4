#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void proton()
{
// int	 i=0;
Int_t n = 9;
Double_t  c=0, mean[n];

TFile f("proton.root","recreate");
TTree *tree = new TTree("T","Data for muon at different energies");

TH1D *Hist[n];

// number of all lines
string hist_name,brn,temp, energy[9]={"1","5","10","50","100","500","1000","5000","10000"},file_name,pic_name;
ifstream  infile;

for(int i=0;i<n;i++)
{
  brn = "proton"+energy[i]+"MeV";
  tree->Branch(brn.c_str(),&c,"c/D");
  file_name="proton"+energy[i]+"MeV.txt";
  hist_name = energy[i]+"MeV";
  temp = file_name +";Energy in MeV;Counts";
  // cout<<hist_name.c_str()<<endl;
  Hist[i] = new TH1D(hist_name.c_str(),temp.c_str(),1000,-0.2,1);
  infile.open(file_name.c_str());
  // TH1D * h1 = new TH1D("h1",energy[i].c_str(), 1000, -0.2,10);
  while(!infile.eof())
      {
        infile >> c;
        Hist[i]->Fill(c);
        tree->Fill();
        mean[i]=Hist[i]->GetMean();
      }
  infile.close();
}
/*
h1 -> Draw();
pic_name=energy[i]+".png";
c1->SaveAs(pic_name.c_str());
*/
//delete h1;
//delete c1;
//break;

// }
TCanvas * can = new TCanvas("ProtonCanvas","Proton Energy",1000,1000);
//TGraph * grp[9];
can->Divide(3,3);
for(int i=0;i<n;i++)
  {
  can->cd(i+1);
  Hist[i]->Draw();
  }

can->Update();
can->SaveAs("Energies.png");

Double_t eng[n];
for (int i=0;i<n;i++)
{
	eng[i]=atof(energy[i].c_str());
}

TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
TGraph *gr = new TGraph(n,eng,mean);
gr->Draw("AC*");
c1->Update();
c1->Close();
f.WriteTObject(gr);
f.Write();

}
