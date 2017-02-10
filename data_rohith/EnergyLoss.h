//Written by Rohith Saradhy
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

#ifndef ENERGYLOSS_H
#define ENERGYLOSS_H
double density(double b,double C,double x0,double x1,double a ,double k, double d,bool conductor)
{
  double x = log(b/pow((1-pow(b,2)),0.5))/log(10);
  if(x>=x1)
  {
      return 2*(log(10))*x - C;
  }
  else if(x<x1 && x>=x0)
  {
     return 2*(log(10))*x - C + a*pow((x1-x),k);
  }
  else if(x<x0 && conductor==false)
  {
    return 0;
  }
  else
  {
  return  d*pow(10,2*(x-x0));
  }
}
// function for shell correction
double shell(double b,double I)
{
  double n= b/pow((1-pow(b,2)),0.5) ;
  if(n>0.13)
  {
  return (0.422377*pow(n,-2) +0.0304043*pow(n,-4)-0.00038106*pow(n,-6))*pow(10,-6)*pow(I,2)+(3.858019*pow(n,-2)-0.1667989*pow(n,-4)+0.00157955*pow(n,-6))*pow(10,-9)*pow(I,3);
  }
  else{
    return 0;
  }
}

double EnergyLoss(double p[10],double d[], bool conductor)
{	double b=p[4];
	p[6] = density(p[4],d[0],d[1],d[2],d[3],d[4],d[5],conductor);  //density(double b,double C,double x0,double x1,double a ,double k, double d,bool conductor)
    	p[7] =shell(b,p[5]);
	return ((0.307*p[0]*(pow(p[1],2))*p[2])/(p[3]*(pow(b,2))))*(log((1021997.82*(pow(b,2)))/(p[5]*(1-(pow(b,2)))))-(pow(b,2)) -p[6]/2 -p[7]/p[2]);

}

double EnergyLossArCO2(double p[],double percentCO2)
{
	double dAr[6]={11.948,1.7635,4.4855,0.1971,2.9618,0.0};
	double dC[6]={3.155,0.048,2.5387,0.2076,2.9532,0.14};
	double dO[6]={10.7004,1.7541,4.3213,0.1178,3.2913,0.0};
	double loss_energy, ar,c,o,co2;
    // for Argon
    p[0]=0.00166;
    p[2]=18;
    p[3]=39.947;
    p[5]=188;
	ar = EnergyLoss(p,dAr,false);


	 // for Carbon
    p[0]=1.7;
    p[2]=6;
    p[3]=12.01115;
    p[5]=78;
	c = EnergyLoss(p,dC,false);

	 // for Oxygen
   p[0]=0.00133;
   p[2]=8;
   p[3]=15.9994;
   p[5]=95;
	o = EnergyLoss(p,dO,false);

	co2 = 0.001977*((12.01115/(44.01*1.7))*c + (2*15.9994/(44.01*0.00133))*o);
	loss_energy =(1-(percentCO2/100))*ar +(percentCO2/100)*co2;
	return loss_energy;
}

#endif
