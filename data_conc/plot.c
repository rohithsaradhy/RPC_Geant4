#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void plot()
{
	Int_t n=12, m=11;
	Double_t mean[n][m],c;
	TH1D *Hist[n][m];
	string hist_name,brn,temp, energy[12]={"50","100","250","400","500","600","750","1000","1250","1500","5000","10000"},file_name,pic_name;
	string conc[11]={"5", "10", "15", "20", "25", "30", "35", "40", "60", "80", "100"};

	ifstream  infile;

//collecting data
	for(int j=0;j<m;j++)
	{
		for(int i=0;i<n;i++)
		{
			file_name="CO_"+conc[j]+"_Energy_"+energy[i]+"MeV.txt";
			hist_name=conc[j]+energy[i]+"MeV";
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


	// Now we will plot the average energy lost!



TCanvas * canvas = new TCanvas("Mean Energy Deposited","Mean Energy Deposited",1600,768);
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
	row[i]=mean[i][3];

TGraph *gr2 = new TGraph(n,eng,row);
gr2->SetLineColor(kRed);
gr2->SetMarkerColor(9);
gr2->SetLineWidth(2);
mg->Add(gr2);


for(int i=0;i<n;i++)
	row[i]=mean[i][6];

TGraph *gr3 = new TGraph(n,eng,row);
gr3->SetLineColor(kBlue);
gr3->SetMarkerColor(kGreen);
gr3->SetLineWidth(2);
mg->Add(gr3);


for(int i=0;i<n;i++)
	row[i]=mean[i][8];

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
  leg->SetHeader("The Concentrations Are:");
	leg->AddEntry(gr1,"5%","lp");
	leg->AddEntry(gr2,"20%","lp");
	leg->AddEntry(gr3,"35%","lp");
	leg->AddEntry(gr4,"60%","lp");
	leg->Draw();
	//canvas->Update();
	canvas->SaveAs("Concentration.eps");

	//Mean Energy vs Concentration Graph now...

	TCanvas * canvas1 = new TCanvas("Mean Energy Deposited vs Conc","Mean Energy Deposited",1600,768);
	TMultiGraph* Mg = new TMultiGraph();
	TLegend* Len = new TLegend(0.8,0.8,0.5,0.5,"The Energies(MeV) are:","brNDC");
	TGraph* Gr[12];
	Double_t Conc[m];
	for(int i=0;i<m;i++)
		Conc[i] = atof(conc[i].c_str());

	for(int i=0;i<n;i+=1)
	{

			for(int j=0;j<m;j++)
				row[j]=mean[i][j];
			if(i==0)
				cout<<Conc[10]<<" "<<row[10]<<endl<<Conc[0]<<" "<<row[0]<<endl;
			Gr[i] = new TGraph(m,Conc,row);
			Gr[i]->SetLineColor(i+1);
			Gr[i]->SetMarkerColor(i+1);
			Gr[i]->SetLineWidth(2);
			Mg->Add(Gr[i]);
			Len->AddEntry(Gr[i],energy[i].c_str(),"lp");


	}
	Mg->Draw("AC*");
	Len->Draw();
	canvas1->SaveAs("Energies.eps");
}
