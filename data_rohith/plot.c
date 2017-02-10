#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void plot()
{
	Int_t n=12,m=4;
	Double_t mean[n][4],c;
	TH1D *Hist[n][m];
	string hist_name,brn,temp, energy[12]={"50","100","250","400","500","600","750","1000","1250","1500","5000","10000"},file_name,pic_name;
	string particle[4]={"proton","muon","kaon","pion"};

	ifstream  infile;

//collecting data
	for(int j=0;j<m;j++)
	{
		for(int i=0;i<n;i++)
		{
			file_name=particle[j]+energy[i]+"MeV.txt";
			hist_name=particle[j]+energy[i]+"MeV";
			temp = hist_name+";Energy in MeV;Counts";
			Hist[i][j] = new TH1D(hist_name.c_str(),temp.c_str(),1000,0,.005);
			infile.open(file_name.c_str());
			while(!infile.eof())
      			{
			        infile >> c;
							// cout<<c<<endl;
			        Hist[i][j]->Fill(c);
							mean[i][j]=Hist[i][j]->GetMean();
     			}
			infile.close();

		}
	}


	TCanvas * can1 = new TCanvas("ProtonCanvas","Proton Energy",1000,1000);
	TCanvas * can2 = new TCanvas("MuonCanvas","Muon Energy",1000,1000);
	TCanvas * can3 = new TCanvas("KaonCanvas","Kaon Energy",1000,1000);
	TCanvas * can4 = new TCanvas("PionCanvas","Pion Energy",1000,1000);

	can1->Divide(4,3);
	for(int i=0;i<n;i++)
	{
  		can1->cd(i+1);
  		Hist[i][0]->Draw();
  	}
	can1->Update();
	can1->SaveAs("ProtonEnergies.eps");
	can1->Close();

	can2->Divide(4,3);

	for(int i=0;i<n;i++)
	{
  		can2->cd(i+1);
  		Hist[i][1]->Draw();
  	}
	can2->Update();
	can2->SaveAs("MuonEnergies.eps");
	can2->Close();

	can3->Divide(4,3);
	for(int i=0;i<n;i++)
	{
  		can3->cd(i+1);
  		Hist[i][2]->Draw();
  	}
	can3->Update();
	can3->SaveAs("KaonEnergies.eps");
	can3->Close();

	can4->Divide(4,3);
	for(int i=0;i<n;i++)
	{
  		can4->cd(i+1);
  		Hist[i][3]->Draw();
  	}
	can4->Update();
	can4->SaveAs("PionEnergies.eps");
	can4->Close();

	// Now we will plot the average energy lost!



TCanvas * canvas = new TCanvas("Mean Energy Deposited;IncidentEnergy(MeV);MeanEnergyDeposited(MeV)","Mean Energy Deposited",1600,768);
TMultiGraph* mg = new TMultiGraph();
Double_t row[n],eng[n];

for (int i=0;i<n;i++)
{
	eng[i]=atof(energy[i].c_str());
}

for(int i=0;i<n;i++)
	row[i]=mean[i][0];

TGraph *gr1 = new TGraph(n,eng,row);
gr1->SetLineColor(kBlack);
gr1->SetMarkerColor(kRed);
gr1->SetLineWidth(2);
mg->Add(gr1);


for(int i=0;i<n;i++)
	row[i]=mean[i][1];

TGraph *gr2 = new TGraph(n,eng,row);
gr2->SetLineColor(kRed);
gr2->SetMarkerColor(9);
gr2->SetLineWidth(2);
mg->Add(gr2);


for(int i=0;i<n;i++)
	row[i]=mean[i][2];

TGraph *gr3 = new TGraph(n,eng,row);
gr3->SetLineColor(kBlue);
gr3->SetMarkerColor(kGreen);
gr3->SetLineWidth(2);
mg->Add(gr3);


for(int i=0;i<n;i++)
	row[i]=mean[i][3];

TGraph *gr4 = new TGraph(n,eng,row);
gr4->SetLineColor(kGreen);
gr4->SetMarkerColor(kBlack);
gr4->SetLineWidth(2);
mg->Add(gr4);
mg->Draw("AC*");
mg->SetTitle("Mean Energy Deposited for RPC with Sensitive Volume 2mm thickness");
mg->GetXaxis()->SetTitle("Incident Energy(MeV)");
mg->GetYaxis()->SetTitle("Mean Energy Deposited(MeV)");



	TLegend *leg = new TLegend(0.8,0.8,0.5,0.5,"","brNDC");
  leg->SetHeader("The Particles Are:");
	leg->AddEntry(gr1,"Proton","lp");
	leg->AddEntry(gr2,"Muon","lp");
	leg->AddEntry(gr3,"Kaon","lp");
	leg->AddEntry(gr4,"Pion","lp");
	leg->Draw();
	//canvas->Update();
	canvas->SaveAs("Particles.eps");


}
