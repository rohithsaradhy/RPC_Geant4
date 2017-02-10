#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void plot()
{	
int	 i=0;
double  c=0;
// number of all lines

ifstream infile;
infile.open("proton_100MeV.txt");
TH1D *h1 = new TH1D("h1","proton @ 100 MeV;Energy Deposited(MeV);Count", 1000, -0.2,1);
while(!infile.eof())
    {
      infile >> c;
      h1->Fill(c);
	
}

h1 -> Draw();

}
