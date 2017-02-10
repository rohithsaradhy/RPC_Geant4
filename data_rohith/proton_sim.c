#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "EnergyLoss.h"

using namespace std;


void proton_sim()
{
// int	 i=0;
Int_t n = 12;
Double_t  c=0, mean[n];
double p[10]={8.96,1,29,63.54,1,322,0,0,938.28,0};

TFile f("proton.root","recreate");
TTree *tree = new TTree("T","Data for muon at different energies");

TH1D *Hist[n];

// number of all lines
string hist_name,brn,temp, energy[12]={"50","100","250","400","500","600","750","1000","1250","1500","5000","10000"},file_name,pic_name;
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
can->Divide(4,3);
for(int i=0;i<n;i++)
  {
  can->cd(i+1);
  Hist[i]->Draw();
  }

can->Update();
can->SaveAs("Energies.png");
can->Close();

Double_t eng[n],z[n];
for (int i=0;i<n;i++)
{
	eng[i]=atof(energy[i].c_str());
  p[4] = (pow((pow((eng[i]/(p[8])+1),2)-1),0.5)/((eng[i]/p[8])+1));
  z[i]=EnergyLossArCO2(p,30)*5;
	//cout<<eng[i]<<" "<<mean[i]<<endl
  cout<<eng[i]<<" "<<mean[i]<<" "<<z[i]<<endl;
}

for(int i=0;i<n;i++)
{
  if (mean[i]==0)
  {
    for(int j=i;j<n;j++)
    {
      mean[j] = mean[j+1];
      eng[j]=eng[j+1];
      z[j]=z[j+1];
    }
    n=n-1;
    i=i-1;
  }
  cout<<eng[i]<<" "<<mean[i]<<" "<<z[i]<<endl;
}
cout<<n<<endl;

TMultiGraph *mg = new TMultiGraph();
//TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

TGraph *gr = new TGraph(n,eng,mean);
gr->SetLineColor(kBlack);
gr->SetLineWidth(2);
mg->Add(gr);
TGraph *gr2 = new TGraph(n,eng,z);
gr2->SetLineColor(kBlue);
gr2->SetMarkerColor(kBlue);
gr2->SetLineWidth(2);
// mg->Add(gr2);



cout<<"********************"<<endl;
//starting the theory curve...
n=1000;
Double_t Emin=10,Emax=10000,x[10000],y[10000],b;

for(int i=0;i<n;i++)
  {

    	x[i]=Emin + (Emax-Emin)*i/n;
    	p[4] = (pow((pow((x[i]/(p[8])+1),2)-1),0.5)/((x[i]/p[8])+1));

	y[i]=EnergyLossArCO2(p,30)*5; //the times five is becuase of the thickness of the detector is 2mm.

 // cout<<x[i]<<" "<<y[i]<<endl;


  }

   TGraph *gr1 = new TGraph(n,x,y);
   gr1->SetLineColor(kRed);
   gr1->SetMarkerColor(kRed);
   gr1->SetLineWidth(2);
   //mg->Add(gr1);
   mg->Draw("AL*");
   //c1->Draw();
   //c1->Update();

f.WriteTObject(gr);
f.Write();

}
