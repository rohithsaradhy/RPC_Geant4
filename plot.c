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
infile.open("proton.txt");
TH1D *h1 = new TH1D("h1","Histogram", 1000,  0, 1);
while(!infile.eof())
    {
      infile >> c;
      h1->Fill(c);
	
}
h1 -> Draw();
}
